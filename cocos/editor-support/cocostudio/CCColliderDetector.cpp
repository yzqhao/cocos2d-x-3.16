/****************************************************************************
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

#include "editor-support/cocostudio/CCColliderDetector.h"
#include "editor-support/cocostudio/CCBone.h"
#include "editor-support/cocostudio/CCTransformHelp.h"



using namespace cocos2d;

namespace cocostudio {


#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
ColliderBody::ColliderBody(ContourData *contourData)
    : _contourData(contourData)
{
    CC_SAFE_RETAIN(_contourData);
}
#endif

ColliderBody::~ColliderBody()
{
    CC_SAFE_RELEASE(_contourData);
}

ColliderDetector *ColliderDetector::create()
{
    ColliderDetector *pColliderDetector = new (std::nothrow) ColliderDetector();
    if (pColliderDetector && pColliderDetector->init())
    {
        pColliderDetector->autorelease();
        return pColliderDetector;
    }
    CC_SAFE_DELETE(pColliderDetector);
    return nullptr;
}

ColliderDetector *ColliderDetector::create(Bone *bone)
{
    ColliderDetector *pColliderDetector = new (std::nothrow) ColliderDetector();
    if (pColliderDetector && pColliderDetector->init(bone))
    {
        pColliderDetector->autorelease();
        return pColliderDetector;
    }
    CC_SAFE_DELETE(pColliderDetector);
    return nullptr;
}

ColliderDetector::ColliderDetector()
    :  _active(false)
{

}

ColliderDetector::~ColliderDetector()
{
    _colliderBodyList.clear();
}

bool ColliderDetector::init()
{
    _colliderBodyList.clear();

    return true;
}

bool ColliderDetector::init(Bone *bone)
{
    init();
    setBone(bone);

    return true;
}

void ColliderDetector::addContourData(ContourData *contourData)
{
    ColliderBody *colliderBody = new (std::nothrow) ColliderBody(contourData);
    _colliderBodyList.pushBack(colliderBody);
    colliderBody->release();


#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    std::vector<Vec2> &calculatedVertexList = colliderBody->_calculatedVertexList;
    
    unsigned long num = contourData->vertexList.size();
    for (unsigned long i = 0; i < num; i++)
    {
        calculatedVertexList.push_back(Vec2());
    }
#endif
}

void ColliderDetector::addContourDataList(cocos2d::Vector<ContourData*> &contourDataList)
{
    for (const auto &contourData : contourDataList)
    {
        this->addContourData(contourData);
    }
}

void ColliderDetector::removeContourData(ContourData *contourData)
{
    std::vector<ColliderBody*> eraseList;
    
    for (const auto &body : _colliderBodyList)
    {
		if (body && body->getContourData() == contourData)
		{
            eraseList.push_back(body);
		}
    }
    
    for (const auto &body : eraseList)
    {
        this->_colliderBodyList.eraseObject(body);
    }
}

void ColliderDetector::removeAll()
{
    _colliderBodyList.clear();
}


void ColliderDetector::setActive(bool active)
{
    if (_active == active)
    {
        return;
    }

    _active = active;
}

bool ColliderDetector::getActive()
{
    return _active;
}

const cocos2d::Vector<ColliderBody*>& ColliderDetector::getColliderBodyList()
{
    return _colliderBodyList;
}

Vec2 helpPoint;

void ColliderDetector::updateTransform(Mat4 &t)
{
    if (!_active)
    {
        return;
    }

    for(auto& object : _colliderBodyList)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;
        ContourData *contourData = colliderBody->getContourData();

        unsigned long num = contourData->vertexList.size();
        std::vector<cocos2d::Vec2> &vs = contourData->vertexList;

#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
        std::vector<cocos2d::Vec2> &cvs = colliderBody->_calculatedVertexList;
#endif

        for (unsigned long i = 0; i < num; i++)
        {
            helpPoint.setPoint( vs.at(i).x,  vs.at(i).y);
            helpPoint = PointApplyTransform(helpPoint, t);


#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
            cvs.at(i).x = helpPoint.x;
            cvs.at(i).y = helpPoint.y;
#endif
        }
    }
}

}
