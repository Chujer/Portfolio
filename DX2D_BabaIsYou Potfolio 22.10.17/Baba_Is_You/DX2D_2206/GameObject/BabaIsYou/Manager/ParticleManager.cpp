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

	vector<Particle::InstanceData*> temp = particle->GetParticleInstanceData().instances;
	for (Particle::InstanceData* instanceData : temp)
	{
		instances[path].push_back(instanceData);
	}

	if(instanceBuffers.count(path) == 0)
		instanceBuffers[path] = new VertexBuffer(instances[path].data(), sizeof(Particle::InstanceData), 500);
}

void ParticleManager::RemoveParticle(Particle* particle)
{
	string path = particle->GetPath();

	//delete particle;
	

	for (Particle::InstanceData* instanceData : particle->GetParticleInstanceData().instances)
	{
		vector<Particle::InstanceData*>::iterator iter = instances[path].begin();

		for (Particle::InstanceData* temp : instances[path])
		{
			if ((*iter) == instanceData)
			{
				iter = instances[path].erase(iter);
			}
			else
			{
				iter++;
			}
		}
		//instances[path].erase(find(instances[path].begin(), instances[path].end(), instanceData));
	}
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
	for (pair<string, VertexBuffer*> instanceBuffer : instanceBuffers)
	{
		instanceBuffer.second->Update(instances[instanceBuffer.first].data(), instances[instanceBuffer.first].size());
	}
}

void ParticleManager::Render()
{
	//if (!isPlay) return;
	for (pair<string, Quad*> quad : quads)
	{
		 instanceBuffers[quad.first]->Set(1);

		quads[quad.first]->SetRender();

		DC->DrawIndexedInstanced(6, instances[quad.first].size(), 0, 0, 0);
	}
}
