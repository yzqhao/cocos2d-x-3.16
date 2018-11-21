
#include "base/MVPMatManager.h"

NS_CC_BEGIN
// FIXME: it should be a MVPMatManager ivar. Move it there once support for multiple directors is added

// singleton stuff
static MVPMatManager *s_MVPMatManager = nullptr;

MVPMatManager* MVPMatManager::getInstance()
{
    if (!s_MVPMatManager)
    {
		s_MVPMatManager = new (std::nothrow) MVPMatManager;
    }

    return s_MVPMatManager;
}

MVPMatManager::MVPMatManager()
{
}

MVPMatManager::~MVPMatManager(void)
{
	s_MVPMatManager = nullptr;
}

//
// FIXME TODO
// Matrix code MUST NOT be part of the MVPMatManager
// MUST BE moved outside.
// Why the MVPMatManager must have this code ?
//
void MVPMatManager::initMatrixStack()
{
    while (!_modelViewMatrixStack.empty())
    {
        _modelViewMatrixStack.pop();
    }

    _projectionMatrixStackList.clear();

    while (!_textureMatrixStack.empty())
    {
        _textureMatrixStack.pop();
    }

    _modelViewMatrixStack.push(Mat4::IDENTITY);
    std::stack<Mat4> projectionMatrixStack;
    projectionMatrixStack.push(Mat4::IDENTITY);
    _projectionMatrixStackList.push_back(projectionMatrixStack);
    _textureMatrixStack.push(Mat4::IDENTITY);
}

void MVPMatManager::resetMatrixStack()
{
    initMatrixStack();
}

void MVPMatManager::initProjectionMatrixStack(size_t stackCount)
{
    _projectionMatrixStackList.clear();
    std::stack<Mat4> projectionMatrixStack;
    projectionMatrixStack.push(Mat4::IDENTITY);
    for (size_t i = 0; i < stackCount; ++i)
        _projectionMatrixStackList.push_back(projectionMatrixStack);
}

size_t MVPMatManager::getProjectionMatrixStackSize()
{
    return _projectionMatrixStackList.size();
}

void MVPMatManager::popMatrix(MATRIX_STACK_TYPE type)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _modelViewMatrixStack.pop();
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStackList[0].pop();
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.pop();
    }
    else
    {
        CCASSERT(false, "unknown matrix stack type");
    }
}

void MVPMatManager::popProjectionMatrix(size_t index)
{
    _projectionMatrixStackList[index].pop();
}

void MVPMatManager::loadIdentityMatrix(MATRIX_STACK_TYPE type)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _modelViewMatrixStack.top() = Mat4::IDENTITY;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStackList[0].top() = Mat4::IDENTITY;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.top() = Mat4::IDENTITY;
    }
    else
    {
        CCASSERT(false, "unknown matrix stack type");
    }
}

void MVPMatManager::loadProjectionIdentityMatrix(size_t index)
{
    _projectionMatrixStackList[index].top() = Mat4::IDENTITY;
}

void MVPMatManager::loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _modelViewMatrixStack.top() = mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStackList[0].top() = mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.top() = mat;
    }
    else
    {
        CCASSERT(false, "unknown matrix stack type");
    }
}

void MVPMatManager::loadProjectionMatrix(const Mat4& mat, size_t index)
{
    _projectionMatrixStackList[index].top() = mat;
}

void MVPMatManager::multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _modelViewMatrixStack.top() *= mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStackList[0].top() *= mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.top() *= mat;
    }
    else
    {
        CCASSERT(false, "unknown matrix stack type");
    }
}

void MVPMatManager::multiplyProjectionMatrix(const Mat4& mat, size_t index)
{
    _projectionMatrixStackList[index].top() *= mat;
}

void MVPMatManager::pushMatrix(MATRIX_STACK_TYPE type)
{
    if(type == MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW)
    {
        _modelViewMatrixStack.push(_modelViewMatrixStack.top());
    }
    else if(type == MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION)
    {
        _projectionMatrixStackList[0].push(_projectionMatrixStackList[0].top());
    }
    else if(type == MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE)
    {
        _textureMatrixStack.push(_textureMatrixStack.top());
    }
    else
    {
        CCASSERT(false, "unknown matrix stack type");
    }
}

void MVPMatManager::pushProjectionMatrix(size_t index)
{
    _projectionMatrixStackList[index].push(_projectionMatrixStackList[index].top());
}

const Mat4& MVPMatManager::getMatrix(MATRIX_STACK_TYPE type) const
{
    if(type == MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW)
    {
        return _modelViewMatrixStack.top();
    }
    else if(type == MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION)
    {
        return _projectionMatrixStackList[0].top();
    }
    else if(type == MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE)
    {
        return _textureMatrixStack.top();
    }

    CCASSERT(false, "unknown matrix stack type, will return modelview matrix instead");
    return  _modelViewMatrixStack.top();
}

const Mat4& MVPMatManager::getProjectionMatrix(size_t index) const
{
    return _projectionMatrixStackList[index].top();
}

NS_CC_END

