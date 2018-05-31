LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cpp_tests_shared

LOCAL_MODULE_FILENAME := libcpp_tests

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := main.cpp \
    ../../Classes/AppDelegate.cpp \
    ../../Classes/Scene3DTest/Scene3DTest.cpp \
    ../../Classes/TerrainTest/TerrainTest.cpp \
    ../../Classes/VisibleRect.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../../..

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos)
