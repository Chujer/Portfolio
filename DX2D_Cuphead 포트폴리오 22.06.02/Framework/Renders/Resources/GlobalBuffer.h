#pragma once

#include "Framework.h"

class WorldBuffer : public ShaderBuffer
{
public:
	WorldBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		D3DXMatrixIdentity(&data.world);
	}

	void SetWorld(Matrix world)
	{
		D3DXMatrixTranspose(&data.world, &world);
	}

	struct Data
	{
		Matrix world;
	};

private:
	Data data;
};

class VPBuffer : public ShaderBuffer
{
public :
	VPBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		D3DXMatrixIdentity(&data.view);
		D3DXMatrixIdentity(&data.projection);
	}

	void SetView(Matrix view)
	{
		D3DXMatrixTranspose(&data.view, &view);
	}

	void SetProj(Matrix projection)
	{
		D3DXMatrixTranspose(&data.projection, &projection);
	}

	struct Data
	{
		Matrix view;
		Matrix projection;
	};

private:
	Data data;
};