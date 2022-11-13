#include "Framework.h"

ObjectSample::ObjectSample()
{
	SetSampleClips();
}

ObjectSample::~ObjectSample()
{

}

/*키에따른 데이터 호출*/
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
	
	//BG
	path = L"Textures/Object/Image/BG.png";
	curFrame = { 0,0 };
	maxFrame = { 1,1 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["ABG"].path = path;
	sampleData["ABG"].curFrame = curFrame;
	sampleData["ABG"].maxFrame = maxFrame;

	//FLAG
	path = L"Textures/Object/Name/FLAG.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["FLAG_NAME"].path = path;
	sampleData["FLAG_NAME"].curFrame = curFrame;
	sampleData["FLAG_NAME"].maxFrame = maxFrame;

	path = L"Textures/Object/Image/FLAG.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["FLAG"].path = path;
	sampleData["FLAG"].curFrame = curFrame;
	sampleData["FLAG"].maxFrame = maxFrame;

	
	//ROCK
	path = L"Textures/Object/Name/ROCK.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["ROCK_NAME"].path = path;
	sampleData["ROCK_NAME"].curFrame = curFrame;
	sampleData["ROCK_NAME"].maxFrame = maxFrame;

	path = L"Textures/Object/Image/ROCK.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["ROCK"].path = path;
	sampleData["ROCK"].curFrame = curFrame;
	sampleData["ROCK"].maxFrame = maxFrame;

	//GRASS
	path = L"Textures/Object/Name/GRASS.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["GRASS_NAME"].path = path;
	sampleData["GRASS_NAME"].curFrame = curFrame;
	sampleData["GRASS_NAME"].maxFrame = maxFrame;

	path = L"Textures/Object/Image/GRASS_ALL.png";
	for (int i = 1; i < 17; i++)
	{
		curFrame = { i - 1.0f,0 };
		maxFrame = { 16,3 };
		cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
		cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
		sampleData["GRASS_" + to_string(i)].path = path;
		sampleData["GRASS_" + to_string(i)].curFrame = curFrame;
		sampleData["GRASS_" + to_string(i)].maxFrame = maxFrame;
	}

	//LAVA
	path = L"Textures/Object/Name/LAVA.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["LAVA_NAME"].path = path;
	sampleData["LAVA_NAME"].curFrame = curFrame;
	sampleData["LAVA_NAME"].maxFrame = maxFrame;

	path = L"Textures/Object/Image/LAVA_ALL.png";
	for (int i = 1; i < 17; i++)
	{
		curFrame = { i - 1.0f,0 };
		maxFrame = { 16,3 };
		cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
		cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
		sampleData["LAVA_" + to_string(i)].path = path;
		sampleData["LAVA_" + to_string(i)].curFrame = curFrame;
		sampleData["LAVA_" + to_string(i)].maxFrame = maxFrame;
	}

	//LAVA
	path = L"Textures/Object/Name/WALL.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["WALL_NAME"].path = path;
	sampleData["WALL_NAME"].curFrame = curFrame;
	sampleData["WALL_NAME"].maxFrame = maxFrame;

	path = L"Textures/Object/Image/WALL_ALL.png";
	for (int i = 1; i < 17; i++)
	{
		curFrame = { i - 1.0f,0 };
		maxFrame = { 16,3 };
		cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
		cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
		sampleData["WALL_" + to_string(i)].path = path;
		sampleData["WALL_" + to_string(i)].curFrame = curFrame;
		sampleData["WALL_" + to_string(i)].maxFrame = maxFrame;
	}

	//WATER
	
	path = L"Textures/Object/Name/WATER.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["WATER_NAME"].path = path;
	sampleData["WATER_NAME"].curFrame = curFrame;
	sampleData["WATER_NAME"].maxFrame = maxFrame;

	path = L"Textures/Object/Image/WATER_ALL.png";
	for (int i = 1; i < 17; i++)
	{
		curFrame = { i - 1.0f,0 };
		maxFrame = { 16,3 };
		cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
		cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
		sampleData["WATER_" + to_string(i)].path = path;
		sampleData["WATER_" + to_string(i)].curFrame = curFrame;
		sampleData["WATER_" + to_string(i)].maxFrame = maxFrame;
	}

	//SKULL
	path = L"Textures/Object/Name/SKULL.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["SKULL_NAME"].path = path;
	sampleData["SKULL_NAME"].curFrame = curFrame;
	sampleData["SKULL_NAME"].maxFrame = maxFrame;

	path = L"Textures/Object/Image/SKULL_ALL.png";
	for (int i = 1; i < 5; i++)
	{
		curFrame = { i - 1.0f,0 };
		maxFrame = { 4,3 };
		cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
		cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
		sampleData["SKULL_" + to_string(i)].path = path;
		sampleData["SKULL_" + to_string(i)].curFrame = curFrame;
		sampleData["SKULL_" + to_string(i)].maxFrame = maxFrame;
	}

	//BaBa
	path = L"Textures/Object/Name/BABA.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["BABA_NAME"].path = path;
	sampleData["BABA_NAME"].curFrame = curFrame;
	sampleData["BABA_NAME"].maxFrame = maxFrame;

	path = L"Textures/Object/Image/BABA_ALL.png";
	for (int i = 1; i < 8; i++)
	{
		curFrame = { i - 1.0f,0 };
		maxFrame = { 8,3 };
		cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
		cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
		sampleData["BABA_" + to_string(i)].path = path;
		sampleData["BABA_" + to_string(i)].curFrame = curFrame;
		sampleData["BABA_" + to_string(i)].maxFrame = maxFrame;
	}

	//Is
	path = L"Textures/PROPERTY/IS.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["PROPERTY_IS"].path = path;
	sampleData["PROPERTY_IS"].curFrame = curFrame;
	sampleData["PROPERTY_IS"].maxFrame = maxFrame;
	
	//DEFEAT
	path = L"Textures/PROPERTY/DEFEAT.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["PROPERTY_DEFEAT"].path = path;
	sampleData["PROPERTY_DEFEAT"].curFrame = curFrame;
	sampleData["PROPERTY_DEFEAT"].maxFrame = maxFrame;
	
	//HOT
	path = L"Textures/PROPERTY/HOT.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["PROPERTY_HOT"].path = path;
	sampleData["PROPERTY_HOT"].curFrame = curFrame;
	sampleData["PROPERTY_HOT"].maxFrame = maxFrame;
	
	//MELT
	path = L"Textures/PROPERTY/MELT.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["PROPERTY_MELT"].path = path;
	sampleData["PROPERTY_MELT"].curFrame = curFrame;
	sampleData["PROPERTY_MELT"].maxFrame = maxFrame;

	//PUSH
	path = L"Textures/PROPERTY/PUSH.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["PROPERTY_PUSH"].path = path;
	sampleData["PROPERTY_PUSH"].curFrame = curFrame;
	sampleData["PROPERTY_PUSH"].maxFrame = maxFrame;

	//SINK
	path = L"Textures/PROPERTY/SINK.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["PROPERTY_SINK"].path = path;
	sampleData["PROPERTY_SINK"].curFrame = curFrame;
	sampleData["PROPERTY_SINK"].maxFrame = maxFrame;
	
	//STOP
	path = L"Textures/PROPERTY/STOP.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["PROPERTY_STOP"].path = path;
	sampleData["PROPERTY_STOP"].curFrame = curFrame;
	sampleData["PROPERTY_STOP"].maxFrame = maxFrame;
	
	//WIN
	path = L"Textures/PROPERTY/WIN.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["PROPERTY_WIN"].path = path;
	sampleData["PROPERTY_WIN"].curFrame = curFrame;
	sampleData["PROPERTY_WIN"].maxFrame = maxFrame;
	
	//YOU
	path = L"Textures/PROPERTY/YOU.png";
	curFrame = { 0,0 };
	maxFrame = { 1,3 };
	cutSize.x = Texture::Add(path)->GetSize().x / maxFrame.x;
	cutSize.y = Texture::Add(path)->GetSize().y / maxFrame.y;
	sampleData["PROPERTY_YOU"].path = path;
	sampleData["PROPERTY_YOU"].curFrame = curFrame;
	sampleData["PROPERTY_YOU"].maxFrame = maxFrame;


}
