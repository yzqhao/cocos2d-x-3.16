/****************************************************************************
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2012 		cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "renderer/ccShaders.h"

#define STRINGIFY(A)  #A

NS_CC_BEGIN
//

#include "renderer/shader/ccShader_Position_uColor.frag"

#include "renderer/shader/ccShader_Position_uColor.vert"

//
#include "renderer/shader/ccShader_PositionColor.frag"
#include "renderer/shader/ccShader_PositionColor.vert"

//
#include "renderer/shader/ccShader_PositionColorTextureAsPointsize.vert"

//
#include "renderer/shader/ccShader_PositionTexture.frag"
#include "renderer/shader/ccShader_PositionTexture.vert"

//
#include "renderer/shader/ccShader_PositionTextureA8Color.frag"
#include "renderer/shader/ccShader_PositionTextureA8Color.vert"

//
#include "renderer/shader/ccShader_PositionTextureColor.frag"
#include "renderer/shader/ccShader_PositionTextureColor.vert"

//
#include "renderer/shader/ccShader_PositionTextureColor_noMVP.frag"
#include "renderer/shader/ccShader_PositionTextureColor_noMVP.vert"

//
#include "renderer/shader/ccShader_PositionTextureColorAlphaTest.frag"

//
#include "renderer/shader/ccShader_PositionTexture_uColor.frag"
#include "renderer/shader/ccShader_PositionTexture_uColor.vert"

#include "renderer/shader/ccShader_PositionColorLengthTexture.frag"
#include "renderer/shader/ccShader_PositionColorLengthTexture.vert"

#include "renderer/shader/ccShader_UI_Gray.frag"
//
#include "renderer/shader/ccShader_Label.vert"
#include "renderer/shader/ccShader_Label_df.frag"
#include "renderer/shader/ccShader_Label_df_glow.frag"
#include "renderer/shader/ccShader_Label_normal.frag"
#include "renderer/shader/ccShader_Label_outline.frag"

//
#include "renderer/shader/ccShader_3D_PositionTex.vert"
#include "renderer/shader/ccShader_3D_Color.frag"
#include "renderer/shader/ccShader_3D_ColorTex.frag"
#include "renderer/shader/ccShader_3D_PositionNormalTex.vert"
#include "renderer/shader/ccShader_3D_ColorNormal.frag"
#include "renderer/shader/ccShader_3D_ColorNormalTex.frag"
#include "renderer/shader/ccShader_3D_Particle.vert"
#include "renderer/shader/ccShader_3D_Particle.frag"
#include "renderer/shader/ccShader_3D_Skybox.vert"
#include "renderer/shader/ccShader_3D_Skybox.frag"
#include "renderer/shader/ccShader_3D_Terrain.vert"
#include "renderer/shader/ccShader_3D_Terrain.frag"
#include "renderer/shader/ccShader_CameraClear.vert"
#include "renderer/shader/ccShader_CameraClear.frag"

// ETC1 ALPHA support
#include "renderer/shader/ccShader_ETC1AS_PositionTextureColor.frag"
#include "renderer/shader/ccShader_ETC1AS_PositionTextureGray.frag"

#include "renderer/shader/ccShader_Position.vert"
#include "renderer/shader/ccShader_LayerRadialGradient.frag"

NS_CC_END
