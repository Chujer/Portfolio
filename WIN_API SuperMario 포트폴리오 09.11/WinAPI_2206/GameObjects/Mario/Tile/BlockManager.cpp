#include "Framework.h"

BlockManager::BlockManager()
{
	Audio::Get()->Add("Coin", "Sounds/Coin.wav");
	Audio::Get()->Add("Item", "Sounds/Item.wav");
	/*CreateGround();
	CreateSecondFloor();*/
}

BlockManager::~BlockManager()
{
	for (BlockTile*& block : indestructibleGroundBlocks)
	{
		delete block;
	}
	for (BlockTile* block : nomalBlock)
	{
		delete block;
	}
	for (ItemBlockTile* block : itemBlocks)
	{
		delete block;
	}
	for (EventTile* tile : eventTiles)
	{
		delete tile;
	}
	for (Tile* bgTile : backgroundTiles)
	{
		delete bgTile;
	}
	backgroundTiles.clear();
	indestructibleGroundBlocks.clear();
	nomalBlock.clear();
	itemBlocks.clear();
	eventTiles.clear();
}

void BlockManager::Update()
{
	for (BlockTile* block : indestructibleGroundBlocks)
		block->Update();

	for (BlockTile* block : nomalBlock)
		block->Update();

	for (ItemBlockTile* block : itemBlocks)
	{
		block->Update();
		IsCollisionBlockToItem(block->GetItem());
	}
	/*if (itemBlock->GetItem()->GetArrivalDestination())
		IsCollisionBlockToItem(itemBlock->GetItem());*/
}

void BlockManager::Render(HDC hdc)
{
	for (BlockTile* block : indestructibleGroundBlocks)
		block->Render(hdc);

	for (BlockTile* block : nomalBlock)
		block->Render(hdc);

	for (Tile* tile : backgroundTiles)
		tile->Render(hdc);

	for (ItemBlockTile* block : itemBlocks)
		block->Render(hdc);

	for (EventTile* tile : eventTiles)
		tile->Render(hdc);
}

void BlockManager::CreateStage(MarioDataManager::TileData data,string ItemName)
{
	switch (data.tag)
	{
	case TAG::BACKGROUND:
		CreateBackgroundTiles(data);
		break;
	case TAG::INDESTRUCTIBLE_BLOCK:
		CreateindestructibleGroundBlocks(data);
		break;	
	case TAG::BLOCK:
		CreateNomalBlocks(data);
		break;
	case TAG::ITEMBLOCK:
		CreateItemBlocks(data, ItemName);
		break;
	case TAG::EVENT:
		CreateEventTiles(data);
		break;
	default:
		break;
	}
}

void BlockManager::CreateBackgroundTiles(MarioDataManager::TileData data)
{
	Tile* tempBlock = new Tile;
	tempBlock->CreateTile({ data.positionX,data.positionY }, data.name, (TAG)data.tag);

	backgroundTiles.push_back(tempBlock);
}

void BlockManager::CreateEventTiles(MarioDataManager::TileData data)
{
	EventTile* tempBlock = new EventTile;
	tempBlock->CreateTile({ data.positionX,data.positionY }, data.name, (TAG)data.tag);
	tempBlock->SetEvent(data.name);
	
	eventTiles.push_back(tempBlock);
}


void BlockManager::CreateindestructibleGroundBlocks(MarioDataManager::TileData data)
{
	BlockTile* tempBlock = new BlockTile;
	tempBlock->CreateTile({ data.positionX,data.positionY }, data.name, (TAG)data.tag);

	indestructibleGroundBlocks.push_back(tempBlock);
}

void BlockManager::CreateNomalBlocks(MarioDataManager::TileData data)
{
	BlockTile* tempBlock = new BlockTile;
	tempBlock->CreateTile({ data.positionX,data.positionY }, data.name, (TAG)data.tag);

	nomalBlock.push_back(tempBlock);
}

void BlockManager::CreateItemBlocks(MarioDataManager::TileData data, string ItemName)
{
	ItemBlockTile* tempBlock = new ItemBlockTile;
	tempBlock->CreateTile({ data.positionX,data.positionY }, data.name, (TAG)data.tag, ItemName);
	tempBlock->CreateAnimation();

	itemBlocks.push_back(tempBlock);
}



