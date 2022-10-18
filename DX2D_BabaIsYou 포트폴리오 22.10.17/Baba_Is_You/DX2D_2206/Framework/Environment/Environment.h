#pragma once

class Environment : public Singleton<Environment>
{
public:
	Environment();
	~Environment();

	Camera * GetMainCamera() { return mainCamera; }

	void SetAlphaBlend();
	void SetAdditiveBlend();
private:
	void CreateProjection();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();

private:
	Camera * mainCamera;
	MatrixBuffer * projection;

	ID3D11SamplerState * samplerState;
	ID3D11BlendState * alphaBlendState;
	ID3D11BlendState * additiveBlendState;
	ID3D11RasterizerState * rasterizerState;
};
