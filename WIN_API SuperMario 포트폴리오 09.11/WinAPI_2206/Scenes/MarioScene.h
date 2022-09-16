#pragma once

class MarioScene : public Scene
{
public:
	MarioScene();
	~MarioScene();

	void SetStage(void* stage);
	void removeStage();
	virtual void Start() override;

	void Update();
	void Render(HDC hdc);

	void Collision();

private:
	Mario* player;
	ImageRect* texture;
	ImageRect* SkyTexture;
	ImageRect* CaveTexture;

	int x;
};