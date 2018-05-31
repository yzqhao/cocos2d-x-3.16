#ifndef _SCENE_3D_TEST_H_
#define _SCENE_3D_TEST_H_

#include "TerrainTest/TerrainTest.h"

namespace cocos2d
{
	class Director;
	class Touch;
	class Event;
	class EventListenerTouchOneByOne;
}

USING_NS_CC;

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
class Scene3DTestScene : public Scene
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

#endif
