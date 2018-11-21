
#ifndef _BASE_MVP_MANAGER
#define _BASE_MVP_MANAGER

#include "platform/CCPlatformMacros.h"
#include "math/CCMath.h"

#include <vector>
#include <stack>

NS_CC_BEGIN

/**
 * @brief Matrix stack type.
 */
enum class MATRIX_STACK_TYPE
{
    /// Model view matrix stack
    MATRIX_STACK_MODELVIEW,
    
    /// projection matrix stack
    MATRIX_STACK_PROJECTION,
    
    /// texture matrix stack
    MATRIX_STACK_TEXTURE
};

class CC_DLL MVPMatManager
{
public:
    /** 
     * Returns a shared instance of the director. 
     * @js _getInstance
     */
    static MVPMatManager* getInstance();

    /**
     * @js ctor
     */
	MVPMatManager();
    
    /**
     * @js NA
     * @lua NA
     */
    ~MVPMatManager();

    /** 
     * Clones a specified type matrix and put it to the top of specified type of matrix stack.
     * @js NA
     */
    void pushMatrix(MATRIX_STACK_TYPE type);

    /**
     * Clones a projection matrix and put it to the top of projection matrix stack.
     * @param index The index of projection matrix stack.
     * @js NA
     */
    void pushProjectionMatrix(size_t index);

    /** Pops the top matrix of the specified type of matrix stack.
     * @js NA
     */
    void popMatrix(MATRIX_STACK_TYPE type);

    /** Pops the top matrix of the projection matrix stack.
     * @param index The index of projection matrix stack.
     * @js NA
     */
    void popProjectionMatrix(size_t index);

    /** Adds an identity matrix to the top of specified type of matrix stack.
     * @js NA
     */
    void loadIdentityMatrix(MATRIX_STACK_TYPE type);

    /** Adds an identity matrix to the top of projection matrix stack.
     * @param index The index of projection matrix stack.
     * @js NA
     */
    void loadProjectionIdentityMatrix(size_t index);

    /**
     * Adds a matrix to the top of specified type of matrix stack.
     * 
     * @param type Matrix type.
     * @param mat The matrix that to be added.
     * @js NA
     */
    void loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);

    /**
     * Adds a matrix to the top of projection matrix stack.
     *
     * @param mat The matrix that to be added.
     * @param index The index of projection matrix stack.
     * @js NA
     */
    void loadProjectionMatrix(const Mat4& mat, size_t index);

    /**
     * Multiplies a matrix to the top of specified type of matrix stack.
     *
     * @param type Matrix type.
     * @param mat The matrix that to be multiplied.
     * @js NA
     */
    void multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);

    /**
     * Multiplies a matrix to the top of projection matrix stack.
     *
     * @param mat The matrix that to be multiplied.
     * @param index The index of projection matrix stack.
     * @js NA
     */
    void multiplyProjectionMatrix(const Mat4& mat, size_t index);

    /**
     * Gets the top matrix of specified type of matrix stack.
     * @js NA
     */
    const Mat4& getMatrix(MATRIX_STACK_TYPE type) const;

    /**
     * Gets the top matrix of projection matrix stack.
     * @param index The index of projection matrix stack.
     * @js NA
     */
    const Mat4& getProjectionMatrix(size_t index) const;

    /**
     * Clear all types of matrix stack, and add identity matrix to these matrix stacks.
     * @js NA
     */
    void resetMatrixStack();

    /**
     * Init the projection matrix stack.
     * @param stackCount The size of projection matrix stack.
     * @js NA
     */
    void initProjectionMatrixStack(size_t stackCount);

    /**
     * Get the size of projection matrix stack.
     * @js NA
     */
    size_t getProjectionMatrixStackSize();

    void initMatrixStack();

private:

    std::stack<Mat4> _modelViewMatrixStack;
    /** In order to support GL MultiView features, we need to use the matrix array,
        but we don't know the number of MultiView, so using the vector instead.
     */
    std::vector< std::stack<Mat4> > _projectionMatrixStackList;
    std::stack<Mat4> _textureMatrixStack;
};

NS_CC_END

#endif // __CCDIRECTOR_H__
