//
// Created by Joshua on 4/24/2016.
//

#include "JNIWwise.h"

bool JNIWwise::Initialize(JavaVM* VM,JNIEnv *env, jobject thisObj)
{
	if(!InitAndroidIO(VM,env,thisObj)) return false;
	if(!InitMemoryManager()) return false;
	if(!InitStreamingManager()) return false;
	if(!InitStreamingDevice()) return false;
	if(!InitSoundEngine()) return false;
	if(!InitMusicEngine()) return false;
	return true;
}

bool JNIWwise::InitAndroidIO(JavaVM* VM,JNIEnv *env, jobject thisObj)
{
    jclass cls = env->FindClass("com/joshua/WwiseNativeWrapper");
    jmethodID mid = env->GetStaticMethodID(cls, "getNativeActivity", "()Landroid/content/Context;");
    if (mid == 0)
    {
        LOG("Message: %s","Could not find getNativeActivity.");
        return false;
    }
    jobject clsObj = env->CallStaticObjectMethod(cls, mid);
    //NativeClass = reinterpret_cast<jobject>(env->NewGlobalRef(clsObj));

    // InitAndroidIO
	AKRESULT eResult = g_lowLevelIO.InitAndroidIO(VM, clsObj);
	if (eResult != AK_Success)
	{
		LOG("eResult : %d : Message: %s",eResult,"InitAndroidIO Not Loaded");
		return false;
	}

    return true;
}

bool JNIWwise::InitMemoryManager(){
	// Create and initialize an instance of the default memory manager. Note
	// that you can override the default memory manager with your own. Refer
	// to the SDK documentation for more information.

	AkMemSettings memSettings;
	memSettings.uMaxNumPools = 20;

    AKRESULT eResult = AK::MemoryMgr::Init(&memSettings);
	if (eResult != AK_Success)
	{
        LOG("eResult : %d : Message: %s",eResult,"Could not create the memory manager.");
        return false;
	}
	return true;
}

bool JNIWwise::InitStreamingManager(){
	// Create and initialize an instance of the default streaming manager. Note
	// that you can override the default streaming manager with your own. Refer
	// to the SDK documentation for more information.
	//
	AkStreamMgrSettings stmSettings;
	AK::StreamMgr::GetDefaultSettings(stmSettings);

	// Customize the Stream Manager settings here.
	if (!AK::StreamMgr::Create(stmSettings))
	{
        LOG("Message: %s","Could not create the Streaming Manager");
        return false;
	}
	return true;
}

bool JNIWwise::InitStreamingDevice(){
    // Create a streaming device with blocking low-level I/O handshaking.
    // Note that you can override the default low-level I/O module with your own. Refer
    // to the SDK documentation for more information.
    //
    AkDeviceSettings deviceSettings;
    AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

    // Customize the streaming device settings here.

    // CAkFilePackageLowLevelIOBlocking::Init() creates a streaming device
    // in the Stream Manager, and registers itself as the File Location Resolver.
    AKRESULT eResult = g_lowLevelIO.Init(deviceSettings);
    if (eResult != AK_Success)
    {
        LOG("Result: %d Message: %s",eResult,"Could not create the streaming device and Low-Level I/O system");
        return false;
    }

    // Set Base Path
    eResult = g_lowLevelIO.SetBasePath(SOUND_BANK_PATH);
    if (eResult != AK_Success)
    {
        LOG("Result: %d Message: %s",eResult,"SetBasePath Not Set");
        return false;
    }
    return true;
}

bool JNIWwise::InitSoundEngine(){
	// Create the Sound Engine
	// Using default initialization parameters
	AkInitSettings initSettings;
    AK::SoundEngine::GetDefaultInitSettings(initSettings);
    initSettings.uDefaultPoolSize = DEMO_DEFAULT_POOL_SIZE;

	AkPlatformInitSettings platformInitSettings;
	AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);
	platformInitSettings.uLEngineDefaultPoolSize = DEMO_LENGINE_DEFAULT_POOL_SIZE;

    AKRESULT eResult = AK::SoundEngine::Init(&initSettings, &platformInitSettings);
	if (eResult != AK_Success)
	{
        LOG("Result: %d : Message: %s",eResult,"Could not initialize the Sound Engine.");
        return false;
	}
	return true;
}

