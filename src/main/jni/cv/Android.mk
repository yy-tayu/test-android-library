LOCAL_PATH:= $(call my-dir)
PROJECT_PATH:=  $(LOCAL_PATH)/../../../..
include $(CLEAR_VARS)

include $(LOCAL_PATH)/../opencv/Android.mk

LOCAL_MODULE    := libjnativecv
LOCAL_C_INCLUDES := $(PROJECT_PATH)/../common $(PROJECT_PATH)/../deps/opencv/sdk/native/jni/include
LOCAL_SRC_FILES := $(PROJECT_PATH)/../common/jni_cvcommon.cpp jni_jnativecv.cpp nativecv.cpp
LOCAL_CFLAGS := -std=c++11 -Wall  -frtti
LOCAL_CPP_FEATURES += exceptions
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -landroid -llog -lz
LOCAL_MODULE_PATH := $(PROJECT_PATH)/src/main/libs/$(TARGET_ARCH_ABI)
include $(BUILD_SHARED_LIBRARY)
