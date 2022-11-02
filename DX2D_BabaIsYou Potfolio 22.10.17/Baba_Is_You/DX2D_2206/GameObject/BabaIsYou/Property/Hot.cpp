#include "Framework.h"

Hot::Hot(Transform* target, string tag)
	:target(target), tag(tag)
{
}

Hot::~Hot()
{
}

void Hot::Update()
{
	Object* brokenTarget = BabaMapManager::Get()->GetPositionExceptMyself(target->Position(), tag);
	if (brokenTarget != nullptr)
	{
		brokenTarget->SetActive(false);
	}
}
