//
// Created by Joshua on 4/9/2016.
//
#ifndef PIXEL_DUNGEON_WWISE_H
#define PIXEL_DUNGEON_WWISE_H

#include "JNIWwise.h"

#define LOG(x,y...) __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", x,##y);

#define JNI_TRUE 1
#define JNI_FALSE 0

JavaVM* VM;
JNIWwise wwise;

jint JNI_OnLoad(JavaVM* vm, void* reserved);

extern "C" {
	JNIEXPORT jboolean JNICALL Java_com_joshua_WwiseNativeWrapper_Initialize(JNIEnv *env, jobject thisObj);
	JNIEXPORT jstring  JNICALL Java_com_joshua_WwiseNativeWrapper_ProcessAudio(JNIEnv *env, jobject thisObj);
	JNIEXPORT jstring  JNICALL Java_com_joshua_WwiseNativeWrapper_Close(JNIEnv *env, jobject thisObj);
	JNIEXPORT jboolean JNICALL Java_com_joshua_WwiseNativeWrapper_LoadBank(JNIEnv *env, jobject thisObj,jstring Bankname);
	JNIEXPORT jboolean JNICALL Java_com_joshua_WwiseNativeWrapper_RegisterGameObject(JNIEnv *env, jobject thisObj,jstring MonitorName,jint GameObjectID);
	JNIEXPORT jboolean JNICALL Java_com_joshua_WwiseNativeWrapper_PostEvent(JNIEnv *env,   jobject thisObj,jstring Event,jint GameObjectID,jboolean Process);
	JNIEXPORT jboolean JNICALL Java_com_joshua_WwiseNativeWrapper_StopEvent(JNIEnv *env,   jobject thisObj,jstring Event,jint GameObjectID,jboolean Process);
    JNIEXPORT jboolean JNICALL Java_com_joshua_WwiseNativeWrapper_PauseEvent(JNIEnv *env,  jobject thisObj,jstring Event,jint GameObjectID,jboolean Process);
    JNIEXPORT jboolean JNICALL Java_com_joshua_WwiseNativeWrapper_ResumeEvent(JNIEnv *env, jobject thisObj,jstring Event,jint GameObjectID,jboolean Process);
}


#endif //PIXEL_DUNGEON_WWISE_H
