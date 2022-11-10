#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768


#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define PI 3.1415f

#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define YELLOW RGB(255, 255, 0)
#define CYAN RGB(0, 255, 255)
#define MAGENTA RGB(255, 0, 255)
#define BLACK RGB(0, 0, 0)
#define WHTIE RGB(255, 255, 255)

#define LERP(s, e, t) (s + (e - s) * (t))
//#define LERP(s, e, t) (s * (1 - t) + e * t)

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#define DELTA Timer::Get()->GetTimeElapsed()

#define TEXTURE TextureManager::Get()
#define SCENE SceneManager::Get()

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>

using namespace std;

//FMOD Library
#include "Libraries/inc/fmod.hpp"
#pragma comment(lib, "Libraries/lib/x64/fmod_vc.lib")

//Framework Header
#include "Utilities/Singleton.h"
#include "Utilities/Keyboard.h"
#include "Utilities/Timer.h"
#include "Utilities/Audio.h"
#include "Utilities/BinaryReader.h"
#include "Utilities/BinaryWriter.h"

#include "Math/Vector2.h"
#include "Math/GameMath.h"

#include "Render/Texture.h"
#include "Render/TextureManager.h"
#include "Render/Animation.h"

#include "Camera/Camera.h"

using namespace GameMath;

//GameObject Header
#include "GameObjects/Basic/Circle.h"
#include "GameObjects/Basic/Line.h"
#include "GameObjects/Basic/Rect.h"
#include "GameObjects/Basic/ImageRect.h"

#include "GameObjects/Effect/Effect.h"
#include "GameObjects/Effect/EffectManager.h"

#include "GameObjects/UI/ProgressBar.h"
#include "GameObjects/UI/Button.h"

//Tile
#include "GameObjects/Mario/Tile/TileTextureData.h"
#include "GameObjects/Mario/Mario/MarioEventManager.h"

typedef TileTextureData::TileData TileData;
typedef TileTextureData::TAG TAG;

#include "GameObjects/Mario/Tile/Tile.h"
#include "GameObjects/Mario/Tile/BlockTile.h"
#include "GameObjects/Mario/Tile/ItemBlockTile.h"
#include "GameObjects/Mario/Tile/EventTile.h"

#include "GameObjects/Mario/Item/Item.h"
#include "GameObjects/Mario/Item/Mushroom.h"
#include "GameObjects/Mario/Item/Flower.h"
#include "GameObjects/Mario/Item/Coin.h"


#include "GameObjects/Mario/MarioDataManager.h"

//Bullet
#include "GameObjects/Mario/Mario/Bullet.h"
#include "GameObjects/Mario/Mario/BulletManager.h"

//Character
#include "GameObjects/Mario/Mario/Mario.h"
#include "GameObjects/Mario/Enemy/Enemy.h"
#include "GameObjects/Mario/Enemy/Goomba.h"
#include "GameObjects/Mario/Enemy/Tutle.h"
#include "GameObjects/Mario/Enemy/Shell.h"
#include "GameObjects/Mario/Enemy/ShellManager.h"
#include "GameObjects/Mario/Enemy/EnemyManager.h"

//CreateMapManager
#include "GameObjects/Mario/Tile/BlockManager.h"

//Scene Header;
#include "Scenes/Scene.h"
#include "System/SceneManager.h"
#include "System/GameManager.h"

//TileMap
#include "GameObjects/Mario/MariioMapEditer/TileMapManager.h"
#include "GameObjects/Mario/MariioMapEditer/MapEditerUIManager.h"

#include "GameObjects/Mario/MarioGameManager.h"
#include "GameObjects/Mario/UI/UIManager.h"

extern Vector2 mousePos;
extern HINSTANCE hInst;
extern HWND hWnd;
extern short mouseWheel;