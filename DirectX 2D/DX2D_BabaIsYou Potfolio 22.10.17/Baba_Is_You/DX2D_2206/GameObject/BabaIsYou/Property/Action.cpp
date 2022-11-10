#include "Framework.h"

Action::Action()
{
}

Action::~Action()
{
	if (particles.size() != 0)
	{
		for (Particle* particle : particles)
		{
			delete particle;
		}
	}
}

void Action::Render()
{
	if (particles.size() != 0)
	{
		for (Particle* particle : particles)
		{
			if(particle->GetIsPlay())
				particle->Render();
		}
	}
}