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
#include "TestAnalyticsScene.h"
#include "PluginManager.h"
#include "HelloWorldScene.h"
#include "Configs.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

enum {
    TAG_LOG_EVENT_ID = 0,
    TAG_LOG_EVENT_ID_KV,
    TAG_LOG_ONLINE_CONFIG,
    TAG_LOG_EVENT_ID_DURATION,
    TAG_LOG_EVENT_BEGIN,
    TAG_LOG_EVENT_END,
    TAG_MAKE_ME_CRASH
};

typedef struct tagEventMenuItem {
    std::string id;
    int tag;
}EventMenuItem;

static EventMenuItem s_EventMenuItem[] = {
    {"OnlineConfig",        TAG_LOG_ONLINE_CONFIG},
    {"LogEvent-eventId"   , TAG_LOG_EVENT_ID},
    {"LogEvent-eventId-kv", TAG_LOG_EVENT_ID_KV},
    {"LogEvent-eventId-Duration", TAG_LOG_EVENT_ID_DURATION},
    {"LogEvent-Begin", TAG_LOG_EVENT_BEGIN},
    {"LogEvent-End", TAG_LOG_EVENT_END},
    {"MakeMeCrash", TAG_MAKE_ME_CRASH}
};

Scene* TestAnalytics::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestAnalytics *layer = TestAnalytics::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestAnalytics::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    _pluginAnalytics = NULL;
    loadPlugins();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Point posBR = Point(origin.x + visibleSize.width, origin.y);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestAnalytics::menuBackCallback, this));
    Size backSize = pBackItem->getContentSize();
    pBackItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));

    return true;
}

void TestAnalytics::onExit()
{
    unloadPlugins();
    Layer::onExit();
}

void TestAnalytics::eventMenuCallback(Ref* pSender)
{

}

void TestAnalytics::loadPlugins()
{
    LanguageType langType = Application::getInstance()->getCurrentLanguage();
    
    std::string umengKey  = "";
    std::string flurryKey = "";
    std::string pluginName = "";
    std::string strAppKey = "";
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    umengKey  = UMENG_KEY_IOS;
    flurryKey = FLURRY_KEY_IOS;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    umengKey  = UMENG_KEY_ANDROID;
    flurryKey = FLURRY_KEY_ANDROID;
#endif
    
    if (LanguageType::CHINESE == langType)
    {
        pluginName = "AnalyticsUmeng";
        strAppKey = umengKey;
    }
    else
    {
        pluginName = "AnalyticsFlurry";
        strAppKey = flurryKey;
    }
    
    _pluginAnalytics = dynamic_cast<ProtocolAnalytics*> (PluginManager::getInstance()->loadPlugin(pluginName.c_str()));

    _pluginAnalytics->setDebugMode(true);
    _pluginAnalytics->startSession(strAppKey.c_str());
    _pluginAnalytics->setCaptureUncaughtException(true);
    _pluginAnalytics->setSessionContinueMillis(10000);
    
    const char* sdkVer = _pluginAnalytics->getSDKVersion().c_str();
    log("SDK version : %s", sdkVer);
    
    _pluginAnalytics->callFuncWithParam("updateOnlineConfig", NULL);
    
    PluginParam pParam1(true);
    _pluginAnalytics->callFuncWithParam("setReportLocation", &pParam1, NULL);
    
	_pluginAnalytics->callFuncWithParam("logPageView", NULL);
    
	PluginParam pParam2("1.1");
	_pluginAnalytics->callFuncWithParam("setVersionName", &pParam2, NULL);
    
	PluginParam pParam3(20);
	_pluginAnalytics->callFuncWithParam("setAge", &pParam3, NULL);
    
	PluginParam pParam4(1);
	_pluginAnalytics->callFuncWithParam("setGender", &pParam4, NULL);
    
	PluginParam pParam5("123456");
	_pluginAnalytics->callFuncWithParam("setUserId", &pParam5, NULL);
    
	PluginParam pParam6(false);
	_pluginAnalytics->callFuncWithParam("setUseHttps", &pParam6, NULL);

}

void TestAnalytics::unloadPlugins()
{
    if (NULL != _pluginAnalytics) {
        _pluginAnalytics->stopSession();

        std::string pluginName = _pluginAnalytics->getPluginName();
        PluginManager::getInstance()->unloadPlugin(pluginName.c_str());
        _pluginAnalytics = NULL;
    }
}

void TestAnalytics::menuBackCallback(Ref* pSender)
{
    Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}
