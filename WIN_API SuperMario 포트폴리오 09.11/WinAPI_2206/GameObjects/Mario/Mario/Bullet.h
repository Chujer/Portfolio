#pragma once

class Bullet : public ImageRect
{
private:
	const float GRAVITY = 1800.0f;
	const float BOUND_FOWER = 150.0f;
public:
	Bullet();
	~Bullet();

	void Update();
	void Render(HDC hdc);
	void CreateBullet(Vector2 position, bool isLeft);
	void IsCollisionGround();

private:
	void Move();
	void StartMove();

private:
	Vector2 velocity;
	Animation* animation;
	float speed;
	float gravity;
	float time;
	
	bool isTuchGround = false;
};