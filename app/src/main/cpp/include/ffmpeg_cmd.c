//
// Created by Administrator on 2019/12/18 0018.
//

//#include "ffmpeg_cmd.h"
#include <jni.h>
#include <string.h>
#include <android_log.h>
#include "jni_utils.h"
#include "ffmpeg.h"
#include "ffmpeg_cmd.h"

JNIEnv *jniEnv;
jclass clazz_java;

static JavaVM *jvm = NULL;
//java虚拟机
static jclass m_clazz = NULL;//当前类(面向java)

JNIEXPORT void JNICALL
Java_com_cy_ffmpegcmd_JniUtils_runCmd(JNIEnv *env, jclass clazz, jobjectArray commands) {
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




    //新建线程 执行ffmpeg 命令
//    ffmpeg_thread_run_cmd(argc, argv);
    //注册ffmpeg命令执行完毕时的回调
//    ffmpeg_thread_callback(ffmpeg_callback);

//    free(strr);

    int ret = run_cmd(argc, argv);
    if(ret==0){
        jmethodID methodId = getMethodID(jniEnv, clazz_java, "onSuccess", "()V");
        if (methodId != NULL)(*jniEnv)->CallVoidMethod(jniEnv,clazz_java, methodId, ret);
    } else{
        jmethodID methodId = getMethodID(jniEnv, clazz_java, "onFail", "()V");
        if (methodId != NULL)(*jniEnv)->CallVoidMethod(jniEnv,clazz_java, methodId, ret);
    }


}

void cmd_progress(int hour,int min,int secs,int totalSecs) {
    jmethodID methodId = getMethodID(jniEnv, clazz_java, "onProgress", "(IIII)V");
    if (methodId != NULL)(*jniEnv)->CallVoidMethod(jniEnv, clazz_java, methodId, hour,min,secs,totalSecs);
}
//void cmd_onFailed(char * msg){
//    jmethodID methodId = getMethodID(jniEnv, clazz_java, "onFailed", "(Ljava/lang/String;)V");
//    if (methodId != NULL)(*jniEnv)->CallVoidMethod(jniEnv, clazz_java, methodId, (*jniEnv)->NewStringUTF(jniEnv,msg));
//}
///**
// * c语言-线程回调
// */
//static void ffmpeg_callback(int ret) {
//    JNIEnv *env;
//    //附加到当前线程从JVM中取出JNIEnv, C/C++从子线程中直接回到Java里的方法时  必须经过这个步骤
//    (*jvm)->AttachCurrentThread(jvm, (void **) &env, NULL);
////    callJavaMethod(env, m_clazz,ret);
//    //完毕-脱离当前线程
//    (*jvm)->DetachCurrentThread(jvm);
//}
/**
 * 回调执行Java方法
 * 参看 Jni反射+Java反射
 */
//void callJavaMethod(JNIEnv *env, jclass clazz,int ret) {
//    if (clazz == NULL) {
//        LOGE("---------------clazz isNULL---------------");
//        return;
//    }
//    //获取方法ID (I)V指的是方法签名 通过javap -s -public FFmpegCmd 命令生成
//    jmethodID methodID = (*env)->GetStaticMethodID(env, clazz, "onExecuted", "(I)V");
//    if (methodID == NULL) {
//        LOGE("---------------methodID isNULL---------------");
//        return;
//    }
//    //调用该java方法
//    (*env)->CallStaticVoidMethod(env, clazz, methodID,ret);
//}