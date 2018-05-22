#include "Scene3DTest.h"

#include "renderer/CCRenderState.h"
#include <spine/spine-cocos2dx.h>

#include "../testResource.h"
#include "../TerrainTest/TerrainTest.h"

USING_NS_CC;
using namespace spine;

class SkeletonAnimationCullingFix : public SkeletonAnimation
{
public:
    SkeletonAnimationCullingFix()
    : SkeletonAnimation()
    {}
    
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) override
    {
        glDisable(GL_CULL_FACE);
        SkeletonAnimation::draw(renderer, transform, transformFlags);
        RenderState::StateBlock::invalidate(cocos2d::RenderState::StateBlock::RS_ALL_ONES);
    }
    
    static SkeletonAnimationCullingFix* createWithFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1)
    {
        SkeletonAnimationCullingFix* node = new SkeletonAnimationCullingFix();
        spAtlas* atlas = spAtlas_createFromFile(atlasFile.c_str(), 0);
        node->initWithJsonFile(skeletonDataFile, atlas, scale);
        node->autorelease();
        return node;
    }
};

////////////////////////////////////////////////////////////////////////////////
// Declare Scene3DTestScene

/** Scene3DTestScene designed for test 2D-3D mixed render for common 3D game usage.
 *
 *  Scene has three logic sub scenes:
 *  -   World scene for maintain 3D game world objects, there are two cameras in this
 *      scene, one for skybox, another for other 3D models.
 *  -   UI scene, the root scene, maintain a menu in main UI.
 *  -   Dialog scene maintain two dialogs, which has 3D models on it and another
 *      2D elements above on 3D models, there are three cameras for them.
 *  -   OSD scene, maintain the UI element, like the description dialog, above
 *  -   on other elements.
 */
class Scene3DTestScene : public TestCase
{
public:
    CREATE_FUNC(Scene3DTestScene);
    
    bool onTouchBegan(Touch* touch, Event* event) { return true; }
    void onTouchEnd(Touch*, Event*);
    
private:
    Scene3DTestScene();
    virtual ~Scene3DTestScene();
    bool init() override;
    
    void createWorld3D();
    void createUI();
    void createPlayerDlg();
    void createDetailDlg();
    void createDescDlg();
    
    // init in init()
    std::vector<Camera *> _gameCameras;
    Node* _worldScene;
    Node* _dlgScene;
    Node* _osdScene;
    
    // init in createWorld3D()
    TextureCube*        _textureCube;
    Skybox*             _skyBox;
    cocos2d::Terrain*   _terrain;
    Player *            _player;
    Node*               _monsters[2];
    
    // init in createUI()
    Node* _playerItem;
    Node* _detailItem;
    Node* _descItem;
    Node* _ui;
    
    enum SkinType
    {
        HAIR = 0,
        GLASSES,
        FACE,
        UPPER_BODY,
        HAND,
        PANTS,
        SHOES,
        MAX_TYPE,
    };
    
    std::vector<std::string> _skins[(int)SkinType::MAX_TYPE]; //all skins
    int                      _curSkin[(int)SkinType::MAX_TYPE]; //current skin index
    cocos2d::Sprite3D* _reskinGirl;
    
    // for capture screen
    static const int SNAPSHOT_TAG = 119;
    std::string _snapshotFile;
};

/** Define the sub scenes in test. */
enum GAME_SCENE {
    SCENE_UI = 0,
    SCENE_WORLD,
    SCENE_DIALOG,
    SCENE_OSD,
    SCENE_COUNT,
};

/** Define the layers in scene, layer separated by camera mask. */
enum SCENE_LAYER {
    LAYER_BACKGROUND = 0,
    LAYER_DEFAULT,
    LAYER_MIDDLE,
    LAYER_TOP,
    LAYER_COUNT,
};

