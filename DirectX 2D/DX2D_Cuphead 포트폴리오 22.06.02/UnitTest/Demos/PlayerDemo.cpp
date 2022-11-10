#include "stdafx.h"
#include "PlayerDemo.h"

#include "Game/Player.h"
#include "Game/Monster.h"

void PlayerDemo::Init()
{
	player = new Player({ 100, 80, 0 }, { 400, 250, 1 });
//	m = new Monster({ 300, 300, 0 }, { 100, 100, 1 });
}

void PlayerDemo::Destroy()
{
	SAFE_DELETE(player);
//	SAFE_DELETE(m);
}

void PlayerDemo::Update()
{
	player->Update();
	player->Move();

	//if (player->AABB(m->GetAnimRect()->GetBox()) == true)
	//	cout << "Check" << endl;
	//else
	//	cout << "No Check" << endl;

//	m->Update();
//	m->Move();
}

void PlayerDemo::Render()
{
	player->Render();
//	m->Render();
}

void PlayerDemo::PostRender()
{
}

void PlayerDemo::GUI()
{
}
