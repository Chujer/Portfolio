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
	sample = data;
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

void BabaMapManager::ShakeMap()
{
	shakeStartPos = sample->Position();

	shakePos.x = Random(10.0f, MAX_SHAKE_POWER);
	shakePos.y = Random(10.0f, MAX_SHAKE_POWER);

	shakeEndPos = sample->Position() + shakePos;

	shakeDirection = (shakeEndPos - sample->Position()).Normalize();

	isShacke = true;
}

void BabaMapManager::Update()
{
	if (isShacke)
	{
		shakeTime += DELTA;
		switch (mode)
		{
		case BabaMapManager::MOVE:
			sample->Position() += shakeDirection * 100 * DELTA;
			if (shakeTime > SHAKE_TIME)
			{
				mode = REVERSE_MOVE;
				shakeEndPos = shakeStartPos - shakePos;
				shakeDirection = (shakeEndPos - shakeStartPos).Normalize();
				shakeTime = 0;
			}
			break;
		case BabaMapManager::REVERSE_MOVE:
			sample->Position() += shakeDirection * 100 * DELTA;
			if (shakeTime > SHAKE_TIME)
			{
				mode = Stop;
				shakeTime = 0;
			}
			break;
		case BabaMapManager::Stop:
			sample->Position() = shakeStartPos;
			isShacke = false;
			mode = MOVE;
			break;
		}
	}
	sample->UpdateWorld();
	//CAM->Position() += 10.0f * DELTA;
	//CAM->UpdateWorld();
}
