#include "Framework.h"

Sink::Sink(Transform* target)
	:target(target)
{
}

Sink::~Sink()
{
}

void Sink::Update()
{
	if (!target->Active()) return;

	Object* brokenTarget = BabaMapManager::Get()->GetPositionTile(target->Position());
	if (brokenTarget != nullptr)
	{
		brokenTarget->SetActive(false);
		target->SetActive(false);
	}
}
