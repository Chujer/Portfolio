#include "Framework.h"
#include "HitBox.h"

HitBox::HitBox(Vector3 position, Vector3 size, string tag)
	: Character(position, size)
{
	animRect = new AnimationRect(position, size);
	animator = new Animator();
	this->Tag = tag;
	Texture2D* srcTex = new Texture2D(TexturePath + L"Empty.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());
	clips = new AnimationClip(L"Empty", srcTex, 1, Vector2(0, 0), texSize, 1.0f / 10.0f);
	animator->AddAnimClips(clips);
	animator->SetCurrentAnimClip(L"Empty");
	animRect->SetAnimation(animator);
}

HitBox::~HitBox()
{
	SAFE_DELETE(clips);
}

void HitBox::SetReHitBox(Vector3 position, Vector3 size, bool a)
{
	animRect = new AnimationRect(position, size, true);
	animator = new Animator();
	Texture2D* srcTex = new Texture2D(TexturePath + L"Empty.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());
	clips = new AnimationClip(L"Empty", srcTex, 1, Vector2(0, 0), texSize, 1.0f / 10.0f);
	animator->AddAnimClips(clips);
	animator->SetCurrentAnimClip(L"Empty");
	animRect->SetAnimation(animator);
}

void HitBox::Update()
{
	if(hitBoxPosition!=nullptr)
		animRect->SetPosition(*hitBoxPosition);
	animRect->Update();
}

void HitBox::Render()
{
	sb->SetPoint(1);
	sb->SetPSBuffer(0);
	animRect->Render();
}

void HitBox::Move()
{
}

void HitBox::MoveHitBox(Vector3 plusPos)
{
	animRect->SetPosition(*animRect->GetPosition() + plusPos);
}

bool HitBox::GetActive()
{
	return false;
}

void HitBox::SetActive(bool active)
{
}
