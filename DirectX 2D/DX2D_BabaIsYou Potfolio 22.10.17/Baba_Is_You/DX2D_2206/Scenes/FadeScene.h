#pragma once

class FadeScene : public Scene
{
public:
	enum FadeMode
	{
		FADE_IN, FADE_OUT, NONE
	};
public:
	FadeScene();
	~FadeScene();

	void FadeIn();
	void FadeOut();
	void Stop();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Quad* quads[4];
	Vector2 firstPosition[4];
	FadeMode mode = NONE;
	float speed = 300;

};