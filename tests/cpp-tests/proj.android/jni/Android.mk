LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cpp_tests_shared

LOCAL_MODULE_FILENAME := libcpp_tests

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := main.cpp \
../../Classes/ActionManagerTest/ActionManagerTest.cpp \
../../Classes/ActionsEaseTest/ActionsEaseTest.cpp \
../../Classes/ActionsProgressTest/ActionsProgressTest.cpp \
../../Classes/ActionsTest/ActionsTest.cpp \
../../Classes/AllocatorTest/AllocatorTest.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/BaseTest.cpp \
../../Classes/BillBoardTest/BillBoardTest.cpp \
../../Classes/BugsTest/Bug-CCDrawNode.cpp \
../../Classes/BugsTest/Bug-1159.cpp \
../../Classes/BugsTest/Bug-1174.cpp \
../../Classes/BugsTest/Bug-350.cpp \
../../Classes/BugsTest/Bug-422.cpp \
../../Classes/BugsTest/Bug-458/Bug-458.cpp \
../../Classes/BugsTest/Bug-458/QuestionContainerSprite.cpp \
../../Classes/BugsTest/Bug-624.cpp \
../../Classes/BugsTest/Bug-886.cpp \
../../Classes/BugsTest/Bug-899.cpp \
../../Classes/BugsTest/Bug-914.cpp \
../../Classes/BugsTest/Bug-12847.cpp \
../../Classes/BugsTest/Bug-15594.cpp \
../../Classes/BugsTest/Bug-15776.cpp \
../../Classes/BugsTest/Bug-Child.cpp \
../../Classes/BugsTest/BugsTest.cpp \
../../Classes/Camera3DTest/Camera3DTest.cpp \
../../Classes/ClickAndMoveTest/ClickAndMoveTest.cpp \
../../Classes/ClippingNodeTest/ClippingNodeTest.cpp \
../../Classes/ConfigurationTest/ConfigurationTest.cpp \
../../Classes/ConsoleTest/ConsoleTest.cpp \
../../Classes/CurlTest/CurlTest.cpp \
../../Classes/CurrentLanguageTest/CurrentLanguageTest.cpp \
../../Classes/DataVisitorTest/DataVisitorTest.cpp \
../../Classes/DownloaderTest/DownloaderTest.cpp \
../../Classes/DrawPrimitivesTest/DrawPrimitivesTest.cpp \
../../Classes/EffectsAdvancedTest/EffectsAdvancedTest.cpp \
../../Classes/EffectsTest/EffectsTest.cpp \
../../Classes/ExtensionsTest/AssetsManagerExTest/AssetsManagerExTest.cpp \
../../Classes/ExtensionsTest/ExtensionsTest.cpp \
../../Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp \
../../Classes/ExtensionsTest/NetworkTest/SocketIOTest.cpp \
../../Classes/ExtensionsTest/NetworkTest/WebSocketTest.cpp \
../../Classes/ExtensionsTest/TableViewTest/CustomTableViewCell.cpp \
../../Classes/ExtensionsTest/TableViewTest/TableViewTestScene.cpp \
../../Classes/FileUtilsTest/FileUtilsTest.cpp \
../../Classes/FontTest/FontTest.cpp \
../../Classes/InputTest/MouseTest.cpp \
../../Classes/IntervalTest/IntervalTest.cpp \
../../Classes/JNITest/JNITest.cpp \
../../Classes/LayerTest/LayerTest.cpp \
../../Classes/LightTest/LightTest.cpp \
../../Classes/MaterialSystemTest/MaterialSystemTest.cpp \
../../Classes/MenuTest/MenuTest.cpp \
../../Classes/MotionStreakTest/MotionStreakTest.cpp \
../../Classes/MultiTouchTest/MultiTouchTest.cpp \
../../Classes/NewEventDispatcherTest/NewEventDispatcherTest.cpp \
../../Classes/NewRendererTest/NewRendererTest.cpp \
../../Classes/NodeTest/NodeTest.cpp \
../../Classes/OpenURLTest/OpenURLTest.cpp \
../../Classes/ParallaxTest/ParallaxTest.cpp \
../../Classes/ReleasePoolTest/ReleasePoolTest.cpp \
../../Classes/RenderTextureTest/RenderTextureTest.cpp \
../../Classes/RotateWorldTest/RotateWorldTest.cpp \
../../Classes/SceneTest/SceneTest.cpp \
../../Classes/SchedulerTest/SchedulerTest.cpp \
../../Classes/ShaderTest/ShaderTest.cpp \
../../Classes/ShaderTest/ShaderTest2.cpp \
../../Classes/SpineTest/SpineTest.cpp \
../../Classes/Scene3DTest/Scene3DTest.cpp \
../../Classes/Sprite3DTest/DrawNode3D.cpp \
../../Classes/Sprite3DTest/Sprite3DTest.cpp \
../../Classes/SpritePolygonTest/SpritePolygonTest.cpp \
../../Classes/TerrainTest/TerrainTest.cpp \
../../Classes/TextInputTest/TextInputTest.cpp \
../../Classes/Texture2dTest/Texture2dTest.cpp \
../../Classes/TextureCacheTest/TextureCacheTest.cpp \
../../Classes/TexturePackerEncryptionTest/TextureAtlasEncryptionTest.cpp \
../../Classes/TileMapTest/TileMapTest.cpp \
../../Classes/TileMapTest/TileMapTest2.cpp \
../../Classes/TouchesTest/Ball.cpp \
../../Classes/TouchesTest/Paddle.cpp \
../../Classes/TouchesTest/TouchesTest.cpp \
../../Classes/TransitionsTest/TransitionsTest.cpp \
../../Classes/UserDefaultTest/UserDefaultTest.cpp \
../../Classes/VisibleRect.cpp \
../../Classes/VibrateTest/VibrateTest.cpp \
../../Classes/ZwoptexTest/ZwoptexTest.cpp \
../../Classes/SpriteFrameCacheTest/SpriteFrameCacheTest.cpp \
../../Classes/controller.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../../..

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos)
