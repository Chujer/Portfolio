#pragma once

class MapEditerScene : public Scene
{
public:
	MapEditerScene();
	~MapEditerScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void CreateTemp();

private:
	vector<Button*> samplBtns;
};