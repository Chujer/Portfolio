#pragma once

class BabaScene : public Scene
{
public:
	BabaScene();
	~BabaScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Object* temp;
};