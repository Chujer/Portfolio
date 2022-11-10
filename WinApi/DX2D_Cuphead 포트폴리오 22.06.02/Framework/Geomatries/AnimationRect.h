#pragma once

#include "Text.h"

class Animator;
class AnimationRect : public Text
{
public:
	AnimationRect(Vector3 position, Vector3 size);
	AnimationRect(Vector3 position, Vector3 size, bool changePoint);
	~AnimationRect();

	void Update();
	void Render();

	virtual void Move() override;

	void SetPosition(Vector3 position) { this->position = position; }
	void SetAnimation(Animator* animator) { this->animator = animator; }

	void Change_Size(Vector3 v) { size = v; }
	Animator* GetAnimator() { return animator; }
	Vector3* GetPosition() { return &position; }
	OBB* GetObb() { return obb; }

	BoundingBox* GetBox() { return box; }

private:
	class Animator* animator = nullptr;
	RectEdge* edge = nullptr;
	BoundingBox* box = nullptr;

	ID3D11SamplerState* point[2];
	ID3D11BlendState* bPoint[2];

	class OBB* obb;
	TransformData transform;
};