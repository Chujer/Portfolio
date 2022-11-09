#include "Framework.h"

Win::Win(Transform* target)
	:target(target)
{	
	particles.resize(2);
	particles[0] = new Particle("Particle/WinParticle.fx");
	particles[1] = new Particle("Particle/ClearParticle.fx");
}

Win::~Win()
{
}

void Win::Update()
{
	Object* MoveTile = BabaMapManager::Get()->GetPositionAndEffectTile(target->Position(), "MOVE");

	if (MoveTile == nullptr)
	{
		if (!particles[0]->GetIsPlay() && target->Active())
			particles[0]->Play(target->GlobalPosition());
	}
	else
	{
		if (!particles[1]->GetIsPlay())
		{
			particles[1]->Play(target->GlobalPosition());
			Audio::Get()->Play("Clear");
			Audio::Get()->Stop("BGM");
		}
		isClear = true;
	}
	particles[0]->Update();
	particles[1]->Update();
	if (isClear)
	{
		time += DELTA;
		if (time > 1.0f)
		{
			BabaGameManager::Get()->CallLoad() = true;
		}
		if (time > 2.0f)
			BabaMapManager::Get()->IsClear() = true;
	}
}
