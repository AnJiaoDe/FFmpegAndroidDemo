//
// Created by Administrator on 2019/12/18 0018.
//

#ifndef FFMPEGDEMO_ANDROID_LOG_H
#define FFMPEGDEMO_ANDROID_LOG_H
#include <android/log.h>
#define FF_LOG_TAG     "FFmpeg_Cmd"

#define VLOG(level, TAG, ...)    ((void)__android_log_vprint(level, TAG, __VA_ARGS__))
#define VLOGV(...)  VLOG(ANDROID_LOG_VERBOSE,   FF_LOG_TAG, __VA_ARGS__)
#define VLOGD(...)  VLOG(ANDROID_LOG_DEBUG,     FF_LOG_TAG, __VA_ARGS__)
#define VLOGI(...)  VLOG(ANDROID_LOG_INFO,      FF_LOG_TAG, __VA_ARGS__)
#define VLOGW(...)  VLOG(ANDROID_LOG_WARN,      FF_LOG_TAG, __VA_ARGS__)
#define VLOGE(...)  VLOG(ANDROID_LOG_ERROR,     FF_LOG_TAG, __VA_ARGS__)


#define LOG(level, TAG, ...)    ((void)__android_log_print(level, TAG, __VA_ARGS__))
#define LOGV(...)  LOG(ANDROID_LOG_VERBOSE,   FF_LOG_TAG, __VA_ARGS__)
#define LOGD(...)  LOG(ANDROID_LOG_DEBUG,     FF_LOG_TAG, __VA_ARGS__)
#define LOGI(...)  LOG(ANDROID_LOG_INFO,      FF_LOG_TAG, __VA_ARGS__)
#define LOGW(...)  LOG(ANDROID_LOG_WARN,      FF_LOG_TAG, __VA_ARGS__)
#define LOGE(...)  LOG(ANDROID_LOG_ERROR,     FF_LOG_TAG, __VA_ARGS__)

#define LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR, FF_LOG_TAG, format, ##__VA_ARGS__)
#define LOGI(format, ...)  __android_log_print(ANDROID_LOG_INFO,  FF_LOG_TAG, format, ##__VA_ARGS__)
#endif //FFMPEGDEMO_ANDROID_LOG_H
