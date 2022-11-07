#include "Framework.h"

Sink::Sink(Transform* target, string tag)
	:target(target), tag(tag)
{
	particles.resize(2);
	for (int i = 0; i < 2; i++)
	{
		particles[i] = new Particle("Particle/BrokenParticleTest.fx");
		particles[i]->SetRotate(true);
	}
}

Sink::~Sink()
{
}

void Sink::Update()
{
	for (Particle* particle : particles)
	{
		if (particle->GetIsPlay())
			particle->Update();
	}

	if (!target->Active()) return;

	Object* brokenTarget = BabaMapManager::Get()->GetPositionExceptMyself(target->Position(),tag);

	if (brokenTarget != nullptr)
	{
		GetBackObject::Get()->SetPrevData(BabaMapManager::Get()->GetPositionMyself(target));
		GetBackObject::Get()->SetPrevData(brokenTarget);
		if (!particles[0]->GetIsPlay())
		{
			particles[0]->Play(target->GlobalPosition());
		}
		if (!particles[1]->GetIsPlay())
		{
			particles[1]->Play(brokenTarget->GlobalPosition());
		}
		brokenTarget->SetActive(false);
		target->SetActive(false);
		GetBackObject::Get()->SetNextData(BabaMapManager::Get()->GetPositionMyself(target));
		GetBackObject::Get()->SetNextData(brokenTarget);

	}

}

void Sink::Render()
{
	for (Particle* particle : particles)
	{
		if (particle->GetIsPlay())
			particle->Render();
	}
}
