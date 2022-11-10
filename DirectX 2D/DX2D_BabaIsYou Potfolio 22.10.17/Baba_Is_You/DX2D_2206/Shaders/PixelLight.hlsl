//PixelLight

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

cbuffer IndexBuffer : register(b1)
{
    int index;
    int range;
}

cbuffer SizeBuffer : register(b2)
{
    float2 imageSize;
    float2 lightPos;
}

float4 Light(float2 uv)
{
    float4 albedo = map.Sample(samp, uv);
    
    float2 pixelCoord = uv * imageSize;
    
    float dist = distance(lightPos, pixelCoord);
    
    if(dist < range)
        return albedo;
    
    return float4(albedo.rgb * 0.1f, albedo.a);
}

float4 LightIntensity(float2 uv)
{
    float4 albedo = map.Sample(samp, uv);
    
    float2 pixelCoord = uv * imageSize;
    
    float dist = distance(lightPos, pixelCoord);
    
    float value = dist / range;
    
    float3 color = albedo.rgb - (value * value);
    
    if(value >= 0.9f)
        return float4(albedo.rgb * 0.1f, albedo.a);
    
    return float4(color, albedo.a);
}

float4 PS(PixelInput input) : SV_TARGET
{
    if(index == 1)
        return Light(input.uv);
    if (index == 2)
        return LightIntensity(input.uv);
    
    float4 result = map.Sample(samp, input.uv);
    //result.a = 1;
    result = pow(result, 0.5f);
    
    return result * color;
}