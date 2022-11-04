#include "Framework.h"

Defeat::Defeat(Transform* target)
	:target(target)
{
}

Defeat::~Defeat()
{
}

void Defeat::Update()
{
	Object* brokenTarget = BabaMapManager::Get()->GetPositionAndEffectTile(target->Position(), "MOVE");
	if (brokenTarget != nullptr && brokenTarget->Active())
	{
		GetBackObject::Get()->SetPrevData(brokenTarget);
		brokenTarget->SetActive(false);
		GetBackObject::Get()->SetNextData(brokenTarget);
	}
}
