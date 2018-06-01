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

#ifndef __CCCONFIG_H__
#define __CCCONFIG_H__

#include "platform/CCPlatformConfig.h"

/**
 * @file
 * cocos2d (cc) configuration file.
*/

/** @def CC_ENABLE_STACKABLE_ACTIONS
 * If enabled, actions that alter the position property (eg: MoveBy, JumpBy, BezierBy, etc..) will be stacked.
 * If you run 2 or more 'position' actions at the same time on a node, then end position will be the sum of all the positions.
 * If disabled, only the last run action will take effect.
 * Enabled by default. Disable to be compatible with v2.0 and older versions.
 * @since v2.1
 */
#ifndef CC_ENABLE_STACKABLE_ACTIONS
#define CC_ENABLE_STACKABLE_ACTIONS 1
#endif

/** @def CC_ENABLE_GL_STATE_CACHE
 * If enabled, cocos2d will maintain an OpenGL state cache internally to avoid unnecessary switches.
 * In order to use them, you have to use the following functions, instead of the GL ones:
 *  - ccGLUseProgram() instead of glUseProgram().
 *  - GL::deleteProgram() instead of glDeleteProgram().
 *  - GL::blendFunc() instead of glBlendFunc().

 * If this functionality is disabled, then ccGLUseProgram(), GL::deleteProgram(), GL::blendFunc() will call the GL ones, without using the cache.

 * It is recommended to enable whenever possible to improve speed.
 * If you are migrating your code from GL ES 1.1, then keep it disabled. Once all your code works as expected, turn it on.

 * Default value: Enabled by default

 * @since v2.0.0
 */
#ifndef CC_ENABLE_GL_STATE_CACHE
#define CC_ENABLE_GL_STATE_CACHE 1
#endif

/** @def CC_DIRECTOR_STATS_INTERVAL
 * Seconds between FPS updates.
 * 0.5 seconds, means that the FPS number will be updated every 0.5 seconds.
 * Having a bigger number means a more reliable FPS.

 * Default value: 0.5f
 */
#ifndef CC_DIRECTOR_STATS_INTERVAL
#define CC_DIRECTOR_STATS_INTERVAL (0.5f)
#endif

/** Support PNG or not. If your application don't use png format picture, you can undefine this macro to save package size.
*/
#ifndef CC_USE_PNG
#define CC_USE_PNG  1
#endif // CC_USE_PNG

/** Support JPEG or not. If your application don't use jpeg format picture, you can undefine this macro to save package size.
 */
#ifndef CC_USE_JPEG
#define CC_USE_JPEG  1
#endif // CC_USE_JPEG

/** Support TIFF or not. If your application don't use TIFF format picture, you can undefine this macro to save package size.
 */
#ifndef CC_USE_TIFF
#define CC_USE_TIFF  1
#endif // CC_USE_TIFF

/** @def CC_STRIP_FPS
 * Whether to strip FPS related data and functions, such as cc_fps_images_png
 */
#ifndef CC_STRIP_FPS
#define CC_STRIP_FPS 0
#endif

#endif // __CCCONFIG_H__
