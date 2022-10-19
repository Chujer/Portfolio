#include "Framework.h"

ObjectSample::ObjectSample()
{
	SetSampleClips();
}

ObjectSample::~ObjectSample()
{
}

ObjectSample::InstanceData ObjectSample::GetInstanceData(string key)
{
	if (sampleData.count(key) > 0)
		return sampleData[key];
	else
		MessageBox(hWnd, L"키값이 없습니다", L"오류클래스 ObjectSample", MB_OK);
	return InstanceData();
}

void ObjectSample::SetSampleClips()
{
	wstring path;
	Vector2 curFrame;
	Vector2 maxFrame;
	Vector2 cutSize;
	
	//FLAG
	path = L"Textures/Object/Image/FLAG.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["Flag"].path = path;
	sampleData["Flag"].curFrame = curFrame;
	sampleData["Flag"].maxFrame = maxFrame;
}
