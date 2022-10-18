#include "Framework.h"

Object::Object()
{
	Texture* texture = Texture::Add(L"Textures/Object/Image/VAVA.png");
	Vector2 cutSize = texture->GetSize() / Vector2(3, 8);

	vector<Frame*> frame;
	frame.push_back(new Frame(L"Textures/Object/Image/VAVA.png", cutSize.x * 0, cutSize.y * 2, cutSize.x, cutSize.y));
	frame.push_back(new Frame(L"Textures/Object/Image/VAVA.png", cutSize.x * 1, cutSize.y * 2, cutSize.x, cutSize.y));
	frame.push_back(new Frame(L"Textures/Object/Image/VAVA.png", cutSize.x * 2, cutSize.y * 2, cutSize.x, cutSize.y));
	clips[0] = new Clip(frame, true,0.3f);
	curClip = clips[0];
	curClip->Play();

}

Object::~Object()
{
}

void Object::Update()
{
	AnimObject::Update();
	curClip->Update();
}

void Object::Render()
{
	AnimObject::Render();
	curClip->Render();
}
