macro (SelectModule)
  set(USE_WEBP_DEFAULT ON)
  if(WINRT OR WP8)
    set(USE_WEBP_DEFAULT OFF)
  endif()

  set(USE_PREBUILT_LIBS_DEFAULT ON)
  if(MINGW)
    set(USE_PREBUILT_LIBS_DEFAULT OFF)
  endif()

  set(BUILD_CPP_EMPTY_TEST_DEFAULT ON)
  set(BUILD_CPP_TESTS_DEFAULT ON)
  set(BUILD_LUA_LIBS_DEFAULT ON)
  set(BUILD_LUA_TESTS_DEFAULT ON)
  set(BUILD_JS_LIBS_DEFAULT ON)
  set(BUILD_JS_TESTS_DEFAULT ON)
  # TODO: fix test samples for MSVC
  if(MSVC)
    set(BUILD_CPP_EMPTY_TEST_DEFAULT OFF)
    set(BUILD_CPP_TESTS_DEFAULT OFF)
    set(BUILD_LUA_LIBS_DEFAULT OFF)
    set(BUILD_LUA_TESTS_DEFAULT OFF)
    set(BUILD_JS_LIBS_DEFAULT OFF)
    set(BUILD_JS_TESTS_DEFAULT OFF)
  endif()

  option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
  option(DEBUG_MODE "Debug or release?" ON)
  option(BUILD_EXTENSIONS "Build extension library" ON)
  option(BUILD_CPP_TESTS "Build TestCpp samples" ${BUILD_CPP_TESTS_DEFAULT})
  option(BUILD_CPP_EMPTY_TEST "Build TestCpp samples" ${BUILD_CPP_EMPTY_TEST_DEFAULT})
  option(USE_PREBUILT_LIBS "Use prebuilt libraries in external directory" ${USE_PREBUILT_LIBS_DEFAULT})
  option(USE_SOURCES_EXTERNAL "Use sources in external directory (automatically ON when USE_PREBUILT_LIBS is ON)" OFF)

  if(USE_PREBUILT_LIBS AND MINGW)
    message(FATAL_ERROR "Prebuilt windows libs can't be used with mingw, please use packages.")
    return()
  endif()

endmacro(SelectModule)