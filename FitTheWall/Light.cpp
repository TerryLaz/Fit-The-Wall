#include "Light.h"
#include"GraphicsManager.h"

Light::Light(GraphicsManager* graphicsManager):
	graphicsManager(graphicsManager)
{
	graphicsManager->CreateLightBuffer(lightBuffer);
}

Light::~Light()
{
	lightBuffer->Release();
}

void Light::ClearLightBuffer()
{
	dirLight.direction = XMFLOAT3(0, 0, 0);
	graphicsManager->UpdateLightBuffer(lightBuffer, dirLight, dirLight2, pointLight, spotLight);
}

void Light::Update()
{
	spotLight.direction.x += spotLight.movement.x;
	if (spotLight.direction.x >= 2 || spotLight.direction.x <= -2)
		spotLight.movement.x *= -1;
	spotLight.direction.y += spotLight.movement.y;
	if (spotLight.direction.y >= 0 || spotLight.direction.y <= -1)
		spotLight.movement.y *= -1;
	spotLight.direction.z += spotLight.movement.z;
	if (spotLight.direction.z >= 3 || spotLight.direction.z <= 0)
		spotLight.movement.z *= -1;


	graphicsManager->UpdateLightBuffer(lightBuffer, dirLight, dirLight2, pointLight, spotLight);
}

void Light::SetDirectionalLight(XMFLOAT3 dir, XMFLOAT4 amb, XMFLOAT4 diff)
{
	DirectionalLight light;
	light.direction = dir;
	light.ambient = amb;
	light.color = diff;
	dirLight = light;
}

void Light::SetDirectionalLight2(XMFLOAT3 dir, XMFLOAT4 amb, XMFLOAT4 diff)
{
	DirectionalLight light;
	light.direction = dir;
	light.ambient = amb;
	light.color = diff;
	dirLight2 = light;
}

void Light::SetPointLight(XMFLOAT3 pos, float r, XMFLOAT3 att)
{
	PointLight light;
	light.position = pos;
	light.range = r;
	light.attenuation = att;
	light.color = XMFLOAT4(0.7f, 1.0f, 1.0f, 1.0f);
	pointLight = light;
}



void Light::SetSpotLight(XMFLOAT3 pos, float r, XMFLOAT3 att, float c)
{
	SpotLight light;
	light.position = pos;
	light.range = r;
	light.attenuation = att;
	light.cone = c;
	light.direction = XMFLOAT3(0.0f, -1.f, 0.5f);
	light.color = XMFLOAT4(1.5f, 0.5f, 1.5f, 1.0f);
	light.movement = XMFLOAT3(0.04f, 0.04f, 0.04f);
	spotLight = light;
}

ID3D11Buffer* Light::GetLightBuffer()
{
	return lightBuffer;
}


