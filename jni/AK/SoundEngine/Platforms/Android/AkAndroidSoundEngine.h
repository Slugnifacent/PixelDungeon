//////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2011 Audiokinetic Inc. / All Rights Reserved
//
//////////////////////////////////////////////////////////////////////

// AkAndroidSoundEngine.h

/// \file 
/// Main Sound Engine interface, specific Android.

#pragma once

#include <AK/SoundEngine/Common/AkTypes.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>
#include <SLES/OpenSLES.h>
#include "SLES/OpenSLES_Android.h"
#include <jni.h>


/// Platform specific initialization settings
/// \sa AK::SoundEngine::Init
/// \sa AK::SoundEngine::GetDefaultPlatformInitSettings
/// - \ref soundengine_initialization_advanced_soundengine_using_memory_threshold
struct AkPlatformInitSettings
{
	// Threading model.
    AkThreadProperties  threadLEngine;			///< Lower engine threading properties
	AkThreadProperties  threadBankManager;		///< Bank manager threading properties (its default priority is AK_THREAD_PRIORITY_NORMAL)
	AkThreadProperties  threadMonitor;			///< Monitor threading properties (its default priority is AK_THREAD_PRIORITY_ABOVENORMAL). This parameter is not used in Release build.
	
    // Memory.
	AkReal32            fLEngineDefaultPoolRatioThreshold;	///< 0.0f to 1.0f value: The percentage of occupied memory where the sound engine should enter in Low memory mode. \ref soundengine_initialization_advanced_soundengine_using_memory_threshold
	AkUInt32            uLEngineDefaultPoolSize;///< Lower Engine default memory pool size
	AkUInt32			uSampleRate;			///< Sampling Rate.  Set to 0 to get the native sample rate.  Default value is 0.
	// Voices.
	AkUInt16            uNumRefillsInVoice;		///< Number of refill buffers in voice buffer. 2 == double-buffered, defaults to 4.
	AkChannelMask		uChannelMask;			///< use AK_SPEAKER_SETUP_STEREO
	SLObjectItf			pSLEngine;				///< OpenSL engine reference for sharing between various audio components.
	JavaVM*				pJavaVM;				///< Active JavaVM for the app, used for internal system calls.  Usually provided through the android_app structure given at startup or the NativeActivity
	jobject				jNativeActivity;		///< NativeActivity instance for this application. Usually provided through the android_app structure, or through other means if your application has an overriden activity.
												///< This is optional.  However, not providing this object will prevent the background music muting when player start his own music in an external player.
};

///< API used for audio output
///< Use with AkInitSettings to select the API used for audio output.
///< \sa AK::SoundEngine::Init
enum AkAudioAPI
{
	AkAPI_Default = 1 << 0,		///< Default audio subsystem
	AkAPI_Dummy = 1 << 2,		///< Dummy output, simply eats the audio stream and outputs nothing.
};

///< Used with \ref AK::SoundEngine::AddSecondaryOutput to specify the type of secondary output.
enum AkAudioOutputType
{
	AkOutput_Dummy = 1 << 2,		///< Dummy output, simply eats the audio stream and outputs nothing.
	AkOutput_MergeToMain = 1 << 3,	///< This output will mix back its content to the main output, after the master mix.
	AkOutput_Main = 1 << 4,			///< Main output.  This cannot be used with AddSecondaryOutput, but can be used to query information about the main output (GetSpeakerConfiguration for example).	
	AkOutput_NumOutputs = 1 << 5,	///< Do not use.
};

namespace AK
{
	namespace SoundEngine
	{
		/// Get instance of OpenSL created by the sound engine at initialization.
		/// \return NULL if sound engine is not initialized
		AK_EXTERNAPIFUNC( SLObjectItf, GetWwiseOpenSLInterface )();
	};
};