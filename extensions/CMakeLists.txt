if(WINDOWS AND BUILD_SHARED_LIBS)
  ADD_DEFINITIONS (-D_USREXDLL)
endif()

include_directories(
  ../../extensions
)

set(COCOS_EXTENSIONS_SRC

  ../extensions/GUI/CCScrollView/CCScrollView.cpp
  ../extensions/GUI/CCScrollView/CCTableView.cpp
  ../extensions/GUI/CCScrollView/CCTableViewCell.cpp
  ${PLATFORM_EXTENSIONS_SRC}
)
