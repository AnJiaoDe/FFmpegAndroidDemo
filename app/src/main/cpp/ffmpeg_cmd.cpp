//
// Created by Administrator on 2019/12/18 0018.
//

//#include "ffmpeg_cmd.h"
#include <jni.h>
#include<stdlib.h>
#include <string.h>
#include <android_log.h>
#include "jni_utils.h"
#include "ffmpeg.h"
#include "ffmpeg_cmd.h"
#include <pthread.h>

JNIEnv *jniEnv;
JavaVM *jvm;

jclass clazz_java;

struct Parameter_run_cmd {
    int index;
    int arg_num;
    char **args;
};

void *thread_run_cmd(void *arg) {
    struct Parameter_run_cmd *parameter_run_cmd = arg;

    LOGI("thread_run_cmd index %d\n", parameter_run_cmd->index);
    LOGI("thread_run_cmd arg_num %d\n", parameter_run_cmd->arg_num);
    LOGI("thread_run_cmd args  %d\n", parameter_run_cmd->args[0]);
    LOGI("thread_run_cmd args  %s\n", parameter_run_cmd->args[0]);


    int ret = run_cmd_ffmpeg(parameter_run_cmd->index, parameter_run_cmd->arg_num,
                             parameter_run_cmd->args);
    LOGI("run_cmd_ffmpeg");

    if (ret == 0) {
        jmethodID methodId = getMethodID(jniEnv, clazz_java, "onSuccess", "(I)V");
        if (methodId != NULL) {
            (*jvm)->AttachCurrentThread(jvm, (void **) &jniEnv, NULL);
            jniEnv->CallVoidMethod(jniEnv, clazz_java, methodId, parameter_run_cmd->index);
            (*jvm)->DetachCurrentThread(jvm);
        }
    } else {
        jmethodID methodId = getMethodID(jniEnv, clazz_java, "onFail", "(I)V");
        if (methodId != NULL) {
            (*jvm)->AttachCurrentThread(jvm, (void **) &jniEnv, NULL);
            (*jniEnv)->CallVoidMethod(jniEnv, clazz_java, methodId, parameter_run_cmd->index);
            (*jvm)->DetachCurrentThread(jvm);
        }
    }
    return (void *) 0;
}
extern "C"
JNIEXPORT jlong JNICALL
Java_com_cy_ffmpegcmd_JniUtils_runCmd(JNIEnv *env, jclass clazz, jint index,
                                      jobjectArray commands) {

    jniEnv = env;
    (*env)->GetJavaVM(env, &jvm);
    clazz_java = clazz;
    int arg_num = (*env)->GetArrayLength(env, commands);
    char **args = malloc(sizeof(char *) * arg_num);

    LOGE("Kit argc %d\n", arg_num);
    int i;
    for (i = 0; i < arg_num; i++) {
        jstring js = (jstring) (*env)->GetObjectArrayElement(env, commands, i);
        args[i] = env->GetStringUTFChars(env, js, 0);
        LOGE("Kit argv %s\n", args[i]);
    }
    LOGI("pthread_create0");

    struct Parameter_run_cmd *parameter_run_cmd = malloc(sizeof(struct Parameter_run_cmd));
    LOGI("pthread_create1");

    parameter_run_cmd->index = index;
    parameter_run_cmd->arg_num = arg_num;
    parameter_run_cmd->args = args;
    LOGI("pthread_create2 index %d", index);
    LOGI("pthread_create2 arg_num %d", arg_num);
    LOGI("pthread_create2 args %d", args[0]);
    LOGI("pthread_create2 args %s", args[0]);

    pthread_t ntid = 0;

    int temp = pthread_create(&ntid, NULL, thread_run_cmd, parameter_run_cmd);

//    int temp = run_cmd_ffmpeg(index, arg_num,args);

    if (temp != 0) {
        LOGE("can't create thread: %s ", strerror(temp));
        jmethodID methodId = getMethodID(jniEnv, clazz_java, "onFail", "(I)V");
        if (methodId != NULL)(*jniEnv)->CallVoidMethod(jniEnv, clazz_java, methodId, index);
        return -1;
    }
    LOGI("create thread succes: %s ", strerror(temp));
    return ntid;

}

void cmd_progress(int index, int hour, int min, int secs, int totalSecs) {
    LOGI("cmd_progress");

    jmethodID methodId = getMethodID(jniEnv, clazz_java, "onProgress", "(IIIII)V");
    if (methodId != NULL) {
        LOGI("cmd_progress111111");

        (*jvm)->AttachCurrentThread(jvm, (void **) &jniEnv, NULL);
        LOGI("cmd_progress2222222222222222");

        (*jniEnv)->CallVoidMethod(jniEnv, clazz_java, methodId, index, hour, min, secs, totalSecs);
        LOGI("cmd_progress333333333333333");

        (*jvm)->DetachCurrentThread(jvm);
        LOGI("cmd_progress4444444444444");


    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_cy_ffmpegcmd_JniUtils_cancelCmd(JNIEnv *env, jclass type, jlong id_thread) {
    pthread_kill(id_thread, SIGKILL);
}
