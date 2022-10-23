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
	map<string, InstanceQuad*> instanceQuads;
	Object* object;
	Object* object2;

};