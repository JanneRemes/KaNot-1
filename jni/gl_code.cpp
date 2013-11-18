/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// OpenGL ES 2.0 code

#include <Win32toAndroid.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Engine.h>
#include <FileReader.h>
#include <Debug.h>


static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

Engine* engine;

bool setupGraphics(int w, int h) {
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);

	engine = new Engine();
	engine->fixAspectRatio(1000,1000,w,h);
    checkGlError("glViewport");
    return true;
}

void renderFrame() {
	engine->Update();
	engine->Draw();
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_step(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_GetManager(JNIEnv* env, jclass clazz, jobject assetManager);
};

JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}

JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_GetManager(JNIEnv* env, jclass clazz, jobject assetManager)
{
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	FileReader::mgr = mgr;
}
