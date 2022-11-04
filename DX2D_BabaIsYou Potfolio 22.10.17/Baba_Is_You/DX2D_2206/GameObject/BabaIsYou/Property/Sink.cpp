#include "Framework.h"

Sink::Sink(Transform* target, string tag)
	:target(target), tag(tag)
{
}

Sink::~Sink()
{
}

void Sink::Update()
{
	if (!target->Active()) return;

	Object* brokenTarget = BabaMapManager::Get()->GetPositionExceptMyself(target->Position(),tag);

	if (brokenTarget != nullptr)
	{
		GetBackObject::Get()->SetPrevData(BabaMapManager::Get()->GetPositionMyself(target));
		GetBackObject::Get()->SetPrevData(brokenTarget);
		brokenTarget->SetActive(false);
		target->SetActive(false);
		GetBackObject::Get()->SetNextData(BabaMapManager::Get()->GetPositionMyself(target));
		GetBackObject::Get()->SetNextData(brokenTarget);

	}
}
