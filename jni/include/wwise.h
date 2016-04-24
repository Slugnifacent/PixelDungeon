//
// Created by Joshua on 4/9/2016.
//
#ifndef PIXEL_DUNGEON_WWISE_H
#define PIXEL_DUNGEON_WWISE_H

#include <jni.h>
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>                 // Streaming Manager
#include <AK/Tools/Common/AkPlatformFuncs.h>                    // Thread defines
#include <AK/MusicEngine/Common/AkMusicEngine.h>



jint JNI_OnLoad(JavaVM* vm, void* reserved);
extern "C" {

JNIEXPORT jstring JNICALL Java_com_joshua_wwise_getMessage(JNIEnv *, jobject);
JNIEXPORT jstring JNICALL Java_com_joshua_wwise_Initialize (JNIEnv *env, jobject thisObj);
JNIEXPORT jstring JNICALL Java_com_joshua_wwise_ProcessAudio (JNIEnv *env, jobject thisObj);
JNIEXPORT jstring JNICALL Java_com_joshua_wwise_Close (JNIEnv *env, jobject thisObj);
JNIEXPORT jstring JNICALL Java_com_joshua_wwise_LoadBanks (JNIEnv *env, jobject thisObj);

}


namespace AK
{
    void * AllocHook( size_t in_size );
    void FreeHook( void * in_ptr );
}
#endif //PIXEL_DUNGEON_WWISE_H