bool JNIWwise::InitMusicEngine(){
	// Initializing the music engine
	//
	// Initialize the music engine
	// Using default initialization parameters

	AkMusicSettings musicInit;
	AK::MusicEngine::GetDefaultInitSettings(musicInit);
    AKRESULT eResult = AK::MusicEngine::Init(&musicInit);
	if (eResult != AK_Success)
	{
        LOG("Result: %d Message: %s",eResult,"Could not initialize the Music Engine.");
        return false;
	}
    LOG("Message: %s","Sound Initialization Success");
    return true;
}

bool JNIWwise::ProcessAudio()
{
    	AK::SoundEngine::RenderAudio();
    	return true;
}

bool JNIWwise::Close(){
	// Terminate the music engine
	// music engine should be terminated before the sound engine.
	AK::MusicEngine::Term();

	// Terminate the sound engine
	AK::SoundEngine::Term();

	// Terminate the streaming device and streaming manager

	// CAkFilePackageLowLevelIOBlocking::Term() destroys its associated streaming device
	// that lives in the Stream Manager, and unregisters itself as the File Location Resolver.
	g_lowLevelIO.Term();

	if (AK::IAkStreamMgr::Get()) AK::IAkStreamMgr::Get()->Destroy();
	// Terminate the Memory Manager

	AK::MemoryMgr::Term();
	LOG("Wwise Exited");
	return true;
}

bool JNIWwise::LoadBank(const char * Bankname){
	AkBankID bankID;
	AKRESULT eResult = AK::SoundEngine::LoadBank(Bankname, AK_DEFAULT_POOL_ID, bankID);
	if (eResult != AK_Success)
	{
		LOG( "LoadBank eResult : %d :  Bank: %s Not Loaded", eResult,Bankname);
		return false;
	}
	LOG( "Bank: %s Loaded",Bankname);
	return true;
}

bool JNIWwise::PostEvent(const char * Event,int GameObjectID, bool Process){
    AK::SoundEngine::PostEvent(Event, GameObjectID);
	if(Process) ProcessAudio();
    LOG( "Event: %s Posted",Event);
    return true;
}

bool JNIWwise::StopEvent(const char * Event, int GameObjectID,bool Process)
{
	return ExecuteActionOnEvent(
		Event,
		AK::SoundEngine::AkActionOnEventType_Stop,
		GameObjectID,
		Process);
}

bool JNIWwise::PauseEvent(const char * Event, int GameObjectID,bool Process)
{
	return ExecuteActionOnEvent(
		Event,
		AK::SoundEngine::AkActionOnEventType_Pause,
		GameObjectID,
		Process);
}

bool JNIWwise::ResumeEvent(const char * Event, int GameObjectID,bool Process)
{
	return ExecuteActionOnEvent(
		Event,
		AK::SoundEngine::AkActionOnEventType_Resume,
		GameObjectID,
		Process);
 }


bool JNIWwise::ExecuteActionOnEvent(const char * Event,
                                    	    AK::SoundEngine::AkActionOnEventType Action,
                                    	    int GameObjectID,
                                    	    bool Process){
    AK::SoundEngine::ExecuteActionOnEvent(Event, Action,GameObjectID);
	if(Process) ProcessAudio();
    LOG( "Event: %s ExecuteActionOnEvent",Event);
    return true;
}

bool JNIWwise::RegisterGameObject(const char * Event,int GameObjectID)
{
	AKRESULT eResult = AK::SoundEngine::RegisterGameObj(GameObjectID, Event);
	if (eResult != AK_Success)
	{
		LOG( "EResult: %d Unable to register %s Game Object ID: %d", eResult,Event,GameObjectID);
		return false;
	}
	LOG( "GameObject: %s Registered",Event);
    return true;
}

namespace AK
{
	void * AllocHook(size_t in_size)
	{
		return malloc(in_size);
	}
	void FreeHook(void * in_ptr)
	{
		free(in_ptr);
	}
}