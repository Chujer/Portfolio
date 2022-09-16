#include "stdafx.h"
#include "Program.h"
#include "Systems/Window.h"

#include "Demos/GUIDemo.h"
#include "Demos/TextureDemo.h"
#include "Demos/AnimationDemo.h"
#include "Demos/PlayerDemo.h"
#include "Demos/FileStreamDemo.h"
#include "Demos/Test.h"
#include "Demos/GameDemo.h"

void Program::Init()
{
	States::Create();
	Camera::Create();

	//Push(new FileStreamDemo());

	Push(new TextureDemo());
	//Push(new GameDemo());
	//Push(new PlayerDemo());
	Push(new Test());
}

void Program::Destroy()
{
	cout << "des";
	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
}


void Program::Update()
{
	
	for (IObject* obj : objs)
		obj->Update();


	Camera::Get()->Move();
	/*time += Time::Delta();
	if (time > 1)
	{
		time = 0;
		a++;
		cout << a<<endl;
	}*/
}

void Program::Render()
{
	Camera::Get()->Render();
	for (IObject* obj : objs)
		obj->Render();
}

void Program::PostRender()
{
	for (IObject* obj : objs)
		obj->PostRender();
}

void Program::GUI()
{
	for (IObject* obj : objs)
		obj->GUI();
}

void Program::Push(IObject * obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevINSTANCE, LPSTR param, int command)
{
	//프로그램의 인스턴스 핸들 / 프로그램의 식별자 / 인스턴스는 객체 라고 생각하면됨.
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);
	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;
}
