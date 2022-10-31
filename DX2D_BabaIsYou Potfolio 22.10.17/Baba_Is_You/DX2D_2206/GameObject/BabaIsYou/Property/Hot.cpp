#include "Framework.h"

Hot::Hot(Transform* target)
	:target(target)
{
}

Hot::~Hot()
{
}

void Hot::Update()
{
	Object* brokenTarget = BabaMapManager::Get()->GetPositionandEffectTile(target->Position(), "MELT");
	if (brokenTarget != nullptr)
	{
		brokenTarget->SetActive(false);
	}
}