/** Define the all cameras, which in Scene3DTest, render order. */
enum GAME_CAMERAS_ORDER {
    CAMERA_WORLD_3D_SKYBOX = 0,
    CAMERA_WORLD_3D_SCENE,
    CAMERA_UI_2D,
    CAMERA_DIALOG_2D_BASE,
    CAMERA_DIALOG_3D_MODEL,
    CAMERA_DIALOG_2D_ABOVE,
    CAMERA_OSD_2D_BASE,
    CAMERA_OSD_3D_MODEL,
    CAMERA_OSD_2D_ABOVE,
    CAMERA_COUNT,
};

/*
 Defined s_CF and s_CM to avoid force conversion when call Camera::setCameraFlag
 and Node::setCameraMask.
 
 Usage:
 -   Camera::setCameraFlag(s_CF[<SCENE_LAYER_INDEX>]);
 -   Node::setCameraMask(s_CM[<SCENE_LAYER_INDEX>]);
 
 Note:
 For LAYER_DEFAULT, we use CameraFlag::DEFAULT, thus we don't need to set
 camera flag/mask for this layer, for other layers we must to set camera
 flag/mask to distinguish between each other.
 */
static CameraFlag s_CF[LAYER_COUNT] =
{
    CameraFlag::USER1,      //  LAYER_BACKGROUND
    CameraFlag::DEFAULT,    //  LAYER_DEFAULT
    CameraFlag::USER3,      //  LAYER_MIDDLE
    CameraFlag::USER4,      //  LAYER_TOP
};

static unsigned short s_CM[LAYER_COUNT] =
{
    (unsigned short)s_CF[0],
    (unsigned short)s_CF[1],
    (unsigned short)s_CF[2],
    (unsigned short)s_CF[3],
};

static const char * s_CameraNames[CAMERA_COUNT] =
{
    "World 3D Skybox",
    "World 3D Scene",
    "UI 2D",
    "Dialog 2D Base",
    "Dialog 3D Model",
    "Dialog 2D Above",
    "OSD 2D Base",
    "OSD 3D Model",
    "OSD 2D Above"
};

/** The scenes, located in different position, won't see each other. */
static Vec3 s_scenePositons[SCENE_COUNT] = {
    Vec3(0, 0, 0),          //  center  :   UI scene
    Vec3(0, 10000, 0),      //  top     :   World sub scene
    Vec3(10000, 0, 0),      //  right   :   Dialog sub scene
    Vec3(0, -10000, 0),     //  bottom  :   OSD sub scene
};

////////////////////////////////////////////////////////////////////////////////
// Implements Scene3DTestScene

Scene3DTestScene::Scene3DTestScene()
: _worldScene(nullptr)
, _dlgScene(nullptr)
, _osdScene(nullptr)
, _textureCube(nullptr)
, _skyBox(nullptr)
, _terrain(nullptr)
, _player(nullptr)
, _playerItem(nullptr)
, _detailItem(nullptr)
, _descItem(nullptr)
, _ui(nullptr)
{
    _monsters[0] = _monsters[1] = nullptr;
}

Scene3DTestScene::~Scene3DTestScene()
{
}

