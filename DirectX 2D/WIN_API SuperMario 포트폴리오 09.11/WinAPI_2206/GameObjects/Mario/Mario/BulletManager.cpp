#include "Framework.h"

BulletManager::BulletManager()
{
	bullets.resize(MAX_BULLET_COUNT);
	for (Bullet*& bullet : bullets)
	{
		bullet = new Bullet();
	}
}

BulletManager::~BulletManager()
{
	for (Bullet*& bullet : bullets)
	{
		delete bullet;
	}
	bullets.clear();
}

void BulletManager::Update()
{
	shootTime += DELTA;
	for (Bullet*& bullet : bullets)
	{
		if (bullet->Active() == true)
		{
			bullet->Update();
			BlockManager::Get()->IsCollisionBlockToBullet(bullet);
		}
	}
}

void BulletManager::Render(HDC hdc)
{
	for (Bullet*& bullet : bullets)
	{
		if(bullet->Active()== true)
			bullet->Render(hdc);
	}
}

void BulletManager::CreateBullet(Vector2 position, bool isRight)
{
	if (shootTime < SHOOT_DELAY_TIME) return;

	for (Bullet*& bullet : bullets)
	{
		if (!bullet->Active())
		{
			bullet->CreateBullet(position, isRight);
			shootTime = 0;
			break;
		}
	}
}

//void BulletManager::IsCollisionBlockToBullet(Tile* block)
//{
//	if (block->TileInfo().tag == TAG::NONE) return;
//
//	for (Bullet*& bullet : bullets)
//	{
//		if (bullet->IsCollision(block, overlapSize))
//		{
//			if (overlapSize.x > overlapSize.y)
//			{
//				bullet->IsCollisionGround();
//			}
//			else
//			{
//				bullet->Active() = false;
//			}
//		}
//	}
//}
