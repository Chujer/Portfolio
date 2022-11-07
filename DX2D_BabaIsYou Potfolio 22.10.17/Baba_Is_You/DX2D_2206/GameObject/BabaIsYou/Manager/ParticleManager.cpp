#include "Framework.h"

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::AddParticle(Particle* particle)
{
	string path = particle->GetPath();
	BinaryReader* reader = new BinaryReader(path);
	wstring textureFile = reader->WString();

	particles[path].push_back(particle);
	quads[path] = new Quad(textureFile);
	quads[path]->SetVertexShader(L"Shaders/VertexParticle.hlsl");
	quads[path]->SetPixelShader(L"Shaders/PixelInstancing.hlsl");

}

void ParticleManager::RemoveParticle(Particle* particle)
{
	string path = particle->GetPath();

	//delete particle;
	particles[path].erase(find(particles[path].begin(),particles[path].end(),particle));
}

void ParticleManager::Update()
{
	for (pair<string, vector<Particle*>> selectParticle : particles)
	{
		for (Particle* particle : selectParticle.second)
		{
			particle->Update();
		}
	}
}

void ParticleManager::Render()
{
	for (pair<string, Quad*> quad : quads)
	{
		for (Particle* particle : particles[quad.first])
		{
			if (!particle->GetIsPlay()) continue;

			quad.second->GetColorBuffer()->Set(Float4(1, 1, 1, 1));
			quad.second->Position() = particle->GetQuad()->Position();
			quad.second->UpdateWorld();
			particle->GetParticleInstanceData().instanceBuffer->Set(1);
		}



		quad.second->SetRender();

		//DC->DrawIndexedInstanced(6, particle->GetParticleInstanceData().instances->size(), 0, 0, 0);
	}
}
