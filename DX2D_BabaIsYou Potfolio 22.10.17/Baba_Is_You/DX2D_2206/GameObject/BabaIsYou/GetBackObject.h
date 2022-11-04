#pragma once

class GetBackObject : public Singleton<GetBackObject>
{
private:
	struct ChangeObjectData
	{
		Object* object;
		Transform transform;
		Vector2 curFrame;
	};

public:
	GetBackObject();
	~GetBackObject();

	void SetPrevData(Object* object);
	void SetNextData(Object* object);

	void SaveData();

	void GetBack();

	void ClearData();

private:
	vector<ChangeObjectData> prevData;

	vector<ChangeObjectData> datas;
	stack<vector<ChangeObjectData>> saveDatas;

	bool oneMore = false;
};