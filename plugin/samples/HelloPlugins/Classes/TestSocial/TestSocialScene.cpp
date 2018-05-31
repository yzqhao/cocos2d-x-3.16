/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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
#include "TestSocialScene.h"
#include "PluginManager.h"
#include "AppDelegate.h"
#include "MySocialManager.h"
#include "HelloWorldScene.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

const std::string s_aTestCases[] = {
    "Nd91",
};

Scene* TestSocial::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestSocial *layer = TestSocial::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestSocial::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    MySocialManager::getInstance()->loadPlugins();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Point posMid = Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    Point posBR = Point(origin.x + visibleSize.width, origin.y);

    MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestSocial::menuBackCallback, this));
    Size backSize = pBackItem->getContentSize();
    pBackItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));


    return true;
}

void TestSocial::testSubmit(Ref* pSender)
{
    int nIdx = _caseItem->getSelectedIndex();
    MySocialManager::getInstance()->submitScore((MySocialManager::MySocialMode)(nIdx + 1), "0", 30000);
}

void TestSocial::testUnlock(Ref* pSender)
{
    int nIdx = _caseItem->getSelectedIndex();
    TAchievementInfo info;
    info["AchievementID"] = "MyAchiID";
    info["NDDisplayText"] = "Fighter";
    info["NDScore"] = "100";
    MySocialManager::getInstance()->unlockAchievement((MySocialManager::MySocialMode)(nIdx + 1), info);
}

void TestSocial::testLeaderboard(Ref* pSender)
{
    int nIdx = _caseItem->getSelectedIndex();
    MySocialManager::getInstance()->showLeaderboard((MySocialManager::MySocialMode)(nIdx + 1), "0");
}

void TestSocial::testAchievement(Ref* pSender)
{
    int nIdx = _caseItem->getSelectedIndex();
    MySocialManager::getInstance()->showAchievement((MySocialManager::MySocialMode)(nIdx + 1));
}

void TestSocial::menuBackCallback(Ref* pSender)
{
    MySocialManager::purgeManager();
    Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}
