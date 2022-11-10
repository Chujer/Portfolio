//High Level Shader Language ����

struct VertexInput
{
	float4 position : POSITION0;
	float4 color : COLOR0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float4 color : COLOR0;
};

cbuffer TransformData : register(b0)
{
	matrix _world;
	matrix _view;
	matrix _projection;
}

PixelInput VS(VertexInput input)			//Vertex Shader		������ 3Dȭ �Ͽ� ����
{
	PixelInput output;
	output.position = mul(input.position, _world);
	output.color = mul(input.color, _view);
	output.position = mul(output.position, _projection);
	output.color = input.color;
	return output;
}

float4 PS(PixelInput input) : SV_Target		 //Pixel Shader		��ĥ
{
	return input.color;
}