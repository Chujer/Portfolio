#pragma once
#include "Game/Character.h"

class TextureInfo
{
public:
	TextureInfo(Vector2 texSize, int imageCutX, int imageCutY)
	{
		this->texSize = texSize;
		this->scsizeX = texSize.x / imageCutX;
		this->scsizeY = texSize.y / imageCutY;
	}
	Vector2 texSize;
	float scsizeX;
	float scsizeY;
};

class Effect : public Character
{
public:
	Effect(Vector3 position, Vector3 size, wstring name);
	void ChangeEffect(Vector3 position, Vector3 size, bool a)
	{
		animRect = new AnimationRect(position, size, true);
		animRect->SetAnimation(animator);
	}
	~Effect();
	virtual void Update() override;
	virtual void Render() override;
	virtual void Move() override;
	virtual bool GetActive() override;
	virtual void SetActive(bool active) override;
	Animator* GetAnimator() { return animator; }

private:
	wstring eName;
	vector<AnimationClip*> clips;
	bool active;
	int point = 0;
};

