#include "stdafx.h"
#include "AnimationDemo.h"

#include "Geomatries/AnimationRect.h"

void AnimationDemo::Init()
{
	ar = new AnimationRect({ 840, 450, 0 }, { 300, 300, 1 });
}

void AnimationDemo::Destroy()
{
	SAFE_DELETE(ar);
}

void AnimationDemo::Update()
{
	ar->Update();
}

void AnimationDemo::Render()
{
	ar->Render();
}

void AnimationDemo::PostRender()
{
}

void AnimationDemo::GUI()
{
}
