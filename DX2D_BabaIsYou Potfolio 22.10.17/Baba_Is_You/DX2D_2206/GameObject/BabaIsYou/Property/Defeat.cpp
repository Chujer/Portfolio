#include "Framework.h"

Defeat::Defeat(Transform* target)
	:target(target)
{
	particles.resize(1);
	particles[0] = new Particle("Particle/BrokenParticleTest.fx");
	particles[0]->SetRotate(true);
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
		if (!particles[0]->GetIsPlay())
		{
			particles[0]->Play(target->GlobalPosition());
		}
		GetBackObject::Get()->SetNextData(brokenTarget);
	}
	particles[0]->Update();
}