void BlockManager::IsCollisionBlockToPlayer(Mario* mario)
{
	if (mario->GetDie() == true)return;


	for (BlockTile* gBlock : indestructibleGroundBlocks)
	{
		if (gBlock->IsCollision(mario, overlap))
		{
			if (overlap.x > overlap.y)
			{
				if (gBlock->Top() > mario->Pos().y)
				{
					mario->Pos().y -= overlap.y;
					mario->IsOnTheGround({ gBlock->Pos().x,gBlock->Top() });
				}
			}
			else
			{
				if (gBlock->Right() < mario->Pos().x)
					mario->Pos().x += overlap.x;
				else
					mario->Pos().x -= overlap.x;
			}
		}
	}

	for (BlockTile* nBlock : nomalBlock)
	{
		if (nBlock->GetTileInfo().tag == TAG::BACKGROUND)
			continue;
		if (nBlock->IsCollision(mario, overlap))
		{
			if (overlap.x > overlap.y)
			{
				if (nBlock->Bottom() < mario->Pos().y)		//블럭이 마리오 밑에있을대
				{
					mario->Pos().y += overlap.y;
					mario->GetVelocity().y = 2500.0f * DELTA;

					if (mario->GetMode() == 1 || mario->GetMode() == 2)		//마리오 크기가 클때
						nBlock->Break();
				}
				else if (nBlock->Top() > mario->Pos().y)
				{
					mario->Pos().y -= overlap.y;
					mario->IsOnTheGround({ nBlock->Pos().x,nBlock->Top() });
				}
			}
			else
			{
				if (nBlock->Right() < mario->Pos().x)
					mario->Pos().x += overlap.x;
				else
					mario->Pos().x -= overlap.x;
			}
		}
	}

}

void BlockManager::IsCollisionEventTileToPlayer(Mario* mario)
{
	for (EventTile* tile : eventTiles)
	{
		if (tile->IsCollision(mario))
		{
			tile->StartEvent();
			break;
		}
	}
}

void BlockManager::IsCollisionBlockToEnemy(Enemy* enemy)
{
	for (BlockTile* gBlock : indestructibleGroundBlocks)
	{
		if (gBlock->IsCollision(enemy,overlap))
		{
			if (overlap.x > overlap.y)
			{
				enemy->Pos().y -= overlap.y;
				enemy->IsOnTheGround({ gBlock->Pos().x,gBlock->Top() });
			}
			else if(overlap.y > overlap.x+2.0f)
			{
				if (gBlock->Right() < enemy->Pos().x)
				{
					enemy->Pos().x += overlap.x;
					enemy->ReturnMoveX();
				}
				else
				{
					enemy->Pos().x -= overlap.x;
					enemy->ReturnMoveX();
				}
			}
		}
	}
}

void BlockManager::IsCollisionItemBlockToPlayer(Mario* mario)
{
	//아이템블록 TO 플레이어
	for (ItemBlockTile* itemBlock : itemBlocks)
	{
		if (itemBlock->IsCollision(mario, overlap))
		{
			if (overlap.x > overlap.y)
			{
				if (itemBlock->Bottom() < mario->Pos().y)
				{
					mario->Pos().y += overlap.y;
					mario->GetVelocity().y = 2500.0f * DELTA;
					itemBlock->MakeItem();
				}
				else if (itemBlock->Top() > mario->Pos().y)
				{
					mario->Pos().y -= overlap.y;
					mario->IsOnTheGround({ itemBlock->Pos().x,itemBlock->Top() });
				}
			}
			else
			{
				if (itemBlock->Right() < mario->Pos().x)
					mario->Pos().x += overlap.x;
				else
					mario->Pos().x -= overlap.x;
			}
		}
	}
}

