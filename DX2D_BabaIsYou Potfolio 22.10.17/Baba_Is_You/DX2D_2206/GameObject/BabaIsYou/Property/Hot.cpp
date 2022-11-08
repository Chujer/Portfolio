#include "Framework.h"

Hot::Hot(Transform* target, string tag)
	:target(target), tag(tag)
{
	particles.resize(4);
	for(int i =0; i<3;i++)
		particles[i] = new Particle("Particle/SmokeParticle.fx");

	particles[3] = new Particle("Particle/BrokenParticleTest.fx");
	particles[3]->SetRotate(true);
}

Hot::~Hot()
{
}

void Hot::Update()
{
	time += DELTA;
	Object* brokenTarget = BabaMapManager::Get()->GetPositionExceptMyself(target->Position(), tag);
	if (brokenTarget != nullptr && brokenTarget->Active())
	{
		GetBackObject::Get()->SetPrevData(brokenTarget);
		brokenTarget->SetActive(false);
		if(!particles[3]->GetIsPlay())
			particles[3]->Play(brokenTarget->GlobalPosition());
		GetBackObject::Get()->SetPrevData(brokenTarget);
	}
	if (time > PARTICLE_DELAY)
	{
		randNum = Random(0, 10000);
		if (randNum > 9888)
		{
			for (int i =0; i<3;i++)
			{
				if (!particles[i]->GetIsPlay())
				{
					particles[i]->Play(target->GlobalPosition() + Vector2(0, 30.0f));
					time = 0;
					break;
				}

			}
		}
		else
			time = 0;
	}
	for (Particle* particle : particles)
	{
		particle->Update();
	}
}

