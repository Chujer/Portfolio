#pragma once

class MapEditerScene : public Scene
{
public:
	MapEditerScene();
	~MapEditerScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	ImageRect* texture;
};