bool Scene3DTestScene::init()
{
    bool ret = false;
    do
    {
        CC_BREAK_IF(false == TestCase::init());

        // prepare for camera creation, we need several custom cameras
        _gameCameras.resize(CAMERA_COUNT);
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Camera *ca = nullptr;   // temp variable
        
        ////////////////////////////////////////////////////////////////////////
        // create world 3D scene, this scene has two camera
        _worldScene = Node::create();
        // create a camera to look the skybox
        ca = _gameCameras[CAMERA_WORLD_3D_SKYBOX] =
            Camera::createPerspective(60,
                                      visibleSize.width / visibleSize.height,
                                      10,
                                      1000);
        ca->setDepth(CAMERA_WORLD_3D_SKYBOX);
        ca->setName(s_CameraNames[CAMERA_WORLD_3D_SKYBOX]);
        ca->setCameraFlag(s_CF[LAYER_BACKGROUND]);
        ca->setPosition3D(Vec3(0.f, 0.f, 50.f));
        _worldScene->addChild(ca);
        // create a camera to look the 3D models in world 3D scene
        ca = _gameCameras[CAMERA_WORLD_3D_SCENE] =
            Camera::createPerspective(60,
                                      visibleSize.width/visibleSize.height,
                                      0.1f,
                                      200);
        ca->setDepth(CAMERA_WORLD_3D_SCENE);
        ca->setName(s_CameraNames[CAMERA_WORLD_3D_SCENE]);
        _worldScene->addChild(ca);
        // create 3D objects and add to world scene
        createWorld3D();
        _worldScene->addChild(_skyBox);
        _worldScene->addChild(_terrain);
        _worldScene->addChild(_player);
        _worldScene->addChild(_monsters[0]);
        _worldScene->addChild(_monsters[1]);
        // move camera above player
        ca->setPosition3D(_player->getPosition3D()+Vec3(0, 45, 60));
        ca->setRotation3D(Vec3(-45,0,0));
        _worldScene->setPosition3D(s_scenePositons[SCENE_WORLD]);
        this->addChild(_worldScene);
        
        ////////////////////////////////////////////////////////////////////////
        // test scene is UI scene, use default camera
        // use the default camera to look 2D base UI layer
        ca = _gameCameras[CAMERA_UI_2D] = this->getDefaultCamera();
        ca->setDepth(CAMERA_UI_2D);
        ca->setName(s_CameraNames[CAMERA_UI_2D]);
        // create UI element and add to ui scene
        createUI();
        this->addChild(_ui);
        
        ////////////////////////////////////////////////////////////////////////
        // create dialog scene, this scene has two dialog and three cameras
        _dlgScene = Node::create();
        // use default camera to render the base 2D elements
        ca = _gameCameras[CAMERA_DIALOG_2D_BASE] = Camera::create();
        ca->setDepth(CAMERA_DIALOG_2D_BASE);
        ca->setName(s_CameraNames[CAMERA_DIALOG_2D_BASE]);
        _dlgScene->addChild(ca);
        // create a camera to look the 3D model in dialog scene
        ca = _gameCameras[CAMERA_DIALOG_3D_MODEL] = Camera::create();
        ca->setDepth(CAMERA_DIALOG_3D_MODEL);
        ca->setName(s_CameraNames[CAMERA_DIALOG_3D_MODEL]);
        ca->setCameraFlag(s_CF[LAYER_MIDDLE]);
        _dlgScene->addChild(ca);
        // create a camera to look the UI element over on the 3D models
        ca = _gameCameras[CAMERA_DIALOG_2D_ABOVE] = Camera::create();
        ca->setDepth(CAMERA_DIALOG_2D_ABOVE);
        ca->setName(s_CameraNames[CAMERA_DIALOG_2D_ABOVE]);
        ca->setCameraFlag(s_CF[LAYER_TOP]);
        _dlgScene->addChild(ca);
        // add dialog scene to test scene, which can't see the other element
        _dlgScene->setPosition3D(s_scenePositons[SCENE_DIALOG]);
        this->addChild(_dlgScene);

        ////////////////////////////////////////////////////////////////////////
        // create description scene, this scene has a dialog and three cameras
        _osdScene = Node::create();
        // use default camera for render 2D element
        ca = _gameCameras[CAMERA_OSD_2D_BASE] = Camera::create();
        ca->setDepth(CAMERA_OSD_2D_BASE);
        ca->setName(s_CameraNames[CAMERA_OSD_2D_BASE]);
        _osdScene->addChild(ca);
        // create a camera to look the 3D model in dialog scene
        ca = _gameCameras[CAMERA_OSD_3D_MODEL] = Camera::create();
        ca->setDepth(CAMERA_OSD_3D_MODEL);
        ca->setName(s_CameraNames[CAMERA_OSD_3D_MODEL]);
        ca->setCameraFlag(s_CF[LAYER_MIDDLE]);
        _osdScene->addChild(ca);
        // create a camera to look the UI element over on the 3D models
        ca = _gameCameras[CAMERA_OSD_2D_ABOVE] = Camera::create();
        ca->setDepth(CAMERA_OSD_2D_ABOVE);
        ca->setName(s_CameraNames[CAMERA_OSD_2D_ABOVE]);
        ca->setCameraFlag(s_CF[LAYER_TOP]);
        _osdScene->addChild(ca);
        // add osd scene to test scene, which can't see the other elements
        _osdScene->setPosition3D(s_scenePositons[SCENE_OSD]);
        this->addChild(_osdScene);

        ////////////////////////////////////////////////////////////////////////
        // add touch event callback
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(Scene3DTestScene::onTouchBegan, this);
        listener->onTouchEnded = CC_CALLBACK_2(Scene3DTestScene::onTouchEnd, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        ret = true;
    } while (0);
    
    return ret;
}

void Scene3DTestScene::createWorld3D()
{
    // create skybox
    //create and set our custom shader
    auto shader = GLProgram::createWithFilenames("Sprite3DTest/cube_map.vert",
                                                 "Sprite3DTest/cube_map.frag");
    auto state = GLProgramState::create(shader);
    
    // create the second texture for cylinder
    _textureCube = TextureCube::create("Sprite3DTest/skybox/left.jpg",
                                       "Sprite3DTest/skybox/right.jpg",
                                       "Sprite3DTest/skybox/top.jpg",
                                       "Sprite3DTest/skybox/bottom.jpg",
                                       "Sprite3DTest/skybox/front.jpg",
                                       "Sprite3DTest/skybox/back.jpg");
    //set texture parameters
    Texture2D::TexParams tRepeatParams;
    tRepeatParams.magFilter = GL_LINEAR;
    tRepeatParams.minFilter = GL_LINEAR;
    tRepeatParams.wrapS = GL_MIRRORED_REPEAT;
    tRepeatParams.wrapT = GL_MIRRORED_REPEAT;
    _textureCube->setTexParameters(tRepeatParams);
    
    // pass the texture sampler to our custom shader
    state->setUniformTexture("u_cubeTex", _textureCube);
    
    // add skybox
    _skyBox = Skybox::create();
    _skyBox->setCameraMask(s_CM[LAYER_BACKGROUND]);
    _skyBox->setTexture(_textureCube);

    // create terrain
    Terrain::DetailMap r("TerrainTest/dirt.jpg");
    Terrain::DetailMap g("TerrainTest/Grass2.jpg",10);
    Terrain::DetailMap b("TerrainTest/road.jpg");
    Terrain::DetailMap a("TerrainTest/GreenSkin.jpg",20);
    Terrain::TerrainData data("TerrainTest/heightmap16.jpg",
                              "TerrainTest/alphamap.png",
                              r,g,b,a,Size(32,32),40.0f,2);
    _terrain = Terrain::create(data,Terrain::CrackFixedType::SKIRT);
    _terrain->setMaxDetailMapAmount(4);
    _terrain->setDrawWire(false);

    _terrain->setSkirtHeightRatio(3);
    _terrain->setLODDistance(64,128,192);
    
    // create player
    _player = Player::create("Sprite3DTest/girl.c3b",
                             _gameCameras[CAMERA_WORLD_3D_SCENE],
                             _terrain);
    _player->setScale(0.08f);
    _player->setPositionY(_terrain->getHeight(_player->getPositionX(),
                                              _player->getPositionZ()));
    
    auto animation = Animation3D::create("Sprite3DTest/girl.c3b","Take 001");
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        _player->runAction(RepeatForever::create(animate));
    }
    
    // add BillBoard for test blend
    auto billboard = BillBoard::create("Images/btn-play-normal.png");
    billboard->setPosition3D(Vec3(0,180,0));
    _player->addChild(billboard);
    
    // create two Sprite3D monster, one is transparent
    auto monster = Sprite3D::create("Sprite3DTest/orc.c3b");
    monster->setRotation3D(Vec3(0,180,0));
    monster->setPosition3D(_player->getPosition3D() + Vec3(50, -10, 0));
    monster->setOpacity(128);
    _monsters[0] = monster;
    monster = Sprite3D::create("Sprite3DTest/orc.c3b");
    monster->setRotation3D(Vec3(0,180,0));
    monster->setPosition3D(_player->getPosition3D() + Vec3(-50, -5, 0));
    _monsters[1] = monster;
}

