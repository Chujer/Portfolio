#pragma once

class MapEditerScene : public Scene
{
public:
	MapEditerScene();
	~MapEditerScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void CreateTemp();

private:
	vector<Button*> samplBtns;
};