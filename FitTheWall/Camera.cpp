#include "Camera.h"

Camera::Camera(GraphicsManager* graphicsManager):
	graphicsManager(graphicsManager)
{
	fov = 0.25 * 3.14f; // fov ~ 45 degrees in radians
	nearField = 0.1f;
	farField = 1000;

	position = XMFLOAT3(0, 4, -20);
	up = XMFLOAT3(0, 1, 0);
	forward = XMFLOAT3(0, 0, 1);

	view = XMMATRIX();
	projection = XMMATRIX();
}

Camera::~Camera()
{
	cameraBuffer->Release();
}

void Camera::InitCamera(float aspectRatio)
{
	view = XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&forward), XMLoadFloat3(&up));
	projection = XMMatrixPerspectiveFovLH(fov, aspectRatio, nearField, farField);
	
	view= XMMatrixTranspose(view);
	projection = XMMatrixTranspose(projection);

	graphicsManager->CreateCameraBuffer(cameraBuffer);
}

void Camera::Update()
{
	graphicsManager->UpdateCameraBuffer(cameraBuffer, view, projection, position);
}

XMFLOAT3 Camera::getPosition()
{
	return position;
}

void Camera::SetPosition(XMFLOAT3 pos)
{
	position = pos;
	view = XMMatrixTranspose(XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&forward), XMLoadFloat3(&up)));
}

void Camera::SetForward(XMFLOAT3 forwad)
{
	forward = forwad;
	view = XMMatrixTranspose(XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&forward), XMLoadFloat3(&up)));
}

ID3D11Buffer* Camera::GetCameraBuffer()
{
	return cameraBuffer;
}

XMMATRIX Camera::GetViewMatrix()
{
	return view;
}

XMMATRIX Camera::GetProjectionMatrix()
{
	return projection;
}
