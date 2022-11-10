#include "Framework.h"
#include "Monster.h"

Monster::Monster(Vector3 position, Vector3 size)
	:Character(position, size)
{
	Texture2D* srcTex = new Texture2D(TexturePath + L"monster.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	clips.push_back(new AnimationClip(L"IdleR", srcTex, 7, Vector2(0, 0), Vector2(texSize.x * 0.7f, texSize.y * 0.1f), 1.0f / 10.0f));

	animator->AddAnimClips(clips);

	animator->SetCurrentAnimClip(L"IdleR");

	animRect->SetAnimation(animator);

	SAFE_DELETE(srcTex);

	control = new Control(animRect->GetAnimator(), animRect->GetPosition());
}

Monster::~Monster()
{
	SAFE_DELETE(control);
}

void Monster::Update()
{
	animator->Update();
	animRect->Update();
}

void Monster::Render()
{
	animRect->Render();
}

void Monster::Move()
{
	//control->Right('F', 100);
}
