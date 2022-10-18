#pragma once

class BabaScene : public Scene
{
public:
	BabaScene();
	~BabaScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Object* temp;
};