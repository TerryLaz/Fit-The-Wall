#pragma once
#include<DirectXMath.h>
#include<d3d11.h>
#include "GraphicsManager.h"

using namespace DirectX;
class Camera
{
private:
	float fov;
	float nearField;
	float farField;

	XMFLOAT3 position;
	XMFLOAT3 up;
	XMFLOAT3 forward;

	XMMATRIX view;
	XMMATRIX projection;

	ID3D11Buffer* cameraBuffer;

	GraphicsManager* graphicsManager;

public:
	Camera(GraphicsManager* graphicsManager);
	~Camera();

	void InitCamera(float aspectRatio);
	void Update();

	XMFLOAT3 getPosition();
	void SetPosition(XMFLOAT3 pos);
	void SetForward(XMFLOAT3 forwad);
	ID3D11Buffer* GetCameraBuffer();
	XMMATRIX GetViewMatrix();
	XMMATRIX GetProjectionMatrix();

};