void Scene3DTestScene::createUI()
{
    _ui = Layer::create();
    
    // first, add menu to ui
    // create player button
    auto showPlayerDlgItem = MenuItemImage::create("Images/Pea.png",
                                                   "Images/Pea.png",
                                                   [this](Ref* sender)
	{
    });
    showPlayerDlgItem->setName("showPlayerDlgItem");
    showPlayerDlgItem->setPosition(VisibleRect::left().x + 30, VisibleRect::top().y - 30);
    
    // create description button
    TTFConfig ttfConfig("fonts/arial.ttf", 20);
    auto descItem = MenuItemLabel::create(Label::createWithTTF(ttfConfig, "Description"),
                                          [this](Ref* sender)
    {
       
    });
    descItem->setName("descItem");
    descItem->setPosition(Vec2(VisibleRect::right().x - 50, VisibleRect::top().y - 25));

    auto menu = Menu::create(showPlayerDlgItem,
                             descItem,
                             nullptr);
    menu->setPosition(Vec2::ZERO);
    _ui->addChild(menu);
    
    
}

void Scene3DTestScene::createPlayerDlg()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_ui_plist);
    
    Size dlgSize(190, 240);
    Vec2 pos = VisibleRect::center();
    float margin = 10;
}

void Scene3DTestScene::createDetailDlg()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_ui_plist);
    
    Size dlgSize(190, 240);
    Vec2 pos = VisibleRect::center();
    float margin = 10;
}

