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

Object* BabaMapManager::GetPositionAndEffectTile(Vector2 pos, string effect)
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

Object* BabaMapManager::GetPositionExceptMyself(Vector2 pos, string tag)
{
	for (Object* object : maps)
	{
		if (object->tag != tag && object->Position() == pos)
		{
			return object;
		}
	}

	return nullptr;
}

Object* BabaMapManager::GetPositionMyself(Transform* transform)
{
	for (Object* object : maps)
	{
		if (object->GetTransform() == transform && object->Position() == transform->Position())
		{
			return object;
		}
	}

	return nullptr;
}
