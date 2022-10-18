#include "Framework.h"

ObjectSample::ObjectSample()
{
	SetSampleClips();
}

ObjectSample::~ObjectSample()
{
}

void ObjectSample::SetSampleClips()
{
	//FLAG
	vector<Frame*> frams;
	wstring path = L"Textures/Object/Image/FLAG.png";
	Texture* texture = Texture::Add(path);
	Vector2 size = texture->GetSize() / Vector2(2, 1);
	frams.push_back(new Frame(path, size.x * 0, size.y * 0, size.x, size.y));
	frams.push_back(new Frame(path, size.x * 1, size.y * 0, size.x, size.y));
	sampleClips["FLAG"] = new Clip(frams, true, 0.3f);

	path = L"Textures/Object/ImageGRASS_ALL.png";
	
}
