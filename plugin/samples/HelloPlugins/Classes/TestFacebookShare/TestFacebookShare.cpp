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
#include "TestFacebookShare.h"
#include "PluginManager.h"
#include "HelloWorldScene.h"
#include "Configs.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

enum {
    TAG_FBS_LINK = 0,
    TAG_FBS_OPEN_GRAPH,
    TAG_FBS_PHOTOT,
    TAG_FBS_LINK_MESSAGE,
    TAG_FBS_OPEN_GRAPH_MESSAGE,
    TAG_FBS_PHOTO_MESSAGE,
    TAG_FBS_APP_REQUEST
};

enum {
    TAG_FBSS_SIMPLE_LINK = 0,
    TAG_FBSS_TEXT_LINK,
    TAG_FBSS_PICTURE_LINK,
    TAG_FBSS_MEDIA_LINK,
    TAG_FBSS_INVITES_REQUEST,
    TAG_FBSS_TIE,
    TAG_FBSS_SLOF,
    TAG_FBSS_SRE,
    TAG_FBSS_TBG
};

struct FBShareMenuItem {
    std::string name;
    int tag;
};

static FBShareMenuItem s_FBShareMenuItem[] =
{
    {"Share link",  TAG_FBS_LINK},
    {"Share open graph", TAG_FBS_OPEN_GRAPH},
    {"Share photo", TAG_FBS_PHOTOT},
    {"Link message", TAG_FBS_LINK_MESSAGE},
    {"Open graph message", TAG_FBS_OPEN_GRAPH_MESSAGE},
    {"Photo message", TAG_FBS_PHOTO_MESSAGE},
    {"App request", TAG_FBS_APP_REQUEST}
};

static FBShareMenuItem s_FBS_LinkMenuItem[] =
{
    {"share a simple link", TAG_FBSS_SIMPLE_LINK},
    {"share a Text link", TAG_FBSS_TEXT_LINK},
    {"share a Picture link", TAG_FBSS_PICTURE_LINK},
    {"share a media link", TAG_FBSS_MEDIA_LINK}
};

static FBShareMenuItem s_FBA_RequestMenuItem[] =
{
    {"Invites request", TAG_FBSS_INVITES_REQUEST},
    {"Target invite request", TAG_FBSS_TIE},
    {"specific lists of friends",TAG_FBSS_SLOF},
    {"Sending requests explicitly", TAG_FBSS_SRE},
    {"Turn-based games", TAG_FBSS_TBG},
};

Scene* TestFacebookShare::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestFacebookShare *layer = TestFacebookShare::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestFacebookShare::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
        return false;
    
    tipsLabel = nullptr;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Point posBR = Point(origin.x + visibleSize.width, origin.y);
    

    /////////////////////////////
    // 3. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *backItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestFacebookShare::menuBackCallback, this));
    Size backSize = backItem->getContentSize();
    backItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));

    return true;
}

void TestFacebookShare::onExit()
{
    Layer::onExit();
}

void TestFacebookShare::eventMenuCallback(Ref* sender)
{

}

void TestFacebookShare::menuBackCallback(Ref* sender)
{
    Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}

std::string TestFacebookShare::sceenshot(std::string& filename)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto tex = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888);
    tex->setPosition((origin.x + visibleSize.width) / 2, (origin.y + visibleSize.height) / 2);
    tex->begin();
    Director::getInstance()->getRunningScene()->visit();
    tex->end();
    
    std::string imgPath = FileUtils::getInstance()->getWritablePath();
    if (imgPath.length() == 0) {
        return "";
    }
    
    bool ret = tex->saveToFile(filename, Image::Format::JPG);
    if (ret) {
        imgPath += filename;
        CCLOG("save image to %s", imgPath.c_str());
        return imgPath;
    }
    return "";
}

void TestFacebookShare::showSecondMenu(int menuTag)
{

}

void TestFacebookShare::secondMenuCallback(Ref* sender)
{
    
}