/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __BASE_CCMACROS_H__
#define __BASE_CCMACROS_H__

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "base/CCConsole.h"
#include "platform/CCStdC.h"

#ifndef CCASSERT
#if COCOS2D_DEBUG > 0
    #define CCASSERT(cond, msg) CC_ASSERT(cond)
#else
    #define CCASSERT(cond, msg)
#endif

#define GP_ASSERT(cond) CCASSERT(cond, "")

// FIXME:: Backward compatible
#define CCAssert CCASSERT
#endif  // CCASSERT

#include "base/ccConfig.h"
#include "base/ccRandom.h"

/** @def CCRANDOM_0_1
 returns a random float between 0 and 1
 */
#define CCRANDOM_0_1() cocos2d::rand_0_1()

/** @def CC_DEGREES_TO_RADIANS
 converts degrees to radians
 */
#define CC_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180

/** @def CC_RADIANS_TO_DEGREES
 converts radians to degrees
 */
#define CC_RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f) // PI * 180

#define CC_REPEAT_FOREVER (UINT_MAX -1)

/** @def CC_BLEND_SRC
default gl blend src function. Compatible with premultiplied alpha images.
*/
#define CC_BLEND_SRC GL_ONE
#define CC_BLEND_DST GL_ONE_MINUS_SRC_ALPHA

/** @def CC_CONTENT_SCALE_FACTOR
On Mac it returns 1;
On iPhone it returns 2 if RetinaDisplay is On. Otherwise it returns 1
*/
#define CC_CONTENT_SCALE_FACTOR() cocos2d::Director::getInstance()->getContentScaleFactor()

/****************************/
/** RETINA DISPLAY ENABLED **/
/****************************/

/** @def CC_RECT_PIXELS_TO_POINTS
 Converts a rect in pixels to points
 */
#define CC_RECT_PIXELS_TO_POINTS(__rect_in_pixels__)                                                                        \
    cocos2d::Rect( (__rect_in_pixels__).origin.x / CC_CONTENT_SCALE_FACTOR(), (__rect_in_pixels__).origin.y / CC_CONTENT_SCALE_FACTOR(),    \
            (__rect_in_pixels__).size.width / CC_CONTENT_SCALE_FACTOR(), (__rect_in_pixels__).size.height / CC_CONTENT_SCALE_FACTOR() )

/** @def CC_RECT_POINTS_TO_PIXELS
 Converts a rect in points to pixels
 */
#define CC_RECT_POINTS_TO_PIXELS(__rect_in_points_points__)                                                                        \
    cocos2d::Rect( (__rect_in_points_points__).origin.x * CC_CONTENT_SCALE_FACTOR(), (__rect_in_points_points__).origin.y * CC_CONTENT_SCALE_FACTOR(),    \
            (__rect_in_points_points__).size.width * CC_CONTENT_SCALE_FACTOR(), (__rect_in_points_points__).size.height * CC_CONTENT_SCALE_FACTOR() )

/** @def CC_POINT_PIXELS_TO_POINTS
 Converts a rect in pixels to points
 */
#define CC_POINT_PIXELS_TO_POINTS(__pixels__)                                                                        \
cocos2d::Vec2( (__pixels__).x / CC_CONTENT_SCALE_FACTOR(), (__pixels__).y / CC_CONTENT_SCALE_FACTOR())

/** @def CC_POINT_POINTS_TO_PIXELS
 Converts a rect in points to pixels
 */
#define CC_POINT_POINTS_TO_PIXELS(__points__)                                                                        \
cocos2d::Vec2( (__points__).x * CC_CONTENT_SCALE_FACTOR(), (__points__).y * CC_CONTENT_SCALE_FACTOR())

/** @def CC_POINT_PIXELS_TO_POINTS
 Converts a rect in pixels to points
 */
#define CC_SIZE_PIXELS_TO_POINTS(__size_in_pixels__)                                                                        \
cocos2d::Size( (__size_in_pixels__).width / CC_CONTENT_SCALE_FACTOR(), (__size_in_pixels__).height / CC_CONTENT_SCALE_FACTOR())

/** @def CC_POINT_POINTS_TO_PIXELS
 Converts a rect in points to pixels
 */
#define CC_SIZE_POINTS_TO_PIXELS(__size_in_points__)                                                                        \
cocos2d::Size( (__size_in_points__).width * CC_CONTENT_SCALE_FACTOR(), (__size_in_points__).height * CC_CONTENT_SCALE_FACTOR())


#ifndef FLT_EPSILON
#define FLT_EPSILON     1.192092896e-07F
#endif // FLT_EPSILON

/**
Helper macros which converts 4-byte little/big endian 
integral number to the machine native number representation
 
It should work same as apples CFSwapInt32LittleToHost(..)
*/

/// when define returns true it means that our architecture uses big endian
#define CC_HOST_IS_BIG_ENDIAN (bool)(*(unsigned short *)"\0\xff" < 0x100) 
#define CC_SWAP32(i)  ((i & 0x000000ff) << 24 | (i & 0x0000ff00) << 8 | (i & 0x00ff0000) >> 8 | (i & 0xff000000) >> 24)
#define CC_SWAP16(i)  ((i & 0x00ff) << 8 | (i &0xff00) >> 8)   
#define CC_SWAP_INT32_LITTLE_TO_HOST(i) ((CC_HOST_IS_BIG_ENDIAN == true)? CC_SWAP32(i) : (i) )
#define CC_SWAP_INT16_LITTLE_TO_HOST(i) ((CC_HOST_IS_BIG_ENDIAN == true)? CC_SWAP16(i) : (i) )
#define CC_SWAP_INT32_BIG_TO_HOST(i)    ((CC_HOST_IS_BIG_ENDIAN == true)? (i) : CC_SWAP32(i) )
#define CC_SWAP_INT16_BIG_TO_HOST(i)    ((CC_HOST_IS_BIG_ENDIAN == true)? (i):  CC_SWAP16(i) )

#if !defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0
#define CHECK_GL_ERROR_DEBUG()
#else
#define CHECK_GL_ERROR_DEBUG() \
    do { \
        GLenum __error = glGetError(); \
        if(__error) { \
            cocos2d::log("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
        } \
    } while (false)
#endif

 /*********************************/
 /** 64bits Program Sense Macros **/
 /*********************************/
#if defined(_M_X64) || defined(_WIN64) || defined(__LP64__) || defined(_LP64) || defined(__x86_64)
#define CC_64BITS 1
#else
#define CC_64BITS 0
#endif


/** @def CC_INCREMENT_GL_DRAWS_BY_ONE
 Increments the GL Draws counts by one.
 The number of calls per frame are displayed on the screen when the Director's stats are enabled.
 */
#define CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(__drawcalls__, __vertices__) \
    do {                                                                \
        auto __renderer__ = cocos2d::Director::getInstance()->getRenderer();     \
        __renderer__->addDrawnBatches(__drawcalls__);                   \
        __renderer__->addDrawnVertices(__vertices__);                   \
    } while(0)

/*******************/
/** Notifications **/
/*******************/
/** @def AnimationFrameDisplayedNotification
 Notification name when a SpriteFrame is displayed
 */
#define AnimationFrameDisplayedNotification "CCAnimationFrameDisplayedNotification"

/*******************/
/** Notifications **/
/*******************/
/** @def Animate3DDisplayedNotification
 Notification name when a frame in Animate3D is played
 */
#define Animate3DDisplayedNotification "CCAnimate3DDisplayedNotification"

// new callbacks based on C++11
#define CC_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CC_CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CC_CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CC_CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

#endif // __BASE_CCMACROS_H__
