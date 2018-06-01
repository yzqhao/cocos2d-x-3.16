#ifndef TERRAIN_TESH_H
#define TERRAIN_TESH_H

#include "3d/CCSprite3D.h"
#include "3d/CCTerrain.h"
#include "2d/CCCamera.h"

#include "cocos2d.h"
#include "VisibleRect.h"

#define PLAYER_STATE_LEFT 0 
#define PLAYER_STATE_RIGHT 1
#define PLAYER_STATE_IDLE 2
#define PLAYER_STATE_FORWARD 3
#define PLAYER_STATE_BACKWARD 4

class Player : public cocos2d::Sprite3D
{
public:
    static Player * create(const char * file, cocos2d::Camera*  cam, cocos2d::Terrain* terrain);
    virtual bool isDone() const;
    virtual void update(float dt);

    void turnLeft();
    void turnRight();
    void forward();
    void backward();
    void idle();
    cocos2d::Vec3 _targetPos;
    void updateState();
    float _headingAngle;
    cocos2d::Vec3 _headingAxis;
private:
    cocos2d::Terrain* _terrain;
    cocos2d::Camera*  _cam;
    int _playerState;
};


class TerrainWalkThru : public cocos2d::Scene
{
public:
    CREATE_FUNC(TerrainWalkThru);
    TerrainWalkThru();
    virtual std::string title() const ;
    virtual std::string subtitle() const ;
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnd(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
protected:
    cocos2d::Camera*  _camera;
    cocos2d::Terrain* _terrain;
    Player * _player;
};

class TerrainWithLightMap : public cocos2d::Scene
{
public:
    CREATE_FUNC(TerrainWithLightMap);
    TerrainWithLightMap();
    virtual std::string title() const ;
    virtual std::string subtitle() const ;
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
protected:
    cocos2d::Terrain* _terrain;
    cocos2d::Camera* _camera;
};

#endif // !TERRAIN_TESH_H
