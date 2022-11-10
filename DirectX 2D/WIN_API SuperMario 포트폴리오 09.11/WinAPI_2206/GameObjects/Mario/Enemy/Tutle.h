#pragma once

class Tutle :public Enemy
{
public:
	Tutle();
	~Tutle();

	void ReturnAni();

	virtual void Update() override;
	//virtual void Render(HDC hdc) override;

	virtual void Move() override;

	virtual void SetAniamtion() override;
	virtual void CreateAnimation() override;

	void Resurection(Vector2 position);
	bool GetCave() { return isCave; }

	void SetShell();


private:
	bool isLeft = false;
	class Shell* shell;
};