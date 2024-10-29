struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float2 uv : UV;
};


Texture2D myTexture;
SamplerState mySampler;

float4 main(PixelShaderInput input) : SV_TARGET
{
	float4 textureColor = myTexture.Sample(mySampler,input.uv);
	//return textureColor;
	//textureColor.w /= 10;
	return float4(textureColor.x, textureColor.y, textureColor.z, textureColor.w);
}