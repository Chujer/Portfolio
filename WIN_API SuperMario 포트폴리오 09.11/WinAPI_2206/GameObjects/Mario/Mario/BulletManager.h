#pragma once

class BulletManager : public Singleton<BulletManager>
{
private:
	const UINT MAX_BULLET_COUNT = 25;
	const float SHOOT_DELAY_TIME = 0.2f;
public:
	BulletManager();
	~BulletManager();

	void Update();
	void Render(HDC hdc);

	void CreateBullet(Vector2 position, bool isLeft);
	//void IsCollisionBlockToBullet(Tile* block);

private:
	vector<Bullet*> bullets;
	float shootTime = 0;
	Vector2 overlapSize;
};