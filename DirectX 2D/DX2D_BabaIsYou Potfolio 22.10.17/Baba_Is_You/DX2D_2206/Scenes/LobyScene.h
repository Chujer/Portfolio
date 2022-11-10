#pragma once

class LobyScene : public Scene
{
public:
	LobyScene();
	~LobyScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void SetEndPos();

private:
	Quad* quad;
	Quad* pressQuad;

	Vector2 StartPos;
	Vector2 endPos;
	Vector2 direction;

	Float4 endColor;

	float blinkSpeed = 0.9f;
};