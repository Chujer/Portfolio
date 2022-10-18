#pragma once

class ObjectSample : public Singleton<ObjectSample>
{
public:
	struct InstanceData
	{
		Matrix transform;
		Vector2 maxFrame;
		Vector2 curFrame;
	};

public:
	ObjectSample();
	~ObjectSample();

private:
	void SetSampleClips();
private:
	map<string, Clip*> sampleClips;
};