struct VertexInput
{
	float4 position : POSITION0;
	float2 uv : TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
    float2 uv : TEXCOORD0;
};

cbuffer WorldBuffer : register(b0)
{
    matrix _world;
};

cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _projection;
}
cbuffer ShadedBuffer : register(b0)
{
	int selection;
}

PixelInput VS(VertexInput input)
{
	PixelInput output;
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
	output.uv = input.uv;
	return output;
}

Texture2D _sourceTex : register(t0);
//Texture2D _sourceTex2 : register(t1);
SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, input.uv);
	float3 hit = 0;
    

	if (selection == 1)
	{
		if (input.uv.x < 0.01f ||
			input.uv.x > 0.99f ||
			input.uv.y < 0.01f ||
			input.uv.y > 0.99f)
		{
			return float4(1, 0, 0, 1);
		}
	}

	if (selection == 2)		//≈ı∏Ì
	{
		return color - float4(0, 0, 0, 0.5f);
	}
    
    return color;
 
}