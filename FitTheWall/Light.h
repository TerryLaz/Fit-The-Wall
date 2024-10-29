#pragma once

#include<d3d11.h>
#include<DirectXMath.h>

class GraphicsManager;

using namespace DirectX;
struct DirectionalLight
{
	XMFLOAT3 direction;
	float pad = 0;
	XMFLOAT4 ambient;
	XMFLOAT4 color;
};

struct PointLight : DirectionalLight
{
	XMFLOAT3 position;
	float range;
	XMFLOAT3 attenuation;
	float pad = 0;
};

struct SpotLight : PointLight
{
	float cone;
	XMFLOAT3 movement; //pad, används bara på cpu för att beräkna rörelse
};


class Light
{
private:
	GraphicsManager* graphicsManager;
	ID3D11Buffer* lightBuffer;

	DirectionalLight dirLight;
	DirectionalLight dirLight2;
	PointLight pointLight;
	SpotLight spotLight;


public:
	Light(GraphicsManager* graphicsManager);
	~Light();

	void Update();
	void ClearLightBuffer();

	void SetDirectionalLight(XMFLOAT3 dir, XMFLOAT4 amb, XMFLOAT4 diff);
	void SetDirectionalLight2(XMFLOAT3 dir, XMFLOAT4 amb, XMFLOAT4 diff);
	void SetPointLight(XMFLOAT3 pos, float r, XMFLOAT3 att);
	void SetSpotLight(XMFLOAT3 pos, float r, XMFLOAT3 att, float c);

	ID3D11Buffer* GetLightBuffer();
};

