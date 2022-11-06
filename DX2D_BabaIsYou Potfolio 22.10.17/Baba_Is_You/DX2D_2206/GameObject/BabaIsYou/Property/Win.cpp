#include "Framework.h"

Win::Win(Transform* target)
	:target(target)
{	
	particles.resize(1);
	particles[0] = new Particle("Particle/WinParticle.fx");
}

Win::~Win()
{
}

void Win::Update()
{
	if (!particles[0]->GetIsPlay())
		particles[0]->Play(target->GlobalPosition());

	particles[0]->Update();
}
