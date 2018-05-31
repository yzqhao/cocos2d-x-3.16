if(WINDOWS AND BUILD_SHARED_LIBS)
  ADD_DEFINITIONS (-D_USREXDLL)
endif()

include_directories(
  ../../extensions
)
