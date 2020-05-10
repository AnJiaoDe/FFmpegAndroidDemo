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

static JavaVM *jvm;
static jclass clazz_java;

struct Parameter_run_cmd {
    JNIEnv *jniEnv;
    int index;
    int arg_num;
    char **args;
};

void *thread_run_cmd(void *arg) {
    struct Parameter_run_cmd *parameter_run_cmd = (Parameter_run_cmd *) arg;

    LOGI("thread_run_cmd index %d\n", parameter_run_cmd->index);
    LOGI("thread_run_cmd arg_num %d\n", parameter_run_cmd->arg_num);
    LOGI("thread_run_cmd args  %d\n", parameter_run_cmd->args[0]);
    LOGI("thread_run_cmd args  %s\n", parameter_run_cmd->args[0]);


    int ret = run_cmd_ffmpeg(parameter_run_cmd->index, parameter_run_cmd->arg_num,
                             parameter_run_cmd->args);
    LOGI("run_cmd_ffmpeg");

    if (ret == 0) {
        jmethodID methodId = getMethodID(parameter_run_cmd->jniEnv, clazz_java, "onSuccess",
                                         "(I)V");
        if (methodId != NULL) {
            jvm->AttachCurrentThread(&parameter_run_cmd->jniEnv, NULL);
            parameter_run_cmd->jniEnv->CallVoidMethod(clazz_java,
                                                      methodId, parameter_run_cmd->index);
            jvm->DetachCurrentThread();
        }
    } else {
        jmethodID methodId = getMethodID(parameter_run_cmd->jniEnv, clazz_java, "onFail", "(I)V");
        if (methodId != NULL) {
            jvm->AttachCurrentThread(&parameter_run_cmd->jniEnv, NULL);
            parameter_run_cmd->jniEnv->CallVoidMethod(clazz_java,
                                                      methodId, parameter_run_cmd->index);
            jvm->DetachCurrentThread();
        }
    }
    return (void *) 0;
}

/**
 * 工具方法，把java的string类型转化成 c的str
 */
char *Jstring2CppStr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes",
                                     "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid,
                                                         strencode); // String .getByte("GB2312");
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = '\0';
    }
    env->ReleaseByteArrayElements(barr, ba, 0); //释放内存
    return rtn;
}
JNIEXPORT jlong JNICALL
Java_com_cy_ffmpegcmd_JniUtils_runCmd(JNIEnv *env, jclass clazz, jint index,
                                      jobjectArray commands) {

    env->GetJavaVM(&jvm);
    clazz_java = clazz;
    int arg_num = env->GetArrayLength(commands);
    char **args = (char **) malloc(sizeof(char *) * arg_num);

    LOGE("Kit argc %d\n", arg_num);
    int i;
    for (i = 0; i < arg_num; i++) {
        jstring js = (jstring) env->GetObjectArrayElement(commands, i);
        args[i] = Jstring2CppStr(env, js);
        LOGE("Kit argv %s\n", args[i]);
    }
    LOGI("pthread_create0");

    struct Parameter_run_cmd *parameter_run_cmd = (Parameter_run_cmd *) malloc(
            sizeof(Parameter_run_cmd));
    LOGI("pthread_create1");

    parameter_run_cmd->jniEnv = env;
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
        jmethodID methodId = getMethodID(env, clazz_java, "onFail", "(I)V");
        if (methodId != NULL)env->CallVoidMethod(clazz_java, methodId, index);
        return -1;
    }
    LOGI("create thread succes: %s ", strerror(temp));
    return ntid;

}


void cmd_progress(int index, int hour, int min, int secs, int totalSecs) {
    LOGI("cmd_progress");
    JNIEnv *jniEnv;
    jvm->AttachCurrentThread(&jniEnv, NULL);
    jmethodID methodId = getMethodID(jniEnv, clazz_java, "onProgress", "(IIIII)V");
    if (methodId != NULL) {
        LOGI("cmd_progress111111");

        jniEnv->CallVoidMethod(clazz_java, methodId, index, hour, min, secs, totalSecs);
        LOGI("cmd_progress333333333333333");

        jvm->DetachCurrentThread();
        LOGI("cmd_progress4444444444444");

    }
}

JNIEXPORT void JNICALL
Java_com_cy_ffmpegcmd_JniUtils_cancelCmd(JNIEnv *env, jclass type, jlong id_thread) {
    pthread_kill(id_thread, SIGKILL);
}

