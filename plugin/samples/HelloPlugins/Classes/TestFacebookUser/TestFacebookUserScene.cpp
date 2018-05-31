/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

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
#include "TestFacebookUserScene.h"
#include "PluginManager.h"
#include "HelloWorldScene.h"
#include "Configs.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

enum {
    TAG_FB_LOGIN = 0,
    TAG_FB_LOGIN_WITH_PERMISSION,
    TAG_FB_LOGOUT,
    TAG_FB_GETUID,
    TAG_FB_GETTOKEN,
    TAG_FB_GETPERMISSIONS,
    TAG_FB_REQUEST_API,
    TAG_FB_PUBLISH_INSTALL,
    TAG_FB_LOG_EVENT,
    TAG_FB_LOG_PURCHASE,
};

struct FBEventMenuItem {
    std::string name;
    int tag;
};

static FBEventMenuItem s_FBMenuItem[] =
{
    {"login",  TAG_FB_LOGIN},
    {"loginWithPermission", TAG_FB_LOGIN_WITH_PERMISSION},
    {"logout", TAG_FB_LOGOUT},
    {"getUid", TAG_FB_GETUID},
    {"getToken", TAG_FB_GETTOKEN},
    {"getPermissions", TAG_FB_GETPERMISSIONS},
    {"request API", TAG_FB_REQUEST_API},
    {"publishInstall",TAG_FB_PUBLISH_INSTALL},
    {"logEvent",TAG_FB_LOG_EVENT},
    {"logPurchase",TAG_FB_LOG_PURCHASE},
};

Scene* TestFacebookUser::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestFacebookUser *layer = TestFacebookUser::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestFacebookUser::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
        return false;
    
    isLogin = false;
    callbackInfo = nullptr;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Point posBR = Point(origin.x + visibleSize.width, origin.y);

    /////////////////////////////
    // 3. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *backItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestFacebookUser::menuBackCallback, this));
    Size backSize = backItem->getContentSize();
    backItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));

    return true;
}

void TestFacebookUser::onExit()
{
    Layer::onExit();
}

void TestFacebookUser::eventMenuCallback(Ref* sender)
{
    
}

void TestFacebookUser::menuBackCallback(Ref* sender)
{
    Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}
