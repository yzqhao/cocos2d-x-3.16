/****************************************************************************
 Copyright (c) 2014-2017 Chukong Technologies Inc.

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

#include "platform/CCPlatformConfig.h"

#include "VibrateTest.h"

using namespace cocos2d;
using namespace cocos2d::ui;

VibrateTests::VibrateTests()
{
    ADD_TEST_CASE(VibrateControlTest);
}

namespace {
    class TextButton : public cocos2d::Label
    {
    public:
        
        static TextButton *create(const std::string& text, const std::function<void(TextButton*)> &onTriggered)
        {
            auto ret = new (std::nothrow) TextButton();
            
            TTFConfig ttfconfig("fonts/arial.ttf",25);
            if (ret && ret->setTTFConfig(ttfconfig)) {
                ret->setString(text);
                ret->_onTriggered = onTriggered;
                
                ret->autorelease();
                
                return ret;
            }
            
            delete ret;
            return nullptr;
        }
        
        void setEnabled(bool enabled)
        {
            _enabled = enabled;
            if(_enabled){
                this->setColor(Color3B::WHITE);
            }
            else {
                this->setColor(Color3B::GRAY);
            }
        }
        
    private:
        TextButton()
        : _enabled(true)
        , _onTriggered(nullptr)
        {
            auto listener = EventListenerTouchOneByOne::create();
            listener->setSwallowTouches(true);
            
            listener->onTouchBegan = CC_CALLBACK_2(TextButton::onTouchBegan, this);
            listener->onTouchEnded = CC_CALLBACK_2(TextButton::onTouchEnded, this);
            listener->onTouchCancelled = CC_CALLBACK_2(TextButton::onTouchCancelled, this);
            
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);            
        }
        
        bool touchHits(Touch  *touch)
        {
            auto hitPos = this->convertToNodeSpace(touch->getLocation());
            if (hitPos.x >= 0 && hitPos.y >= 0 && hitPos.x <= _contentSize.width && hitPos.y <= _contentSize.height) {
                return true;
            }
            return false;
        }
        
        bool onTouchBegan(Touch  *touch, Event  *event)
        {
            auto hits = touchHits(touch);
            if (hits){
                scaleButtonTo(0.95f);
            }
            return hits;
        }
        
        void onTouchEnded(Touch  *touch, Event  *event)
        {
            if(_enabled) {
                auto hits = touchHits(touch);
                if (hits && _onTriggered){
                    _onTriggered(this);
                }
            }
            
            scaleButtonTo(1);
        }
        
        void onTouchCancelled(Touch  *touch, Event  *event)
        {
            scaleButtonTo(1);
        }
        
        void scaleButtonTo(float scale)
        {
            auto action = ScaleTo::create(0.05f, scale);
            action->setTag(10000);
            stopActionByTag(10000);
            runAction(action);
        }
        
        std::function<void(TextButton*)> _onTriggered;
        
        bool _enabled;
    };
}

void VibrateTestDemo::onExit()
{
    TestCase::onExit();
}

std::string VibrateTestDemo::title() const
{
    return "Vibrate Test";
}

// VibrateControlTest
bool VibrateControlTest::init()
{
    auto ret = VibrateTestDemo::init();
    _duration = 0.1f;
    
    std::string fontFilePath = "fonts/arial.ttf";
    
    auto& layerSize = this->getContentSize();

    auto vibrateItem = TextButton::create("vibrate", [&](TextButton* button){
        Device::vibrate(_duration);
    });
    vibrateItem->setPosition(layerSize.width * 0.5f, layerSize.height * 0.7f);
    addChild(vibrateItem);
    
    auto durationLabelValue = StringUtils::format("duration: %.3fs", _duration);

    auto durationLabel = Label::createWithTTF(durationLabelValue, fontFilePath, 20);
    durationLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    durationLabel->setPosition(layerSize.width * 0.5f, layerSize.height * 0.5f);
    addChild(durationLabel);
    _durationLabel = durationLabel;
        
    return ret;
}

VibrateControlTest::~VibrateControlTest()
{
}

std::string VibrateControlTest::title() const
{
    return "vibrate control test";
}
