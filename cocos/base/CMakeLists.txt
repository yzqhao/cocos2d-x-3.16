
if(MACOSX OR APPLE)


elseif(ANDROID)
  set(COCOS_BASE_SPECIFIC_SRC
    base/CCController-android.cpp
  )
elseif(LINUX)
  set(COCOS_BASE_SPECIFIC_SRC
    base/CCController-linux-win32.cpp
  )
endif()

set(COCOS_BASE_SRC
  base/CCAsyncTaskPool.cpp
  base/CCAutoreleasePool.cpp
  base/CCConfiguration.cpp
  base/CCConsole.cpp
  base/CCController.cpp
  base/CCData.cpp
  base/CCNinePatchImageParser.cpp
  base/CCDirector.cpp
  base/CCEvent.cpp
  base/CCEventAcceleration.cpp
  base/CCEventController.cpp
  base/CCEventCustom.cpp
  base/CCEventDispatcher.cpp
  base/CCEventKeyboard.cpp
  base/CCEventListener.cpp
  base/CCEventListenerAcceleration.cpp
  base/CCEventListenerController.cpp
  base/CCEventListenerCustom.cpp
  base/CCEventListenerKeyboard.cpp
  base/CCEventListenerMouse.cpp
  base/CCEventListenerTouch.cpp
  base/CCEventMouse.cpp
  base/CCEventTouch.cpp
  base/CCNS.cpp
  base/CCProperties.cpp
  base/CCRef.cpp
  base/CCScheduler.cpp
  base/CCTouch.cpp
  base/CCValue.cpp
  base/CCStencilStateManager.cpp
  base/TGAlib.cpp
  base/ZipUtils.cpp
  base/atitc.cpp
  base/base64.cpp
  base/ccCArray.cpp
  base/ccRandom.cpp
  base/ccTypes.cpp
  base/ccUTF8.cpp
  base/ccUtils.cpp
  base/etc1.cpp
  base/pvr.cpp
  base/s3tc.cpp
  ${COCOS_BASE_SPECIFIC_SRC}

)
