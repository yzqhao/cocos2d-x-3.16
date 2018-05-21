﻿/****************************************************************************
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

#ifndef __CCCOLLIDERDETECTOR_H__
#define __CCCOLLIDERDETECTOR_H__

#include "editor-support/cocostudio/CCArmatureDefine.h"
#include "editor-support/cocostudio/CCDatas.h"
#include "editor-support/cocostudio/CocosStudioExport.h"

#ifndef PT_RATIO
#define PT_RATIO 32
#endif

namespace cocostudio {

class Bone;

/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL ColliderFilter
{
public:
    virtual ~ColliderFilter() { }
};

class CC_STUDIO_DLL ColliderBody : public cocos2d::Ref
{
public:
    ColliderBody(ContourData *contourData);
    ~ColliderBody();

    inline ContourData *getContourData() { return _contourData; }

#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    virtual const std::vector<cocos2d::Vec2> &getCalculatedVertexList() const { return _calculatedVertexList; }
#endif

private:

#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    std::vector<cocos2d::Vec2> _calculatedVertexList;
#endif

    ContourData *_contourData;

    friend class ColliderDetector;
};

/*
 *  @brief  ContourSprite used to draw the contour of the display
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL ColliderDetector : public cocos2d::Ref
{
public:
    static ColliderDetector *create();
    static ColliderDetector *create(Bone *bone);
public:
    /**
     * @js ctor
     */
    ColliderDetector();
    /**
     * @js NA
     * @lua NA
     */
    ~ColliderDetector(void);

    virtual bool init();
    virtual bool init(Bone *bone);

    void addContourData(ContourData *contourData);
    void addContourDataList(cocos2d::Vector<ContourData*> &contourDataList);

    void removeContourData(ContourData *contourData);
    void removeAll();

    void updateTransform(cocos2d::Mat4 &t);

    void setActive(bool active);
    bool getActive();

    const cocos2d::Vector<ColliderBody*>& getColliderBodyList();

    virtual void setBone(Bone *bone) { _bone = bone; }
    virtual Bone *getBone() const { return _bone; }

 protected:
    cocos2d::Vector<ColliderBody*> _colliderBodyList;

    Bone *_bone;

protected:
    bool _active;
};

}

#endif /*__CCCOLLIDERDETECTOR_H__*/
