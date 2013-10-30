LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/B2DebugDrawLayer.cpp \
                   ../../Classes/Board.cpp \
                   ../../Classes/Cup.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/MainMenuScene.cpp \
                   ../../Classes/Gate.cpp \
                   ../../Classes/GB2ShapeCache-x.cpp \
                   ../../Classes/GLES-Render.cpp \
                   ../../Classes/MenuLevelScene.cpp \
                   ../../Classes/MyContactListener.cpp \
                   ../../Classes/Puck.cpp \
                   ../../Classes/GameWinScene.cpp \
                   ../../Classes/Stick.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dxandroid_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,cocos2dx/platform/android)
