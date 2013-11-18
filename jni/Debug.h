#pragma once
#include <Win32toAndroid.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define LOGI(...) printDebug(false, __VA_ARGS__)
#define LOGE(...) printDebug(true, __VA_ARGS__)

void printDebug(bool error,const char* format, ...);

#else
//android kakka
#include <android/log.h>
#include <GLES2/gl2.h>
#define  LOG_TAG    "libKaNot"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__) // Info
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__) // Error
#endif

void printGLString(const char *name, GLenum s);

void checkGlError(const char* op);