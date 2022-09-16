#include "stdafx.h"
#include "GameDemo.h"

#include "Game/Player.h"

void GameDemo::Init()
{
	player = new Player({ 200, 60, 0 }, { 400, 250, 1 });
	hitbox = new HitBox({ 720, 100, 0 }, { 80, 150, 1 }, "Bullet");
}

void GameDemo::Destroy()
{
	SAFE_DELETE(player);
	SAFE_DELETE(hitbox);
}

void GameDemo::Update()
{
	player->Update();
	player->Move();
	hitbox->Update();

}

void GameDemo::Render()
{
	player->Render();
	hitbox->Render();
}

void GameDemo::PostRender()
{
}

void GameDemo::GUI()
{
}
