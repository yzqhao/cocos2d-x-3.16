LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_extension_static

LOCAL_MODULE_FILENAME := libextension

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := 

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static

LOCAL_CXXFLAGS += -fexceptions

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/. \
                           $(LOCAL_PATH)/.. 
                    
include $(BUILD_STATIC_LIBRARY)