void Scene3DTestScene::createDescDlg()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_ui_plist);
    
    Size dlgSize(440, 240);
    Vec2 pos = VisibleRect::center();
    float margin = 10;
    
    
}

void Scene3DTestScene::onTouchEnd(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto camera = _gameCameras[CAMERA_WORLD_3D_SCENE];
    if(camera != Camera::getVisitingCamera())
    {
        return;
    }

    if(_player)
    {
        Vec3 nearP(location.x, location.y, 0.0f), farP(location.x, location.y, 1.0f);
        // convert screen touch location to the world location on near and far plane
        auto size = Director::getInstance()->getWinSize();
        camera->unprojectGL(size, &nearP, &nearP);
        camera->unprojectGL(size, &farP, &farP);
        Vec3 dir = farP - nearP;
        dir.normalize();
        Vec3 collisionPoint;
        bool isInTerrain = _terrain->getIntersectionPoint(Ray(nearP, dir), collisionPoint);
        if (!isInTerrain)
        {
            _player->idle();
        }
        else
        {
            dir = collisionPoint - _player->getPosition3D();
            dir.y = 0;
            dir.normalize();
            _player->_headingAngle =  -1*acos(dir.dot(Vec3(0,0,-1)));
            dir.cross(dir,Vec3(0,0,-1),&_player->_headingAxis);
            _player->_targetPos=collisionPoint;
            _player->forward();
        }
    }
    event->stopPropagation();
}

////////////////////////////////////////////////////////////////////////////////
// Implements Scene3DTests
Scene3DTests::Scene3DTests()
{
    ADD_TEST_CASE(Scene3DTestScene);
}
