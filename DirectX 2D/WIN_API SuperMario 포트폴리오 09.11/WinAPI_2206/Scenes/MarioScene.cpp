#include "Framework.h"
#include "MarioScene.h"

MarioScene::MarioScene()
{
	MarioGameManager::Get()->SetStageInfo(3, 0, 1);
	MarioGameManager::Get()->SetStartStage(bind(&MarioScene::SetStage, this, placeholders::_1));
	MarioGameManager::Get()->SetEndStage(bind(&MarioScene::removeStage, this));
	player = new Mario();
	SkyTexture = new ImageRect(TEXTURE->Add(L"Textures/BigMap_F.bmp", 8000, 768));
	CaveTexture = new ImageRect(TEXTURE->Add(L"Textures/BigMap_C.bmp", 8000, 768));
	texture = CaveTexture;
	texture->Pos() += texture->Half();
	Camera::Get()->SetMapRect(texture);
	MarioGameManager::Get()->SetStage();
	Audio::Get()->Add("Squish", "Sounds/Squish.wav");
	Audio::Get()->Add("Kick", "Sounds/Kick.wav");
}
void MarioScene::SetStage(void* stage)
{
	texture = SkyTexture;
	if ((int)stage == 1)
	{
		texture = SkyTexture;
	}
	else//if ((int)stage == 2)
	{
		texture = CaveTexture;
	}
	//스테이지 Load및 캐릭터, 타일 생성
	string stageName = "TextData/Stage";
	MarioDataManager::Get()->SetStage(stageName+to_string((int)stage)+".");
	if (player->GetDie())
	{
		player->GetDie() = false;
		
	}
	player->Pos() = { MarioDataManager::Get()->GetPlayerData().positionX, 
		MarioDataManager::Get()->GetPlayerData().positionY - player->Size().y };

	EnemyManager::Get();
	BlockManager::Get();

	Camera::Get()->SetTarget(player);
	MarioGameManager::Get()->GameTime() = MarioGameManager::Get()->GetStageTime();
	MarioGameManager::Get()->PlayGame() = true;
}

void MarioScene::removeStage()
{
	EnemyManager::Delete();
	BlockManager::Delete();
	MarioGameManager::Get()->PlayGame() = false;
	ShellManager::Delete();
}

void MarioScene::Start()
{
	Camera::Get()->SetTarget(player);
}


MarioScene::~MarioScene()
{
	delete player;
	EnemyManager::Delete();
	BlockManager::Delete();
	ShellManager::Delete();
}

void MarioScene::Update()
{
	if (KEY_DOWN(VK_TAB))
	{
		MarioGameManager::Get()->StageClear();
		MarioGameManager::Get()->ChangeScene("UIScene");
		return;
	}

	player->Update();
	BulletManager::Get()->Update();
	EnemyManager::Get()->Update();
	BlockManager::Get()->Update();

	
	ShellManager::Get()->Update();

	Collision();
	MarioGameManager::Get()->Update();
}

void MarioScene::Render(HDC hdc)
{
	texture->CamRender(hdc);
	BlockManager::Get()->Render(hdc);
	player->Render(hdc);
	EnemyManager::Get()->Render(hdc);
	ShellManager::Get()->Render(hdc);
	BulletManager::Get()->Render(hdc);
	UIManger::Get()->InGameRender(hdc);
	
	//마우스 휠
	/*if (mouseWheel > 0)
	{
		x++;
		mouseWheel = 0;
	}
	else if(mouseWheel<0)
	{
		x--;
		mouseWheel = 0;
	}
	else
	{

	}
	TextOut(hdc, CENTER_X, CENTER_Y, to_wstring(x).c_str(), to_wstring(x).length());*/
}

void MarioScene::Collision()
{
	if (player->GetDie() == false)
	{
		EnemyManager::Get()->IsCollisionMarioToEnemy(player);
		BlockManager::Get()->IsCollisionBlockToPlayer(player);
		BlockManager::Get()->IsCollisionItemBlockToPlayer(player);
		BlockManager::Get()->IsCollisionItemToPlayer(player);
		BlockManager::Get()->IsCollisionEventTileToPlayer(player);
	}
	for (Enemy* enemy : EnemyManager::Get()->GetEnemy())
	{
		//몬스터와 플레이어 거리에 따른 몬스터 스폰
		if ((enemy->Pos().x - player->Pos().x) < WIN_WIDTH * 0.8f)
		{
			if(enemy->IsDeath() == false)
				enemy->Active() = true;
		}
		if(!enemy->HiddenDeath())
			BlockManager::Get()->IsCollisionBlockToEnemy(enemy);
		ShellManager::Get()->IsCollisionEnemyToShell(enemy);
	}
	for (Shell* shell : ShellManager::Get()->GetShells())
	{
		BlockManager::Get()->IsCollisionBlockToShell(shell);
		if (shell->Active())
		{
			//껍질과 플레이어가 멀어질시 제거
			if (abs((shell->Pos() - player->Pos()).Length()) > WIN_WIDTH * 0.6f)
				shell->Active() = false;
		}
	}	


	ShellManager::Get()->IsCollisionMarioToShell(player);
}
