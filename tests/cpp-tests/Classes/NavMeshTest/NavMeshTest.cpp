/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "NavMeshTest.h"
#include "physics3d/CCPhysics3DWorld.h"
#include "physics3d/CCPhysics3D.h"
#include "3d/CCBundle3D.h"
#include "2d/CCLight.h"

USING_NS_CC_EXT;
USING_NS_CC;

struct AgentUserData
{
    float time;
};

NavMeshTests::NavMeshTests()
{
};

NavMeshBaseTestDemo::NavMeshBaseTestDemo(void)
    : _camera(nullptr)
    , _needMoveAgents(false)
{

}

NavMeshBaseTestDemo::~NavMeshBaseTestDemo(void)
{
    for (auto iter : _agents){
        AgentUserData *data = static_cast<AgentUserData *>(iter.first->getUserData());
        delete data;
    }
}

bool NavMeshBaseTestDemo::init()
{
    if (!TestCase::init()) return false;

    _angle = 0.0f;

    Size size = Director::getInstance()->getWinSize();
    _camera = Camera::createPerspective(30.0f, size.width / size.height, 1.0f, 1000.0f);
    _camera->setPosition3D(Vec3(0.0f, 50.0f, 100.0f));
    _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    _camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(_camera);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(NavMeshBaseTestDemo::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(NavMeshBaseTestDemo::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(NavMeshBaseTestDemo::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    initScene();
    scheduleUpdate();



    return true;
}

void NavMeshBaseTestDemo::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    _needMoveAgents = true;
    touchesBegan(touches, event);
}

void NavMeshBaseTestDemo::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    if (touches.size() && _camera)
    {
        auto touch = touches[0];
        auto delta = touch->getDelta();

        _angle -= CC_DEGREES_TO_RADIANS(delta.x);
        _camera->setPosition3D(Vec3(100.0f * sinf(_angle), 50.0f, 100.0f * cosf(_angle)));
        _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

        if (delta.lengthSquared() > 16)
        {
            _needMoveAgents = false;
        }
    }
    touchesMoved(touches, event);
}

void NavMeshBaseTestDemo::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    touchesEnded(touches, event);
}

void NavMeshBaseTestDemo::initScene()
{
    
}

void NavMeshBaseTestDemo::createAgent(const Vec3 &pos)
{
    std::string filePath = "Sprite3DTest/girl.c3b";
    NavMeshAgentParam param;
    param.radius = 2.0f;
    param.height = 8.0f;
    param.maxSpeed = 8.0f;
    auto agent = NavMeshAgent::create(param);
    auto agentNode = Sprite3D::create(filePath);
    agent->setOrientationRefAxes(Vec3(-1.0f, 0.0f, 1.0f));
    AgentUserData *data = new AgentUserData{ 0.0f };
    agent->setUserData(data);
    agentNode->setScale(0.05f);
    agentNode->addComponent(agent);

    auto node = Node::create();
    node->addChild(agentNode);
    node->setPosition3D(pos);
    node->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(node);


    auto animation = Animation3D::create(filePath);
    auto animate = Animate3D::create(animation);
    if (animate){
        agentNode->runAction(RepeatForever::create(animate));
        animate->setSpeed(0);
    }

    _agents.push_back(std::make_pair(agent, animate));
}

void NavMeshBaseTestDemo::createObstacle(const Vec3 &pos)
{
    auto obstacle = NavMeshObstacle::create(2.0f, 8.0f);
    auto obstacleNode = Sprite3D::create("Sprite3DTest/cylinder.c3b");
    obstacleNode->setPosition3D(pos + Vec3(0.0f, -0.5f, 0.0f));
    obstacleNode->setRotation3D(Vec3(-90.0f, 0.0f, 0.0f));
    obstacleNode->setScale(0.3f);
    obstacleNode->addComponent(obstacle);
    obstacleNode->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(obstacleNode);
}

