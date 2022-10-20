#pragma once

class ObjectSample : public Singleton<ObjectSample>
{
public:
	struct InstanceData
	{
		wstring path;
		Matrix transform;
		Vector2 maxFrame;
		Vector2 curFrame;
	};

public:
	ObjectSample();
	~ObjectSample();
	InstanceData GetInstanceData(string key);
	map<string, InstanceData> GetSampleData() { return sampleData; }

private:
	void SetSampleClips();
private:
	map<string, InstanceData> sampleData;
};