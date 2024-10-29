struct VertexShaderInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 uv : UV;
	float4 bones : BONE;
	float4 weight : WEIGHT;

};

struct VertexShaderOutput
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv : UV;
	float3 worldPos : WORLD;
	float3 cameraPos : CAMERAPOS;
};

cbuffer cameraBuffer
{
	matrix viewMatrix;
	matrix projectionMatrix;
	float3 cameraPosition;
};

cbuffer modelBuffer
{
	matrix worldMatrix;
};

VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;
	output.position = float4(input.position, 1.0f);
	output.position = mul(output.position, worldMatrix);
	output.worldPos = output.position;
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.normal = mul(input.normal, worldMatrix);
	output.uv = input.uv;
	output.cameraPos = cameraPosition;
	return output;
}