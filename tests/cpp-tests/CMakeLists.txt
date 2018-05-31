set(APP_NAME cpp-tests)

# Use same method as in cocos library
if(LINUX)
  foreach(_pkg FONTCONFIG GTK3)
    cocos_find_package(${_pkg} ${_pkg} REQUIRED)
  endforeach()
endif()
cocos_find_package(FREETYPE FREETYPE REQUIRED)
cocos_find_package(CURL CURL REQUIRED)

if(WIN32)
  set(PLATFORM_SRC proj.win32/main.cpp)
  set(RES_PREFIX "")
elseif(MACOSX)
  set(PLATFORM_SRC proj.mac/main.cpp)

  file(GLOB_RECURSE RES_FILES Resources/*)
  cocos_mark_resources(FILES ${RES_FILES} BASEDIR Resources)
  list(APPEND PLATFORM_SRC ${RES_FILES})

elseif(LINUX)
  set(PLATFORM_SRC proj.linux/main.cpp)
  set(RES_PREFIX "/Resources")
elseif(ANDROID)
  set(PLATFORM_SRC
          Classes/JNITest/JNITest.cpp
          proj.android/jni/main.cpp)
  set(RES_PREFIX "/Resources")
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()

set(TESTS_SRC
  Classes/ActionManagerTest/ActionManagerTest.cpp
  Classes/ActionsTest/ActionsTest.cpp
  Classes/AppDelegate.cpp
  Classes/Scene3DTest/Scene3DTest.cpp
  Classes/TerrainTest/TerrainTest.cpp
  ${PLATFORM_SRC}
)

if(WIN32 OR MACOSX OR LINUX)
  list(APPEND TESTS_SRC
    Classes/WindowTest/WindowTest.cpp
    )
endif()


if(ANDROID)
    IF(CMAKE_BUILD_TYPE MATCHES RELEASE)
        ADD_CUSTOM_COMMAND(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    ENDIF()
else()
endif()

target_link_libraries(${APP_NAME} cocos2d)

if(LINUX)
  foreach(_pkg FONTCONFIG GTK3)
    cocos_use_pkg(${APP_NAME} ${_pkg})
  endforeach()
endif()
foreach(pkg FREETYPE CURL)
  cocos_use_pkg(${APP_NAME} ${pkg})
endforeach()

if(MACOSX OR APPLE)
  set_target_properties(${APP_NAME} PROPERTIES
      MACOSX_BUNDLE 1
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )
ELSEIF(ANDROID)
    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")
    set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${APP_BIN_DIR}")
else()
    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")
    set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${APP_BIN_DIR}")
    
    pre_build(${APP_NAME}
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}${RES_PREFIX}
      )
endif()

