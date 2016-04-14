//
// Created by Joshua on 4/9/2016.
//

#include "wwise.h"

   jint JNI_OnLoad(JavaVM* vm, void* reserved)
   {
       JNIEnv* env;
       if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
           return -1;
       }

       // Get jclass with env->FindClass.
       // Register methods with env->RegisterNatives.

       return JNI_VERSION_1_6;
   }

   JNIEXPORT jstring JNICALL Java_com_joshua_wwise_getMessage (JNIEnv *env, jobject thisObj) {

    AkInitSettings initSettings;
    AkPlatformInitSettings platformInitSettings;
    AK::SoundEngine::GetDefaultInitSettings( initSettings );
    AK::SoundEngine::GetDefaultPlatformInitSettings( platformInitSettings );

    if ( AK::SoundEngine::Init( &initSettings, &platformInitSettings ) != AK_Success )
    {
        return env->NewStringUTF("Could not initialize the Sound Engine.");
    }

        AkMusicSettings musicInit;
        AK::MusicEngine::GetDefaultInitSettings( musicInit );

        if ( AK::MusicEngine::Init( &musicInit ) != AK_Success )
        {
            return env->NewStringUTF("Could not initialize the Music Engine.");
        }

    return env->NewStringUTF("Sound Initialization Success");


   }
namespace AK
{
    void * AllocHook( size_t in_size )
    {
        return malloc( in_size );
    }
    void FreeHook( void * in_ptr )
    {
        free( in_ptr );
    }
    }