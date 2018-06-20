include_directories(
  ../external/ConvertUTF
  ../external/poly2tri
  ../external/poly2tri/common
  ../external/poly2tri/sweep
)

set(COCOS_2D_SRC

  2d/CCCamera.cpp
  2d/CCCameraBackgroundBrush.cpp
  2d/CCLayer.cpp
  2d/CCLight.cpp
  2d/CCNode.cpp
  2d/CCScene.cpp
  2d/CCSprite.cpp
  2d/CCSpriteFrameCache.cpp
  2d/CCSpriteFrame.cpp
  2d/CCAutoPolygon.cpp
  ../external/clipper/clipper.cpp

)
