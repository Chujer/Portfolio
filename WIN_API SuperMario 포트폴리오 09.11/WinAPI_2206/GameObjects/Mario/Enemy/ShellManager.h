#pragma once

class ShellManager : public Singleton<ShellManager>
{
public:
	ShellManager();
	~ShellManager();

	void Update();
	void Render(HDC hdc);

	Shell* SetShell(Tutle* tutle);
	vector<Shell*> GetShells() { return shells; }

	void IsCollisionMarioToShell(Mario* mario);
	void IsCollisionEnemyToShell(Enemy* enemy);

private:
	vector<Shell*> shells;
	Vector2 overlapSize;
};