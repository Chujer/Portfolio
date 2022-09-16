#pragma once

#include "Character.h"

class Monster : public Character
{
public:
	Monster(Vector3 position, Vector3 size);
	~Monster();


	virtual void Update() override;
	virtual void Render() override;
	virtual void Move() override;

//	bool AABB(BoundingBox* other) { return animRect->GetBox()->AABB(other); }
	AnimationRect* GetAnimRect() { return animRect; }

private:
	class Control* control = nullptr;
	class BoundingBox* box = nullptr;
	vector<AnimationClip*> clips;

};