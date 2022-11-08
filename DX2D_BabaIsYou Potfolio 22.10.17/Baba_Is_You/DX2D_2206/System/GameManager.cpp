#include "Framework.h"

#include "Scenes/MapEditerScene.h"
#include "Scenes/BabaScene.h"
#include "Scenes/TestScene.h"
#include "Scenes/ParticleScene.h"
#include "Scenes/FadeScene.h"

GameManager::GameManager()
{
    Create();
        
    //scene = new TextureScene();
    //scene = new ShootingScene();
    //scene = new CollisionScene();
    //scene = new AnimationScene();
    //scene = new ShaderScene();
    //scene = new PuzzleScene();
    //scene = new RenderTargetScene();
    //scene = new TileScene();
    //scene = new TankScene();
    //scene = new DijkstraScene();
    //scene = new InstancingScene();
    //scene = new FontScene();

    Scene * scene = new BabaScene();
    Scene * fadeScene = new FadeScene();
    scene->SetDepth(1);
    fadeScene->SetDepth(2);
    SCENE->Create("Start", scene);    
    SCENE->Create("Fade", fadeScene);
    
    SCENE->Add("Fade");        
    SCENE->Add("Start");        
}

GameManager::~GameManager()
{    
    Delete();
}

void GameManager::Update()
{
    Keyboard::Get()->Update();
    Timer::Get()->Update();
    EffectManager::Get()->Update();

    SCENE->Update();

    CAM->Update();
}

void GameManager::Render()
{
    SCENE->PreRender();

    Device::Get()->Clear();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    Font::Get()->GetDC()->BeginDraw();

    Device::Get()->SetRenderTarget();

    SCENE->Render();

    EffectManager::Get()->Render();

    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    Font::Get()->RenderText(fps, Vector2(100, WIN_HEIGHT - 20));
    //ImGui::Text(fps.c_str());

    CAM->GUIRender();

    SCENE->PostRender();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Font::Get()->GetDC()->EndDraw();

    Device::Get()->Present();
}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    Device::Get();
    Environment::Get();
    EffectManager::Get();
    Font::Get();
    SceneManager::Get();

    Font::Get()->AddColor("White", Float3(1, 1, 1));
    Font::Get()->AddStyle("Default", L"¸¼Àº°íµñ");

    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("Default");

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
    Keyboard::Delete();
    Timer::Delete();
    Device::Delete();
    Environment::Delete();
    Texture::Delete();
    Shader::Delete();
    EffectManager::Delete();
    Font::Delete();
    SceneManager::Delete();
}