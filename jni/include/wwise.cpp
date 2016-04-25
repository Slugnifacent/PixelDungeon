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
	VM = vm;
	return JNI_VERSION_1_6;
}

jboolean SetNativeActivity(JNIEnv *env, jobject thisObj)
{
    jclass cls = env->GetObjectClass(thisObj);
    jmethodID mid = env->GetMethodID(cls, "getNativeActivity", "()Landroid/content/Context;");
    if (mid == 0)
    {
        LOG("Message: %s","Could not create the memory manager.");
        return JNI_FALSE;
    }
    jobject clsObj = env->CallObjectMethod(thisObj, mid);
    NativeClass = reinterpret_cast<jobject>(env->NewGlobalRef(clsObj));
    return JNI_TRUE;
}

jboolean InitAndroidIO()
{
	AKRESULT eResult = g_lowLevelIO.InitAndroidIO(VM, NativeClass);
	if (eResult != AK_Success)
	{
		LOG("eResult : %d : Message: %s",eResult,"InitAndroidIO Not Loaded");
		return JNI_FALSE;
	}
	return JNI_TRUE;
}

jboolean InitMemoryManager()
{
	// Create and initialize an instance of the default memory manager. Note
	// that you can override the default memory manager with your own. Refer
	// to the SDK documentation for more information.

	AkMemSettings memSettings;
	memSettings.uMaxNumPools = 20;

    AKRESULT eResult = AK::MemoryMgr::Init(&memSettings);
	if (eResult != AK_Success)
	{
        LOG("eResult : %d : Message: %s",eResult,"Could not create the memory manager.");
        return JNI_FALSE;
	}
	return JNI_TRUE;
}

jboolean InitStreamingManager()
{
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
        return JNI_FALSE;
	}
	return JNI_TRUE;
}

jboolean InitStreamingDevice()
{
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
        return JNI_FALSE;
	}

	// Set Base Path
    eResult = g_lowLevelIO.SetBasePath(SOUND_BANK_PATH);
    if (eResult != AK_Success)
    {
        LOG("Result: %d Message: %s",eResult,"SetBasePath Not Set");
    }
	return JNI_TRUE;
}

jboolean InitSoundEngine()
{
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
        return JNI_FALSE;
	}
	return JNI_TRUE;
}

jboolean InitMusicEngine()
{
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
        return JNI_FALSE;
	}
    LOG("Message: %s","Sound Initialization Success");
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_com_joshua_wwise_Initialize(JNIEnv *env, jobject thisObj) {
	Env = env;
    if(!SetNativeActivity(env,thisObj)) return JNI_FALSE;
    if(!InitAndroidIO()) return JNI_FALSE;
    if(!InitMemoryManager()) return JNI_FALSE;
    if(!InitStreamingManager()) return JNI_FALSE;
    if(!InitStreamingDevice()) return JNI_FALSE;
    if(!InitSoundEngine()) return JNI_FALSE;
    if(!InitMusicEngine()) return JNI_FALSE;
	return JNI_TRUE;
}

jboolean LoadBank(JNIEnv *env,jstring Bankname)
{
    const char *nativeString = env->GetStringUTFChars(Bankname, 0);
	AkBankID bankID;
	AKRESULT eResult = AK::SoundEngine::LoadBank(nativeString, AK_DEFAULT_POOL_ID, bankID);
	if (eResult != AK_Success)
	{
		LOG( "LoadBank eResult : %d :  Bank: %s Not Loaded", eResult,nativeString);
		env->ReleaseStringUTFChars( Bankname, nativeString);
		return JNI_FALSE;
	}
	LOG( "Bank: %s Loaded",nativeString);
	env->ReleaseStringUTFChars( Bankname, nativeString);
	return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_com_joshua_wwise_PostEvent(JNIEnv *env, jobject thisObj,jstring Event,jint GameObjectID) {
    const char *nativeString = env->GetStringUTFChars(Event, 0);
    AK::SoundEngine::PostEvent(nativeString, GameObjectID);
    LOG( "Event: %s Posted",nativeString);
    env->ReleaseStringUTFChars( Event, nativeString);
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_com_joshua_wwise_RegisterGameObject(JNIEnv *env, jobject thisObj,jstring MonitorName,jint GameObjectID) {
	const char *nativeString = env->GetStringUTFChars(MonitorName, 0);
	AKRESULT eResult = AK::SoundEngine::RegisterGameObj(GameObjectID, nativeString);
	if (eResult != AK_Success)
	{
		LOG( "EResult: %d Unable to register %s Game Object ID: %d", eResult,nativeString,GameObjectID);
		return JNI_FALSE;
	}
	LOG( "GameObject: %s Registered",nativeString);
	env->ReleaseStringUTFChars( MonitorName, nativeString);
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_com_joshua_wwise_LoadBank(JNIEnv *env, jobject thisObj,jstring Bankname) {
    if(!LoadBank(env,Bankname)) return JNI_FALSE;
	return JNI_TRUE;
}



JNIEXPORT jstring JNICALL Java_com_joshua_wwise_ProcessAudio(JNIEnv *env, jobject thisObj) {
	AK::SoundEngine::RenderAudio();
	return env->NewStringUTF("");
}

JNIEXPORT jstring JNICALL Java_com_joshua_wwise_Close(JNIEnv *env, jobject thisObj) {
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
	if (AK::IAkStreamMgr::Get())
		AK::IAkStreamMgr::Get()->Destroy();
	// Terminate the Memory Manager
	AK::MemoryMgr::Term();
	return env->NewStringUTF("Wwise Exited");
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