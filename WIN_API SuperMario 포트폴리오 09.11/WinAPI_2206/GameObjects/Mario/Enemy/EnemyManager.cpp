#include "Framework.h"

EnemyManager::EnemyManager()
{
	/*CreateEnemy(C_TUTLE, { CENTER_X,CENTER_Y +200 });
	CreateEnemy(F_GOOMBA, { CENTER_X-100,CENTER_Y +200 });
	CreateEnemy(F_TUTLE, { CENTER_X-500,CENTER_Y +200 });*/
}

EnemyManager::~EnemyManager()
{
	for (Enemy* enemy : enemys)
	{
		delete enemy;
	}
	enemys.clear();
	enemyIndex = 0;
}

void EnemyManager::Update()
{
	if (enemyIndex == 0)return;
	for (Enemy* enemy : enemys)
	{
		enemy->Update();
	}
}

void EnemyManager::Render(HDC hdc)
{
	if (enemyIndex == 0)return;
	for (Enemy* enemy : enemys)
	{
		enemy->Render(hdc);
	}
}

void EnemyManager::CreateEnemy(MonsterType mType, Vector2 position)
{
	switch (mType)
	{
	case EnemyManager::C_GOOMBA:
		enemys[enemyIndex] = new Goomba();
		enemys[enemyIndex]->InCave(true);
		enemys[enemyIndex]->SetPosition(position);
		enemyIndex++;
		break;
	case EnemyManager::C_TUTLE:
		enemys[enemyIndex] = new Tutle();
		enemys[enemyIndex]->InCave(true);
		enemys[enemyIndex]->SetPosition(position);
		enemyIndex++;
		break;
	case EnemyManager::C_FLOWER:
		break;
	case EnemyManager::F_GOOMBA:
		enemys[enemyIndex] = new Goomba();
		enemys[enemyIndex]->InCave();
		enemys[enemyIndex]->SetPosition(position);
		enemyIndex++;
		break;
	case EnemyManager::F_TUTLE:
		enemys[enemyIndex] = new Tutle();
		enemys[enemyIndex]->InCave();
		enemys[enemyIndex]->SetPosition(position);
		enemyIndex++;
		break;
	case EnemyManager::F_FLYTUTLE:
		break;
	case EnemyManager::F_FLOWER:
		break;
	default:
		break;
	}
}

void EnemyManager::IsCollisionMarioToEnemy(Mario* mario)
{
	for (Enemy* enemy : enemys)
	{
		if (!enemy->IsDeath())
		{
			if (enemy->IsCollision(mario) && (mario->Bottom() < enemy->Pos().y) && !mario->GetDie())
			{
				enemy->IsDeath() = true;
				mario->PushEnemy();
				MarioGameManager::Get()->Score() += 100;
				Audio::Get()->Play("Squish", 0.7f);
			}
			else if (enemy->IsCollision(mario) && (mario->Bottom() > enemy->Pos().y) && !mario->GetDie())
			{
				mario->IsHit();
			}
		}
	}
}

void EnemyManager::IsCollisionBulletToEnemy(Bullet* bullet)
{
	for (Enemy* enemy : enemys)
	{
		if (!enemy->IsDeath())
		{
			if (bullet->IsCollision(enemy))
			{
				enemy->HiddenDeath() = true;
				bullet->Active() = false;
				MarioGameManager::Get()->Score() += 100;
				Audio::Get()->Play("Kick", 0.7f);
			}
		}
	}
}

