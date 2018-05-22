/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
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

#include "DownloaderTest.h"

#include "../testResource.h"

#include "network/CCDownloader.h"

USING_NS_CC;

static const char* sURLList[] =
{
    "http://www.cocos2d-x.org/attachments/802/cocos2dx_landscape.png",
    "http://www.cocos2d-x.org/docs/manual/framework/native/wiki/logo-resources-of-cocos2d-x/res/2dx_icon_512_rounded.png",
    "http://www.cocos2d-x.org/attachments/1503/no_exist.txt",  // try to download no exist file
    "http://download.sdkbox.com/installer/v1/sdkbox-iap_v2.3.6.1.tar.gz",
};
const static int sListSize = (sizeof(sURLList)/sizeof(sURLList[0]));
static const char* sNameList[sListSize] =
{
    "cocos2dx_landscape.png",
    "2dx_icon_512_rounded.png",
    "inexist file",
    "big file",
};

struct DownloaderTest : public TestCase
{
    CREATE_FUNC(DownloaderTest);
    
    virtual std::string title() const override { return "Downloader Test"; }
    
    std::unique_ptr<network::Downloader> downloader;
    
    DownloaderTest()
    {
        downloader.reset(new network::Downloader());
    }
    
    enum {
        TAG_TITLE = 1,
        TAG_BUTTON,
        TAG_PROGRESS_BAR,
        TAG_STATUS,
        TAG_SPRITE,
    };
    
    virtual void onEnter() override
    {
        TestCase::onEnter();
        _restartTestItem->setVisible(true);
    }
};

DownloaderTests::DownloaderTests()
{
    ADD_TEST_CASE(DownloaderTest);
};
