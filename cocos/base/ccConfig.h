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

/** @def CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS
 * If enabled (in conjunction with assertion macros) will verify on Node destruction that the node being destroyed has no event
 * listeners still associated with it in the event dispatcher. This can be used to track down problems where the event dispatch
 * system has dangling pointers to destroyed nodes.
 * Note: event listener verification will always be disabled in builds where assertions are disabled regardless of this setting.
 */
#ifndef CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS
#define CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS 0
#endif

/** @def CC_ENABLE_PROFILERS
 * If enabled, will activate various profilers within cocos2d. This statistical data will be output to the console
 * once per second showing average time (in milliseconds) required to execute the specific routine(s).
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default.
 */
#ifndef CC_ENABLE_PROFILERS
#define CC_ENABLE_PROFILERS 0
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

 /** Support WIC (Windows Image Component) or not. Replaces PNG, TIFF and JPEG
 */
#ifndef CC_USE_WIC
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define CC_USE_WIC  1
#undef CC_USE_TIFF
#undef CC_USE_JPEG
#undef CC_USE_PNG
#endif
#endif // CC_USE_WIC


/** @def CC_CONSTRUCTOR_ACCESS
 * Indicate the init functions access modifier. If value equals to protected, then these functions are protected.
 * If value equals to public, these functions are public,
 * protected by default.
 */
#ifndef CC_CONSTRUCTOR_ACCESS
  //#ifdef CC_ENABLE_SCRIPT_BINDING
    #define CC_CONSTRUCTOR_ACCESS public
  // #else
  //   #define CC_CONSTRUCTOR_ACCESS protected
  // #endif
#endif

#ifndef CC_FILEUTILS_APPLE_ENABLE_OBJC
#define CC_FILEUTILS_APPLE_ENABLE_OBJC  1
#endif

/** @def CC_ENABLE_PREMULTIPLIED_ALPHA
 * If enabled, all textures will be preprocessed to multiply its rgb components
 * by its alpha component.
 */
#ifndef CC_ENABLE_PREMULTIPLIED_ALPHA
# define CC_ENABLE_PREMULTIPLIED_ALPHA 1
#endif

/** @def CC_STRIP_FPS
 * Whether to strip FPS related data and functions, such as cc_fps_images_png
 */
#ifndef CC_STRIP_FPS
#define CC_STRIP_FPS 0
#endif

#endif // __CCCONFIG_H__
