//
// Created by Joshua on 4/9/2016.
//

#include "wwise.h"

#include <AK/SoundEngine/Common/AkMemoryMgr.h>                  // Memory Manager
#include <AK/SoundEngine/Common/AkModule.h>                     // Default memory and stream managers

#include <AK/SoundEngine/Common/IAkStreamMgr.h>                 // Streaming Manager
#include <AK/Tools/Common/AkPlatformFuncs.h>                    // Thread defines

#include <AkFilePackageLowLevelIOBlocking.h>                    // Sample low-level I/O implementation

#include <AK/SoundEngine/Common/AkSoundEngine.h>

#include <AK/MusicEngine/Common/AkMusicEngine.h>


CAkFilePackageLowLevelIOBlocking g_lowLevelIO;

#define DEMO_DEFAULT_POOL_SIZE 2*1024*1024
#define DEMO_LENGINE_DEFAULT_POOL_SIZE 2*1024*1024


JavaVM* VM;
JNIEnv* Env;

jobject NativeClass;

   jint JNI_OnLoad(JavaVM* vm, void* reserved)
   {
       JNIEnv* env;
       if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
           return -1;
       }

       // Get jclass with env->FindClass.
       // Register methods with env->RegisterNatives.
        VM = vm;
       return JNI_VERSION_1_6;
   }

   JNIEXPORT jstring JNICALL Java_com_joshua_wwise_Initialize (JNIEnv *env, jobject thisObj) {
        Env = env;

      jclass cls = env->GetObjectClass(thisObj);
      jmethodID mid = env->GetMethodID( cls, "getNativeActivity", "()Landroid/content/Context;");
      if (mid == 0)
         return env->NewStringUTF("Could not create the memory manager." );
       jobject clsObj = env->CallObjectMethod(thisObj, mid);

        NativeClass = reinterpret_cast<jobject>(env->NewGlobalRef(clsObj));

       AKRESULT eResult = g_lowLevelIO.InitAndroidIO(VM, NativeClass);

     if(eResult != AK_Success)
     {
         __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "eResult : %d",eResult);
         return env->NewStringUTF("InitAndroidIO Not Loaded");
     }

        // Initializing Memory Manager
        //
        // Create and initialize an instance of the default memory manager. Note
        // that you can override the default memory manager with your own. Refer
        // to the SDK documentation for more information.
        //

        AkMemSettings memSettings;
        memSettings.uMaxNumPools = 20;

        if ( AK::MemoryMgr::Init( &memSettings ) != AK_Success )
        {
            return env->NewStringUTF("Could not create the memory manager." );
            }


        // Initialize Streaming manager
        //
        // Create and initialize an instance of the default streaming manager. Note
        // that you can override the default streaming manager with your own. Refer
        // to the SDK documentation for more information.
        //

        AkStreamMgrSettings stmSettings;
        AK::StreamMgr::GetDefaultSettings( stmSettings );

        // Customize the Stream Manager settings here.

        if ( !AK::StreamMgr::Create( stmSettings ) )
        {
            return env->NewStringUTF("Could not create the Streaming Manager");
        }


        // Initialize Streaming Device
        //
        // Create a streaming device with blocking low-level I/O handshaking.
        // Note that you can override the default low-level I/O module with your own. Refer
        // to the SDK documentation for more information.
        //
        AkDeviceSettings deviceSettings;
        AK::StreamMgr::GetDefaultDeviceSettings( deviceSettings );

        // Customize the streaming device settings here.

        // CAkFilePackageLowLevelIOBlocking::Init() creates a streaming device
        // in the Stream Manager, and registers itself as the File Location Resolver.
        if ( g_lowLevelIO.Init( deviceSettings ) != AK_Success )
        {
            return env->NewStringUTF("Could not create the streaming device and Low-Level I/O system" );
        }

        //Initializing Sound Engine
        //
        // Create the Sound Engine
        // Using default initialization parameters
        //

        AkInitSettings initSettings;

        AkPlatformInitSettings platformInitSettings;
        AK::SoundEngine::GetDefaultInitSettings( initSettings );
        AK::SoundEngine::GetDefaultPlatformInitSettings( platformInitSettings );
        initSettings.uDefaultPoolSize = DEMO_DEFAULT_POOL_SIZE;
        platformInitSettings.uLEngineDefaultPoolSize = DEMO_LENGINE_DEFAULT_POOL_SIZE;

        if ( AK::SoundEngine::Init( &initSettings, &platformInitSettings ) != AK_Success )
        {
            return env->NewStringUTF("Could not initialize the Sound Engine.");
        }



        // Initializing the music engine
        //
        // Initialize the music engine
        // Using default initialization parameters
        //

        AkMusicSettings musicInit;
        AK::MusicEngine::GetDefaultInitSettings( musicInit );

        if ( AK::MusicEngine::Init( &musicInit ) != AK_Success )
        {
            return env->NewStringUTF("Could not initialize the Music Engine.");
        }

        return env->NewStringUTF("Sound Initialization Success");
   }

    #define BANKNAME_INIT "Init.bnk"
    #define BANKNAME_SOUNDBANK "SoundBank.bnk"
    const AkGameObjectID GAME_OBJECT_ID_SOUNDBANK = 100;


    #include <android/log.h>

    #define APPNAME "MyApp"

    #define SOUND_BANK_PATH "generatedsoundbanks/android/"
     JNIEXPORT jstring JNICALL Java_com_joshua_wwise_LoadBanks (JNIEnv *env, jobject thisObj){
       AKRESULT eResult = g_lowLevelIO.SetBasePath(SOUND_BANK_PATH);
             if(eResult != AK_Success)
                 {
                 __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "eResult : %d",eResult);
                 return env->NewStringUTF("g_lowLevelIO.SetBasePath Not Set");
                 }


        AkBankID bankID;

        eResult = AK::SoundEngine::LoadBank( BANKNAME_INIT, AK_DEFAULT_POOL_ID, bankID );

        if(eResult != AK_Success)
         {
         __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "eResult : %d",eResult);
         return env->NewStringUTF("BANKNAME_INIT Not Loaded");
         }
        eResult = AK::SoundEngine::LoadBank( BANKNAME_SOUNDBANK, AK_DEFAULT_POOL_ID, bankID );
        if(eResult != AK_Success) return env->NewStringUTF("BANKNAME_SOUNDBANK Not Loaded");



        eResult = AK::SoundEngine::RegisterGameObj( GAME_OBJECT_ID_SOUNDBANK, "SoundBank" );
        if(eResult != AK_Success)
         {
         __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "eResult : %d",eResult);
         return env->NewStringUTF("GAME_OBJECT_ID_SOUNDBANK Not RegisterGameObj");
         }

        AK::SoundEngine::PostEvent( "Play_Game", GAME_OBJECT_ID_SOUNDBANK );

        return env->NewStringUTF("Banks Loaded");
    }



    JNIEXPORT jstring JNICALL Java_com_joshua_wwise_ProcessAudio (JNIEnv *env, jobject thisObj){
        AK::SoundEngine::RenderAudio();
        return env->NewStringUTF("");
    }

    JNIEXPORT jstring JNICALL Java_com_joshua_wwise_Close (JNIEnv *env, jobject thisObj){
            //
            // Terminate the music engine
            // music engine should be terminated before the sound engine.
            //

            AK::MusicEngine::Term();

    //
    // Terminate the sound engine
    //

    AK::SoundEngine::Term();

    // Terminate the streaming device and streaming manager

    // CAkFilePackageLowLevelIOBlocking::Term() destroys its associated streaming device
    // that lives in the Stream Manager, and unregisters itself as the File Location Resolver.

    g_lowLevelIO.Term();

    if ( AK::IAkStreamMgr::Get() )
        AK::IAkStreamMgr::Get()->Destroy();

    // Terminate the Memory Manager
    AK::MemoryMgr::Term();

        return env->NewStringUTF("Wwise Exited");


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