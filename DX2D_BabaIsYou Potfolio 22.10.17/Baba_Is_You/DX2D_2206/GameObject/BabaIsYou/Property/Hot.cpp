#include "Framework.h"

Hot::Hot(Transform* target, string tag)
	:target(target), tag(tag)
{
	particles.resize(3);
	for(int i =0; i<3;i++)
		particles[i] = new Particle("Particle/SmokeParticle.fx");
}

Hot::~Hot()
{
}

void Hot::Update()
{
	time += DELTA;
	Object* brokenTarget = BabaMapManager::Get()->GetPositionExceptMyself(target->Position(), tag);
	if (brokenTarget != nullptr)
	{
		GetBackObject::Get()->SetPrevData(brokenTarget);
		brokenTarget->SetActive(false);
		GetBackObject::Get()->SetPrevData(brokenTarget);
	}
	if (time > PARTICLE_DELAY)
	{
		if (Random(0, 100) > 90)
		{
			for (Particle* particle : particles)
			{
				if (!particle->GetIsPlay())
				{
					particle->Play(target->Position() + Vector2(0, 20.0f));
					break;
				}

			}
		}
	}
	for (Particle* particle : particles)
	{
		particle->Update();
	}
}

