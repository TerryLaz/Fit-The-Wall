struct VertexShaderInput
{
	float3 position : POSITION;
	float2 uv : UV;

};

struct VertexShaderOutput
{
	float4 position : SV_POSITION;
	float2 uv : UV;
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
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.uv = input.uv;
	return output;
}