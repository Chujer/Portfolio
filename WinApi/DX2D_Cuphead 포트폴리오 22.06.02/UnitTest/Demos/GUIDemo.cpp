#include "stdafx.h"
#include "GUIDemo.h"

void GUIDemo::Init()
{
}

void GUIDemo::Destroy()
{
}

void GUIDemo::Update()
{
}

void GUIDemo::Render()
{
}

void GUIDemo::PostRender()
{
}

void GUIDemo::GUI()
{
	static bool temp = true;
	ImGui::ShowDemoWindow(&temp);
	PrintFPS();
	PrintMousePose();
	Graphics::Get()->GUI();
}

void GUIDemo::PrintFPS()
{
	static bool bOpen = true;
	ImGui::SetNextWindowPos({ WinMaxWidth - 100, 15 });
	ImGui::SetNextWindowSize(ImVec2(200, 15));
	ImGui::Begin
	(
		"FPS",
		&bOpen,
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove
	);
	{
		string frame = "FPS : " + to_string((int)ImGui::GetIO().Framerate);
		ImGui::Text(frame.c_str());
	}
	ImGui::End();
}

void GUIDemo::PrintMousePose()
{
	static bool bOpen = true;
	ImGui::SetNextWindowPos({ WinMaxWidth - 100, 30 });
	ImGui::SetNextWindowSize(ImVec2(200, 60));
	ImGui::Begin
	(
		"MousePose",
		&bOpen,
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove
	);
	{
		string x = "X : " + to_string((int)Mouse::Get()->GetPosition().x);
		string y = "Y : " + to_string((int)Mouse::Get()->GetPosition().y);
		
		ImGui::TextColored(ImVec4(1, 0, 0, 1), x.c_str());
		ImGui::Text(y.c_str());
	}
	ImGui::End();
}
