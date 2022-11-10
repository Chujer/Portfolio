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
Texture2D _sourceTex2 : register(t1);
SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, input.uv);
    
    float3 greyscale = 0;
    if(selection == 1)
        return _sourceTex.Sample(_samp, float2(input.uv));
    else if(selection == 2)
        greyscale = (color.r + color.g + color.b) / 3.0f;
      //greyscale = color.r * 0.299f, color.g * 0.587f, color.b * 0.114f; // 진정한 그레이 값
    else if(selection == 3)
        greyscale = dot(color.rgb, float3(.299f, .587f, .114f));
    else if(selection ==4)
    {
        float r, g, b;
        r = dot(color.rgb, float3(0.393f, 0.769f, 0.189f));
        g = dot(color.rgb, float3(0.349f, 0.686f, 0.168f));
        b = dot(color.rgb, float3(0.272f, 0.534f, 0.131f));
        greyscale = float3(r, g, b);
    }
    else
        greyscale = color.rgb;
    
    return float4(greyscale, 1);
    
 
}