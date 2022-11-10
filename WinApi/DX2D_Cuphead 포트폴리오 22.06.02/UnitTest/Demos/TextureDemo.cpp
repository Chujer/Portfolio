#include "stdafx.h"
#include "TextureDemo.h"

#include "Geomatries/Text.h"
#include "Geomatries/AnimationRect.h"

void TextureDemo::Init()
{
	t = new Text(Vector3(WinMaxWidth/2, WinMaxHeight/2, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), 0.0f, TexturePath + L"Back.png");
}

void TextureDemo::Destroy()
{
	SAFE_DELETE(t);
}

void TextureDemo::Update()
{
	t->Update();
}

void TextureDemo::Render()
{
	t->Render();
}

void TextureDemo::PostRender()
{
}

void TextureDemo::GUI()
{
}
