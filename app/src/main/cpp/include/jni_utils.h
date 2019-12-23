//
// Created by Administrator on 2019/12/18 0018.
//

#ifndef FFMPEGDEMO_JNI_UTILS_H
#define FFMPEGDEMO_JNI_UTILS_H

#include <jni.h>
#include "android_log.h"

jmethodID getMethodID(JNIEnv *env, jclass clazz, const char *name, const char *sig) {
    if (clazz == NULL) {
        LOGE("---------------not found jclass---------------");
        return NULL;
    }
    jmethodID methodID = (*env)->GetMethodID(env,clazz, name, sig);
    if (methodID == NULL)
        LOGE("-----------not found method %s",name);
    return methodID;
}

jmethodID getStaMethodID(JNIEnv *env, jclass clazz, const char *name, const char *sig) {
    if (clazz == NULL) {
        LOGE("---------------not found jclass---------------");
        return NULL;
    }
    jmethodID methodID = (*env)->GetStaticMethodID(env,clazz, name, sig);
    if (methodID == NULL)
        LOGE("-----------not found method %s",name);
    return methodID;
}


#endif //FFMPEGDEMO_JNI_UTILS_H