void BlockManager::IsCollisionBlockToItem(Item* item)
{
	for (BlockTile* gBlock : indestructibleGroundBlocks)
	{
		if (gBlock->IsCollision(item, overlap))
		{
			if (overlap.x > overlap.y)
			{
				if (gBlock->Top() > item->Pos().y)
				{
					if(item->GetArrivalDestination() == true)
						item->IsOnTheGround({ gBlock->Pos().x,gBlock->Top() });
				}
			}
			else
			{
				if (item->GetArrivalDestination() == true)
					item->Speed() *= -1.0f;
			}
		}
	}

	for (BlockTile* gBlock : nomalBlock)
	{
		if (gBlock->IsCollision(item))
		{
			if (gBlock->IsCollision(item, overlap))
			{
				if (overlap.x > overlap.y)
				{
					if (gBlock->Top() > item->Pos().y)
					{
						if (item->GetArrivalDestination() == true)
							item->IsOnTheGround({ gBlock->Pos().x,gBlock->Top() });
					}
				}
				else
				{
					if (item->GetArrivalDestination() == true)
						item->Speed() *= -1.0f;
				}
			}
		}
	}
	
	for (ItemBlockTile* gBlock : itemBlocks)
	{
		if (gBlock->IsCollision(item))
		{
			if (gBlock->IsCollision(item, overlap))
			{
				if (overlap.x > overlap.y)
				{
					if (gBlock->Top() > item->Pos().y)
					{
						if (item->GetArrivalDestination() == true)
							item->IsOnTheGround({ gBlock->Pos().x,gBlock->Top() });
					}
				}
				else
				{
					if (item->GetArrivalDestination() == true)
						item->Speed() *= -1.0f;
				}
			}
		}
	}
}

void BlockManager::IsCollisionItemToPlayer(Mario* mario)
{
	if (mario->GetDie() == true)return;

	for (ItemBlockTile* itemBlock : itemBlocks)
	{
		if (itemBlock->GetItem()->IsCollision(mario))
		{
			itemBlock->GetItem()->StartEvent();
			itemBlock->GetItem()->Active() = false;
		}
	}
	
}

void BlockManager::IsCollisionBlockToShell(Shell* shell)
{
	for (BlockTile* gBlock : indestructibleGroundBlocks)
	{
		if (gBlock->IsCollision(shell, overlap))
		{
			if (overlap.x > overlap.y)
			{
				if(shell->GetHiddenDeath() == false)
					shell->Pos().y -= overlap.y;
				shell->IsOnTheGround({ gBlock->Pos().x,gBlock->Top() });
			}
			else if (overlap.y > overlap.x + 2.0f)
			{
				if (gBlock->Right() < shell->Pos().x)
				{
					shell->Pos().x += overlap.x;
					shell->ReturnMoveX();
					Audio::Get()->Play("Kick", 0.7f);
				}
				else
				{
					shell->Pos().x -= overlap.x;
					shell->ReturnMoveX();
					Audio::Get()->Play("Kick", 0.7f);
				}
			}
		}
	}
}

void BlockManager::IsCollisionBlockToBullet(Bullet* bullet)
{
	for (BlockTile* gBlock : indestructibleGroundBlocks)
	{
		if (gBlock->IsCollision(bullet))
		{
			if (gBlock->Top() > bullet->Pos().y)
			{
				bullet->IsCollisionGround();
			}
			else
			{
				bullet->Active() = false;
			}
		}
	}

	for (BlockTile* gBlock : nomalBlock)
	{
		if (gBlock->IsCollision(bullet, overlap))
		{
			if (gBlock->IsCollision(bullet))
			{
				if (gBlock->Top() > bullet->Pos().y)
				{
					bullet->IsCollisionGround();
				}
				else
				{
					bullet->Active() = false;
				}
			}
		}
	}

	for (ItemBlockTile* gBlock : itemBlocks)
	{
		if (gBlock->IsCollision(bullet))
		{
			if (gBlock->Top() > bullet->Pos().y)
			{
				bullet->IsCollisionGround();
			}
			else
			{
				bullet->Active() = false;
			}
		}
	}
	/*for (BlockTile* gBlock : indestructibleGroundBlocks)
	{
		if (gBlock->IsCollision(bullet, overlap))
		{
			if (overlap.x > overlap.y)
			{
				if (gBlock->Top() > bullet->Pos().y)
				{
					bullet->IsCollisionGround();
				}
			}
			else
			{
				bullet->Active() = false;
			}
		}
	}

	for (BlockTile* gBlock : nomalBlock)
	{
		if (gBlock->IsCollision(bullet, overlap))
		{
			if (overlap.x > overlap.y)
			{
				if (gBlock->Top() > bullet->Pos().y)
				{
					bullet->IsCollisionGround();
				}
			}
			else
			{
				bullet->Active() = false;
			}
		}
	}

	for (ItemBlockTile* gBlock : itemBlocks)
	{
		if (gBlock->IsCollision(bullet, overlap))
		{
			if (overlap.x > overlap.y)
			{
				if (gBlock->Top() > bullet->Pos().y)
				{
					bullet->IsCollisionGround();
				}
			}
			else
			{
				bullet->Active() = false;
			}
		}
	}*/
}
