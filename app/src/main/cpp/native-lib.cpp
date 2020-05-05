#include <jni.h>
#include <string>

#include <android_log.h>
#include "F:\\IT\\ffmpeg\\ffmpeg-4.2.1_can_make_so\\ffmpeg-4.2.1\\fftools\\ffmpeg.h"
JNIEnv* jniEnv;
//extern "C" JNIEXPORT jboolean JNICALL
//Java_com_cy_ffmpegdemo_JniUtils_remuxe(JNIEnv *env, jclass type, jstring inPath_,
//                                       jstring outPath_) {
//    const char *inPath = env->GetStringUTFChars(inPath_, 0);
//    const char *outPath = env->GetStringUTFChars(outPath_, 0);
//
//    // TODO
//    int result = main_remuxer(inPath, outPath);
//    env->ReleaseStringUTFChars(inPath_, inPath);
//    env->ReleaseStringUTFChars(outPath_, outPath);
//    if (result == 0) {
//        return true;
//    } else {
//        return false;
//
//    }
//
//}
extern "C"
JNIEXPORT void JNICALL
Java_com_cy_ffmpegdemo_JniUtils_runCmd(JNIEnv *env, jclass type, jobjectArray commands) {
    jniEnv=env;
    int argc = env->GetArrayLength( commands);
    char *argv[argc];

    LOGE("Kit argc %d\n", argc);
    int i;
    for (i = 0; i < argc; i++) {
        jstring js = (jstring)env->GetObjectArrayElement( commands, i);
        argv[i] = (char *) env->GetStringUTFChars( js, 0);
        LOGE("Kit argv %s\n", argv[i]);
    }

    run(argc, argv);
}


/**将JAVA字符串数组转C char字符数组（俗称字符串）的数组**/
//char **stringArrToCharArr(JNIEnv *env, jclass jc, jobjectArray strArray) {
//    jstring jstr;
//    jsize len = env->GetArrayLength(strArray);
//    char **pstr = (char **) malloc(len * sizeof(char *));
//
//    for (jsize i = 0; i < len; i++) {
//        jstr = static_cast<jstring>(env->GetObjectArrayElement(strArray, i));
//        pstr[i] = (char *) env->GetStringUTFChars(jstr, 0);
//    }
//    return pstr;
//}
