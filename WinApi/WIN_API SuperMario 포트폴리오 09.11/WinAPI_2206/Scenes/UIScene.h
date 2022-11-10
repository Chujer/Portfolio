#pragma once

class UIScene : public Scene
{
private:
	const float WAIT_TIME = 3.0f;
public:
	UIScene();
	~UIScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	
private:
	float time =0;
	HBRUSH hbrush;
	ImageRect* mario;
};