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
#include "TestIAPOnlineScene.h"
#include "PluginManager.h"
#include "AppDelegate.h"
#include "MyIAPOLManager.h"
#include "HelloWorldScene.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

enum {
	TAG_PAY_BY_QH360 = 100,
	TAG_PAY_BY_ND91,
	TAG_PAY_BY_UC,
};

typedef struct tagEventMenuItem {
    std::string id;
    int tag;
}EventMenuItem;

static EventMenuItem s_EventMenuItem[] = {
    {"BtnQH360.png", TAG_PAY_BY_QH360},
	{"BtnND91.png", TAG_PAY_BY_ND91},
#if TEST_UC
	{"BtnUC.png", TAG_PAY_BY_UC},
#endif
};

Scene* TestIAPOnline::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestIAPOnline *layer = TestIAPOnline::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestIAPOnline::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    MyIAPOLManager::getInstance()->loadPlugins();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    auto pEGLView = Director::getInstance()->getOpenGLView();
    Point posBR = Point(pEGLView->getVisibleOrigin().x + pEGLView->getVisibleSize().width, pEGLView->getVisibleOrigin().y);
    Point posTL = Point(pEGLView->getVisibleOrigin().x, pEGLView->getVisibleOrigin().y + pEGLView->getVisibleSize().height);

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestIAPOnline::menuBackCallback, this));
    Size backSize = pBackItem->getContentSize();
    pBackItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));

    return true;
}

void TestIAPOnline::eventMenuCallback(Ref* pSender)
{
    
}

void TestIAPOnline::menuBackCallback(Ref* pSender)
{
	MyIAPOLManager::purge();

	Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}
