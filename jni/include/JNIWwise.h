//
// Created by Joshua on 4/24/2016.
//

#ifndef PIXEL_DUNGEON_JNIWWISE_H
#define PIXEL_DUNGEON_JNIWWISE_H

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
#define SOUND_BANK_PATH "generatedsoundbanks/android/"
#define DEMO_DEFAULT_POOL_SIZE 2*1024*1024
#define DEMO_LENGINE_DEFAULT_POOL_SIZE 2*1024*1024


class JNIWwise {
private:
	CAkFilePackageLowLevelIOBlocking g_lowLevelIO;
    bool InitAndroidIO(JavaVM* VM,JNIEnv *env, jobject thisObj);
    bool InitMemoryManager();
    bool InitStreamingManager();
    bool InitStreamingDevice();
    bool InitSoundEngine();
    bool InitMusicEngine();
    bool LoadBank(JNIEnv *env,jstring Bankname);
public:
	bool Initialize(JavaVM* VM,JNIEnv *env, jobject thisObj);
	bool ProcessAudio();
	bool Close();
	bool LoadBank(const char * Bankname);
	bool PostEvent(const char * Event,int GameObjectID);
	bool RegisterGameObject(const char * Event,int GameObjectID);
};

namespace AK
{
	void * AllocHook(size_t in_size);
	void FreeHook(void * in_ptr);
}

#endif //PIXEL_DUNGEON_JNIWWISE_H
