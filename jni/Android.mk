LOCAL_PATH := $(call my-dir)
LOCAL_EXPORT_C_INCLUDES := jni/wwise/AK \
                           jni/wwise/AK/Comm \
                           jni/wwise/AK/DSP \
                           jni/wwise/AK/DSP/Generic \
                           jni/wwise/AK/MotionEngine/Common \
                           jni/wwise/AK/MusicEngine/Common \
                           jni/wwise/AK/Plugin \
                           jni/wwise/AK/Plugin/PluginServices \
                           jni/wwise/AK/SoundEngine/Common \
                           jni/wwise/AK/Platforms/Android \
                           jni/wwise/AK/SoundFrame \
                           jni/wwise/AK/Tools/Android \
                           jni/wwise/AK/Tools/Common \
                           jni/wwise/AK/Wwise \
                           jni/wwise/AK/SourceControl \





 $(info Local Includes: $(LOCAL_EXPORT_C_INCLUDES)) 

WWISE_LIB_DIR := ../wwise/wwiselib

# prepare AkAudioInputSource
include $(CLEAR_VARS)
LOCAL_MODULE    := AkAudioInputSource
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkAudioInputSource.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkCompressorFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkCompressorFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkCompressorFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkConvolutionReverbFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkConvolutionReverbFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkConvolutionReverbFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkDelayFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkDelayFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkDelayFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkExpanderFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkExpanderFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkExpanderFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkFlangerFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkFlangerFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkFlangerFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkGainFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkGainFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkGainFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkGuitarDistortionFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkGuitarDistortionFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkGuitarDistortionFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkHarmonizerFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkHarmonizerFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkHarmonizerFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkMatrixReverbFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkMatrixReverbFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkMatrixReverbFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkMemoryMgr
include $(CLEAR_VARS)
LOCAL_MODULE    := AkMemoryMgr
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkMemoryMgr.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkMeterFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkMeterFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkMeterFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkMusicEngine
include $(CLEAR_VARS)
LOCAL_MODULE    := AkMusicEngine
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkMusicEngine.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkParametricEQFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkParametricEQFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkParametricEQFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkPeakLimiterFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkPeakLimiterFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkPeakLimiterFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkPitchShifterFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkPitchShifterFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkPitchShifterFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkRoomVerbFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkRoomVerbFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkRoomVerbFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkSilenceSource
include $(CLEAR_VARS)
LOCAL_MODULE    := AkSilenceSource
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkSilenceSource.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkSineSource
include $(CLEAR_VARS)
LOCAL_MODULE    := AkSineSource
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkSineSource.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkSoundEngine
include $(CLEAR_VARS)
LOCAL_MODULE    := AkSoundEngine
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkSoundEngine.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkSoundSeedImpactFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkSoundSeedImpactFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkSoundSeedImpactFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkSoundSeedWind
include $(CLEAR_VARS)
LOCAL_MODULE    := AkSoundSeedWind
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkSoundSeedWind.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkSoundSeedWoosh
include $(CLEAR_VARS)
LOCAL_MODULE    := AkSoundSeedWoosh
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkSoundSeedWoosh.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkStereoDelayFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkStereoDelayFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkStereoDelayFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkStreamMgr
include $(CLEAR_VARS)
LOCAL_MODULE    := AkStreamMgr
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkStreamMgr.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkSynthOne
include $(CLEAR_VARS)
LOCAL_MODULE    := AkSynthOne
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkSynthOne.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkTimeStretchFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkTimeStretchFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkTimeStretchFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkToneSource
include $(CLEAR_VARS)
LOCAL_MODULE    := AkToneSource
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkToneSource.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkTremoloFX
include $(CLEAR_VARS)
LOCAL_MODULE    := AkTremoloFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkTremoloFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare AkVorbisDecoder
include $(CLEAR_VARS)
LOCAL_MODULE    := AkVorbisDecoder
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libAkVorbisDecoder.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare CommunicationCentral
include $(CLEAR_VARS)
LOCAL_MODULE    := CommunicationCentral
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libCommunicationCentral.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare McDSPFutzBoxFX
include $(CLEAR_VARS)
LOCAL_MODULE    := McDSPFutzBoxFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libMcDSPFutzBoxFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare McDSPLimiterFX
include $(CLEAR_VARS)
LOCAL_MODULE    := McDSPLimiterFX
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libMcDSPLimiterFX.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare zip
include $(CLEAR_VARS)
LOCAL_MODULE    := zip
LOCAL_SRC_FILES := $(WWISE_LIB_DIR)/android-9_armeabi-v7a/Debug/lib/libzip.a
include $(PREBUILT_STATIC_LIBRARY)

# prepare wwiseSDK
include $(CLEAR_VARS)
LOCAL_ARM_MODE   := arm
LOCAL_STATIC_LIBRARIES += AkMusicEngine \
AkSoundEngine \
AkAudioInputSource \
AkCompressorFX \
AkConvolutionReverbFX \
AkDelayFX \
AkExpanderFX \
AkFlangerFX \
AkGainFX \
AkGuitarDistortionFX \
AkHarmonizerFX \
AkMatrixReverbFX \
AkMemoryMgr \
AkMeterFX \
AkParametricEQFX \
AkPeakLimiterFX \
AkPitchShifterFX \
AkRoomVerbFX \
AkSilenceSource \
AkSynthOne \
AkSineSource \
AkSoundSeedImpactFX \
AkSoundSeedWind \
AkSoundSeedWoosh \
AkStereoDelayFX \
AkStreamMgr \
AkTimeStretchFX \
AkToneSource \
AkTremoloFX \
AkVorbisDecoder \
McDSPFutzBoxFX \
McDSPLimiterFX \
AstoundsoundExpanderFX \
AstoundsoundFolddownFX \
AstoundsoundRTIFX \
AstoundsoundShared

LOCAL_MODULE    := Wwise
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog -lOpenSLES -landroid -lEGL -lGLESv1_CM -lz

LOCAL_SRC_FILES := include/wwise.cpp

LOCAL_CFLAGS := -DLUA_USE_POSIX 

LOCAL_STATIC_LIBRARIES += android_native_app_glue
LOCAL_WHOLE_STATIC_LIBRARIES += gnustl_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)