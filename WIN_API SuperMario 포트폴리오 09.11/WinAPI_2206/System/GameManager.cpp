#include "Framework.h"

#include "Scenes/MarioScene.h"
#include "Scenes/MapEditerScene.h"
#include "Scenes/UIScene.h"

GameManager::GameManager()
{
    Create();   

    SCENE->Add("UIScene", new UIScene());
    SCENE->Add("PlayScene", new MarioScene());
    SCENE->Add("MapEditerScene", new MapEditerScene);

    SCENE->ChangeScene("PlayScene");
}

GameManager::~GameManager()
{
    Destory();
}

void GameManager::Update()
{
    if (isStop) return;

    if (KEY_DOWN(VK_F1))
        Texture::SwichDebug();

    Keyboard::Get()->Update();
    Timer::Get()->Update();
    EffectManager::Get()->Update();
    Audio::Get()->Update();
    Camera::Get()->Update();

    SCENE->Update();
}

void GameManager::Render()
{
    PatBlt(backBuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS);

    SCENE->Render(backBuffer);
    EffectManager::Get()->Render(backBuffer);
    
    //Timer::Get()->Render(backBuffer);

    BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
        backBuffer, 0, 0, SRCCOPY);
}

void GameManager::SetInit()
{
    hdc = GetDC(hWnd);

    backBuffer = CreateCompatibleDC(hdc);    
    bitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
    SelectObject(backBuffer, bitmap);

    SetBkMode(backBuffer, TRANSPARENT);
}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    TextureManager::Get();
    EffectManager::Get();
    Audio::Get();
    Camera::Get();
    SceneManager::Get();
}

void GameManager::Destory()
{
    Keyboard::Delete();
    Timer::Delete();
    TextureManager::Delete();
    EffectManager::Delete();
    Audio::Delete();
    Camera::Delete();
    SceneManager::Delete();
}
