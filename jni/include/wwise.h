//
// Created by Joshua on 4/9/2016.
//
#ifndef PIXEL_DUNGEON_WWISE_H
#define PIXEL_DUNGEON_WWISE_H

#include <jni.h>
#include <android/log.h>
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>                 // Streaming Manager
#include <AK/MusicEngine/Common/AkMusicEngine.h>
#include <AK/SoundEngine/Common/AkMemoryMgr.h>                  // Memory Manager
#include <AK/SoundEngine/Common/AkModule.h>                     // Default memory and stream managers
#include <AK/SoundEngine/Common/IAkStreamMgr.h>                 // Streaming Manager
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/MusicEngine/Common/AkMusicEngine.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>                    // Thread defines
#include <AK/Tools/Common/AkPlatformFuncs.h>                    // Thread defines
#include <AkFilePackageLowLevelIOBlocking.h>                    // Sample low-level I/O implementation


#define LOG(x,y...) __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", x,##y);

#define JNI_TRUE 1
#define JNI_FALSE 0

#define BANKNAME_INIT "Init.bnk"
#define BANKNAME_SOUNDBANK "SoundBank.bnk"

#define SOUND_BANK_PATH "generatedsoundbanks/android/"

#define DEMO_DEFAULT_POOL_SIZE 2*1024*1024
#define DEMO_LENGINE_DEFAULT_POOL_SIZE 2*1024*1024

const AkGameObjectID GAME_OBJECT_ID_SOUNDBANK = 100;

JavaVM* VM;
JNIEnv* Env;
jobject NativeClass;
CAkFilePackageLowLevelIOBlocking g_lowLevelIO;

jint JNI_OnLoad(JavaVM* vm, void* reserved);
jboolean SetNativeActivity(JNIEnv *env, jobject thisObj);
jboolean InitAndroidIO();
jboolean InitMemoryManager();
jboolean InitStreamingManager();
jboolean InitStreamingDevice();
jboolean InitSoundEngine();
jboolean InitMusicEngine();
jboolean LoadBank(JNIEnv *env,jstring Bankname);



extern "C" {
	JNIEXPORT jboolean JNICALL Java_com_joshua_wwise_Initialize(JNIEnv *env, jobject thisObj);
	JNIEXPORT jstring JNICALL Java_com_joshua_wwise_ProcessAudio(JNIEnv *env, jobject thisObj);
	JNIEXPORT jstring JNICALL Java_com_joshua_wwise_Close(JNIEnv *env, jobject thisObj);
	JNIEXPORT jboolean JNICALL Java_com_joshua_wwise_LoadBank(JNIEnv *env, jobject thisObj,jstring Bankname);
	JNIEXPORT jboolean JNICALL Java_com_joshua_wwise_PostEvent(JNIEnv *env, jobject thisObj,jstring Event,jint GameObjectID);
	JNIEXPORT jboolean JNICALL Java_com_joshua_wwise_RegisterGameObject(JNIEnv *env, jobject thisObj,jstring MonitorName,jint GameObjectID);
}


namespace AK
{
	void * AllocHook(size_t in_size);
	void FreeHook(void * in_ptr);
}
#endif //PIXEL_DUNGEON_WWISE_H
