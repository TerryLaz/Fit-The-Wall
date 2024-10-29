struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv : UV;
	float3 worldPos : WORLD;
	float3 cameraPos : CAMERAPOS;
};

struct DirectionalLight
{
	float3 direction;
	float pad;
	float4 ambient;
	float4 color;
};

struct PointLight : DirectionalLight
{
	float3 position;
	float range;
	float3 attenuation;
	float pad;
};

struct SpotLight : PointLight
{
	float cone;
	float3 pad;
};

cbuffer lights : register(b0)
{
	DirectionalLight dirLight1;
	DirectionalLight dirLight2;
	PointLight pLight;
	SpotLight sLight;
};

Texture2D myTexture;
SamplerState mySampler;

float Toonify(float intensity)
{
	if (intensity < 0.3)
		intensity = 0.3;
	else if (intensity < 0.7)
		intensity = 0.7;
	else if (intensity < 0.99)
		intensity = 1.0;
	else
		intensity *= 1.1;

	return intensity;
}

float4 Toonify(float4 color)
{
	float l = length(color);
	color = normalize(color);
	if (l < 0.01)
		color *= 0.0;
	else if (l < 0.1)
		color *= 0.2;
	else if (l < 0.9)
		color *= 0.9;
	else if (l < 2)
		color *= 2;
	else
		color *= 3;

	return color;
}

float4 DirectionalLightColor(DirectionalLight light, PixelShaderInput input)
{
	float3 lightDir = normalize(-light.direction);

	float intensity = saturate(dot(input.normal, lightDir));


	float4 result = light.color * intensity;

	return result * light.color;
}
float4 PointLightColor(PointLight light, PixelShaderInput input)
{

	float3 lightToPixelVec = light.position - input.worldPos;
	float d = length(lightToPixelVec);
	float4 result = float4(0, 0, 0, 1);
	if (d < light.range)
	{
		lightToPixelVec /= d;
		float intensity = dot(lightToPixelVec, input.normal);


		result = intensity * light.color;
	}
	return result;
}
float4 SpotLightColor(SpotLight light, PixelShaderInput input)
{
	float3 lightToPixelVec = light.position - input.worldPos;
	float d = length(lightToPixelVec);
	float3 lightDir = normalize(light.direction);
	float4 result = float4(0, 0, 0, 1);
	if (d < light.range)
	{
		lightToPixelVec /= d;
		float intensity = dot(lightToPixelVec, input.normal);


		if (intensity > 0.0f)
		{
			result = light.color;
			result *= pow(max(dot(-lightToPixelVec, lightDir), 0.0f), light.cone) * intensity;
		}
	}

	return result;
}

float4 main(PixelShaderInput input) : SV_TARGET
{
	input.normal = normalize(input.normal);
	float4 baseColor = myTexture.Sample(mySampler,input.uv);
	float4 lightColor = float4(0, 0, 0, 1);

	if (!any(dirLight1.direction))
		return baseColor;

	float3 cameraToPixel = input.worldPos - input.cameraPos;

	if (dot(input.normal, cameraToPixel) < -0.3)
	{
		SpotLight spot = sLight;
		float4 spot1 = SpotLightColor(spot, input);
		spot.direction.x *= -1;
		spot.color = float4(0.5,1.0, 1.5, 1);
		float4 spot2 = SpotLightColor(spot, input);
		spot.direction.z *= -1;
		spot.color = float4(0.5, 1.5, 0.5, 1);
		float4 spot3 = SpotLightColor(spot, input);
		spot.direction.x *= -1;
		spot.color = float4(1.5, 0.9, 0.5, 1);
		float4 spot4 = SpotLightColor(spot, input);

		lightColor += Toonify(DirectionalLightColor(dirLight1, input) + DirectionalLightColor(dirLight2, input) + spot1 + spot2 + spot3 + spot4);

	}

	return lightColor * baseColor;

}