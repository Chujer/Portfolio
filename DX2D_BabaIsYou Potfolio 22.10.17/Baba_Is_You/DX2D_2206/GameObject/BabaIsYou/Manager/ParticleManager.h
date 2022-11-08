#pragma once

class ParticleManager : public Singleton<ParticleManager>
{
public:
	ParticleManager();
	~ParticleManager();

	void AddParticle(Particle* particle);
	void RemoveParticle(Particle* particle);

	void Update();
	void Render();

private:
	map<string, vector<Particle*>> particles;
	map<string, vector<Particle::InstanceData*>> instances;
	map<string, Quad*> quads;
	map<string, VertexBuffer*> instanceBuffers;
};