#pragma once
#include "Game/Character.h"


class HitBox : public Character
{
public:
	// Character을(를) 통해 상속됨
	HitBox(Vector3 position, Vector3 size, string tag);
	~HitBox();
	void SetReHitBox(Vector3 position, Vector3 size, bool a);
	virtual void Update() override;
	virtual void Render() override;
	virtual void Move() override;
	virtual bool GetActive() override;
	virtual void SetActive(bool active) override;
	Vector3 GetPosition()
	{
		return *animRect->GetPosition();
	}
	
	//bool AABB(BoundingBox* other) { return animRect->GetBox()->AABB(other); }
	AnimationRect* GetAnimRect() { return animRect; }
	void MoveHitBox(Vector3 position);
	
private:
	class AnimationClip* clips;
	Vector3* hitBoxPosition = nullptr;
	Vector3* hitBoxSize = nullptr;
};

