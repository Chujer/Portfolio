#pragma once

class Goomba : public Enemy
{
public:
	Goomba();
	~Goomba();

	virtual void Update() override;
	//virtual void Render(HDC hdc) override;

	virtual void Move() override;

	virtual void SetAniamtion() override;
	virtual void CreateAnimation() override;

private:
};