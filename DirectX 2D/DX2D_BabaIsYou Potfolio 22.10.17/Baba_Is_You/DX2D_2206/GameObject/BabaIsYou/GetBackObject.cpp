#include "Framework.h"

GetBackObject::GetBackObject()
{
}

GetBackObject::~GetBackObject()
{
}

void GetBackObject::SetPrevData(Object* object)
{
	ChangeObjectData tempData;
	tempData.object = object;
	tempData.transform.Position() = object->Position();
	tempData.transform.SetActive(object->Active());
	tempData.curFrame = tempData.object->GetInstanceData().curFrame;

	prevData.push_back(tempData);
}

void GetBackObject::SetNextData(Object* object)
{
	ChangeObjectData tempData;

	for (ChangeObjectData data : prevData)
	{
		if (data.object == object)
		{
			tempData.object = object;
			tempData.transform.Position() = data.transform.Position() - object->Position();
			tempData.transform.SetActive(data.transform.Active());
			tempData.curFrame = tempData.object->GetInstanceData().curFrame;
		}
	}

	datas.push_back(tempData);

	if(datas.size() == prevData.size())
		SaveData();
}

void GetBackObject::SaveData()
{
	saveDatas.push(datas);
	datas.clear();
	prevData.clear();
}

void GetBackObject::GetBack()
{
	if (saveDatas.size() == 0)
		return;

	vector<ChangeObjectData> tempData;

	tempData = saveDatas.top();

	for (ChangeObjectData data : tempData)
	{
		data.object->Position() += data.transform.Position();
		if (data.object->Active() != data.transform.Active())
			oneMore = true;
		data.object->SetActive(data.transform.Active());
		data.object->GetInstanceData().curFrame = data.curFrame;
	}

	saveDatas.pop();

	if (oneMore == true)
	{
		tempData = saveDatas.top();

		for (ChangeObjectData data : tempData)
		{
			data.object->Position() += data.transform.Position();
			data.object->SetActive(data.transform.Active());
			data.object->GetInstanceData().curFrame = data.curFrame;
		}

		saveDatas.pop();
		oneMore = false;
	}

	EventManager::Get()->PlayEvent("CheckIs");
}

void GetBackObject::ClearData()
{
	while (!saveDatas.empty())
		saveDatas.pop();
	datas.clear();
	prevData.clear();
}