Vec3 jump(const Vec3* pV1, const Vec3* pV2, float height, float t)
{
    Vec3 pOut;
    pOut.x = pV1->x + t * (pV2->x - pV1->x);
    pOut.y = pV1->y + t * (pV2->y - pV1->y);
    pOut.z = pV1->z + t * (pV2->z - pV1->z);
    pOut.y += height * sinf(M_PI * t);
    return pOut;
}

void NavMeshBaseTestDemo::moveAgents(const cocos2d::Vec3 &des)
{
    for (auto iter : _agents){
        NavMeshAgent::MoveCallback callback = [](NavMeshAgent *agent, float totalTimeAfterMove){
            AgentUserData *data = static_cast<AgentUserData *>(agent->getUserData());
            if (agent->isOnOffMeshLink()){
                agent->setAutoTraverseOffMeshLink(false);
                agent->setAutoOrientation(false);
                OffMeshLinkData linkdata = agent->getCurrentOffMeshLinkData();

                agent->getOwner()->setPosition3D(jump(&linkdata.startPosition, &linkdata.endPosition, 10.0f, data->time));
                Vec3 dir = linkdata.endPosition - linkdata.startPosition;
                dir.y = 0.0f;
                dir.normalize();
                Vec3 axes;
                Vec3 refAxes = Vec3(-1.0f, 0.0f, 1.0f);
                refAxes.normalize();
                Vec3::cross(refAxes, dir, &axes);
                float angle = Vec3::dot(refAxes, dir);
                agent->getOwner()->setRotationQuat(Quaternion(axes, acosf(angle)));
                data->time += 0.01f;
                if (1.0f < data->time){
                    agent->completeOffMeshLink();
                    agent->setAutoOrientation(true);
                    data->time = 0.0f;
                }
            }
        };
        iter.first->move(des, callback);
    }
}

void NavMeshBaseTestDemo::update(float delta)
{
    for (auto iter : _agents){
        float speed = iter.first->getCurrentVelocity().length() * 0.2;
        iter.second->setSpeed(0.0f < speed ? speed : 0.0f);
    }
}

NavMeshBasicTestDemo::NavMeshBasicTestDemo(void)
{

}

NavMeshBasicTestDemo::~NavMeshBasicTestDemo(void)
{
}

std::string NavMeshBasicTestDemo::title() const
{
    return "Navigation Mesh Test";
}

std::string NavMeshBasicTestDemo::subtitle() const
{
    return "Basic Test";
}

void NavMeshBasicTestDemo::touchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{

}

bool NavMeshBasicTestDemo::init()
{
    if (!NavMeshBaseTestDemo::init()) return false;

    TTFConfig ttfConfig("fonts/arial.ttf", 15);
    _debugLabel = Label::createWithTTF(ttfConfig, "Debug Draw ON");
    _debugLabel->retain();
    auto menuItem1 = MenuItemLabel::create(_debugLabel, [=](Ref*){
        bool enabledDebug = !getNavMesh()->isDebugDrawEnabled();
        getNavMesh()->setDebugDrawEnable(enabledDebug);
        if (enabledDebug){
            _debugLabel->setString("Debug Draw ON");
        }
        else{
            _debugLabel->setString("Debug Draw OFF");
        }
    });
    menuItem1->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    menuItem1->setPosition(Vec2(VisibleRect::left().x, VisibleRect::top().y - 100));
    auto menu = Menu::create(menuItem1, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);

    return true;
}

void NavMeshBasicTestDemo::onEnter()
{
    NavMeshBaseTestDemo::onEnter();
}

NavMeshAdvanceTestDemo::NavMeshAdvanceTestDemo(void)
{

}

NavMeshAdvanceTestDemo::~NavMeshAdvanceTestDemo(void)
{

}

bool NavMeshAdvanceTestDemo::init()
{
    return true;
}

void NavMeshAdvanceTestDemo::onEnter()
{
    NavMeshBaseTestDemo::onEnter();
}

std::string NavMeshAdvanceTestDemo::title() const
{
    return "Navigation Mesh Test";
}

std::string NavMeshAdvanceTestDemo::subtitle() const
{
    return "Advance Test";
}

void NavMeshAdvanceTestDemo::touchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{

}

