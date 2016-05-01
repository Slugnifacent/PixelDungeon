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

JNIEXPORT jboolean JNICALL Java_com_joshua_wwise_Initialize(JNIEnv *env, jobject thisObj) {
    if(!wwise.Initialize(VM,env,thisObj))
    {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_com_joshua_wwise_PostEvent(JNIEnv *env, jobject thisObj,jstring Event,jint GameObjectID,jboolean Process) {
   const char *nativeString = env->GetStringUTFChars(Event, 0);
   if(!wwise.PostEvent(nativeString,GameObjectID,Process))
   {
       env->ReleaseStringUTFChars( Event, nativeString);
       return JNI_FALSE;
   }
    env->ReleaseStringUTFChars( Event, nativeString);
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_com_joshua_wwise_RegisterGameObject(JNIEnv *env, jobject thisObj,jstring MonitorName,jint GameObjectID) {
	const char *nativeString = env->GetStringUTFChars(MonitorName, 0);
    if(!wwise.RegisterGameObject(nativeString,GameObjectID))
    {
        env->ReleaseStringUTFChars( MonitorName, nativeString);
        return JNI_FALSE;
    }
	env->ReleaseStringUTFChars( MonitorName, nativeString);
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_com_joshua_wwise_LoadBank(JNIEnv *env, jobject thisObj,jstring Bankname) {
    const char *nativeString = env->GetStringUTFChars(Bankname, 0);
    if(!wwise.LoadBank(nativeString))
    {
        env->ReleaseStringUTFChars( Bankname, nativeString);
        return JNI_FALSE;
    }
    env->ReleaseStringUTFChars( Bankname, nativeString);
    return JNI_TRUE;
}

JNIEXPORT jstring JNICALL Java_com_joshua_wwise_ProcessAudio(JNIEnv *env, jobject thisObj) {
	wwise.ProcessAudio();
	return env->NewStringUTF("");
}

JNIEXPORT jstring JNICALL Java_com_joshua_wwise_Close(JNIEnv *env, jobject thisObj) {
    wwise.Close();
	return env->NewStringUTF("Wwise Exited");
}