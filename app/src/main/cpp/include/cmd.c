//
// Created by Administrator on 2019/12/18 0018.
//

//#include "ffmpeg_cmd.h"
#include <jni.h>
#include <string.h>
#include <android_log.h>
#include "jni_utils.h"
#include "ffmpeg.h"
#include "cmd.h"
#include <pthread.h>

JNIEnv *jniEnv;
jclass clazz_java;
pthread_t pthread_id;

JNIEXPORT void JNICALL
Java_com_cy_ffmpegcmd_JniUtils_runCmd(JNIEnv *env, jclass clazz, jint index,
                                      jobjectArray commands) {

    jniEnv = env;
    clazz_java = clazz;
    int argc = (*env)->GetArrayLength(env, commands);
    char *argv[argc];

    LOGE("Kit argc %d\n", argc);
    int i;
    for (i = 0; i < argc; i++) {
        jstring js = (jstring) (*env)->GetObjectArrayElement(env, commands, i);
        argv[i] = (char *) (*env)->GetStringUTFChars(env, js, 0);
        LOGE("Kit argv %s\n", argv[i]);
    }

    int temp = pthread_create(&pthread_id, NULL, thread, NULL);
    if (temp != 0) {
        LOGE("can't create thread: %s ", strerror(temp));
        return 1;
    }
    LOGI("create thread succes: %s ", strerror(temp));


}

void *thread(void *arg) {
    int ret = run_cmd(*arg, *(arg+), argv);
    if (ret == 0) {
        jmethodID methodId = getMethodID(jniEnv, clazz_java, "onSuccess", "(I)V");
        if (methodId != NULL)(*jniEnv)->CallVoidMethod(jniEnv, clazz_java, methodId, index);
    } else {
        jmethodID methodId = getMethodID(jniEnv, clazz_java, "onFail", "(I)V");
        if (methodId != NULL)(*jniEnv)->CallVoidMethod(jniEnv, clazz_java, methodId, index);
    }
    return ((void *) 0);
}

JNIEXPORT void JNICALL
Java_com_cy_ffmpegcmd_JniUtils_cancelCmd(JNIEnv *env, jclass clazz, jint index) {
    //发出SIGUSR2信号，让线程退出，如果发送SIGKILL，线程将直接退出。
    pthread_kill(tid, SIGKILL);
}

void cmd_progress(int index, int hour, int min, int secs, int totalSecs) {
    jmethodID methodId = getMethodID(jniEnv, clazz_java, "onProgress", "(IIIII)V");
    if (methodId != NULL)
        (*jniEnv)->CallVoidMethod(jniEnv, clazz_java, methodId, index, hour, min, secs, totalSecs);
}
