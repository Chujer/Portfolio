#pragma once

class EnemyManager : public Singleton<EnemyManager>
{
public:
	enum MonsterType
	{
		C_GOOMBA, C_TUTLE, C_FLOWER,
		F_GOOMBA, F_TUTLE, F_FLYTUTLE, F_FLOWER
	};
public:
	EnemyManager();
	~EnemyManager();

	vector<Enemy*> GetEnemy() { return enemys; }

	void Update();
	void Render(HDC hdc);

	void SetEnemyCount(int count) { enemys.resize(count); }

	void CreateEnemy(MonsterType mType, Vector2 position);
	void IsCollisionMarioToEnemy(Mario* mario);
	void IsCollisionBulletToEnemy(Bullet* bullet);

private:
	vector<Enemy*> enemys;
	int enemyIndex = 0;
};