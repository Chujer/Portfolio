#include "Framework.h"

BabaMapManager::BabaMapManager()
{
}

BabaMapManager::~BabaMapManager()
{
}

void BabaMapManager::SetMapData(BabaTileMap* data)
{
	maps.clear();
	maps = data->GetTiles();
	LB = data->GetBGTiles().front()->Position();
	RT = data->GetBGTiles().back()->Position();
}

Object* BabaMapManager::GetPositionTile(Vector2 pos)
{
	for (Object* object : maps)
	{
		if (object->Position() == pos)
		{
			return object;
		}
	}

	return nullptr;
}

Object* BabaMapManager::GetPositionandEffectTile(Vector2 pos, string effect)
{
	for (Object* object : maps)
	{
		if (object->effect == effect && object->Position() == pos)
		{
			return object;
		}
	}

	return nullptr;
}
