/****************************************************************************
 Copyright (c) 2015-2017 Chukong Technologies Inc.

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

 Ideas taken from:
 - GamePlay3D: http://gameplay3d.org/
 - OGRE3D: http://www.ogre3d.org/
 - Qt3D: http://qt-project.org/
 ****************************************************************************/

#include "renderer/CCPass.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCTexture2D.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCVertexAttribBinding.h"

#include "base/ccTypes.h"
#include "2d/CCNode.h"

#include <xxhash.h>

NS_CC_BEGIN


Pass* Pass::create()
{
    auto pass = new (std::nothrow) Pass();
    if (pass && pass->init())
    {
        pass->autorelease();
        return pass;
    }
    CC_SAFE_DELETE(pass);
    return nullptr;
}

Pass* Pass::createWithGLProgramState(GLProgramState* programState)
{
    auto pass = new (std::nothrow) Pass();
    if (pass && pass->initWithGLProgramState(programState))
    {
        pass->autorelease();
        return pass;
    }
    CC_SAFE_DELETE(pass);
    return nullptr;
}

bool Pass::init()
{
    return true;
}

bool Pass::initWithGLProgramState(GLProgramState *glProgramState)
{
    _glProgramState = glProgramState;
    CC_SAFE_RETAIN(_glProgramState);
    return true;
}

Pass::Pass()
: _glProgramState(nullptr)
, _vertexAttribBinding(nullptr)
{
}

Pass::~Pass()
{
    CC_SAFE_RELEASE(_glProgramState);
    CC_SAFE_RELEASE(_vertexAttribBinding);
}

Pass* Pass::clone() const
{
    auto pass = new (std::nothrow) Pass();
    if (pass)
    {
        RenderState::cloneInto(pass);

        pass->_glProgramState = _glProgramState->clone();
        CC_SAFE_RETAIN(pass->_glProgramState);

        pass->_vertexAttribBinding = _vertexAttribBinding;
        CC_SAFE_RETAIN(pass->_vertexAttribBinding);

        pass->autorelease();
    }
    return pass;
}

GLProgramState* Pass::getGLProgramState() const
{
    return _glProgramState;
}

void Pass::setGLProgramState(GLProgramState* glProgramState)
{
    if ( _glProgramState != glProgramState) {
        CC_SAFE_RELEASE(_glProgramState);
        _glProgramState = glProgramState;
        CC_SAFE_RETAIN(_glProgramState);
    }
}

uint32_t Pass::getHash() const
{
    uint32_t glProgram = (uint32_t)_glProgramState->getGLProgram()->getProgram();
    uint32_t textureid = _texture ? _texture->getName() : -1;
    uint32_t stateblockid = _state->getHash();

    _hash = glProgram ^ textureid ^ stateblockid;

    return _hash;
}

void Pass::bind(const Mat4& modelView)
{
    bind(modelView, true);
}

void Pass::bind(const Mat4& modelView, bool bindAttributes)
{

    // vertex attribs
    if (bindAttributes && _vertexAttribBinding)
        _vertexAttribBinding->bind();

    _glProgramState->applyGLProgram(modelView);
    _glProgramState->applyUniforms();

    //set render state
    if (_texture)
        GL::bindTexture2D(_texture->getName());

    // Get the combined modified state bits for our RenderState hierarchy.
    long stateOverrideBits = _state ? _state->_bits : 0;
    RenderState* rs = _parent;
    while (rs)
    {
        if (rs->_state)
        {
            stateOverrideBits |= rs->_state->_bits;
        }
        rs = rs->_parent;
    }

    // Restore renderer state to its default, except for explicitly specified states
    StateBlock::restore(stateOverrideBits);

    // Apply renderer state for the entire hierarchy, top-down.
    rs = nullptr;
    while ((rs = getTopmost(rs)))
    {
        if (rs->_state)
        {
            rs->_state->bindNoRestore();
        }
    }
}

void Pass::unbind()
{
    RenderState::StateBlock::restore(0);

    _vertexAttribBinding->unbind();
}

void Pass::setVertexAttribBinding(VertexAttribBinding* binding)
{
    if (_vertexAttribBinding != binding)
    {
        CC_SAFE_RELEASE(_vertexAttribBinding);
        _vertexAttribBinding = binding;
        CC_SAFE_RETAIN(_vertexAttribBinding);
    }
}

VertexAttribBinding* Pass::getVertexAttributeBinding() const
{
    return _vertexAttribBinding;
}


NS_CC_END
