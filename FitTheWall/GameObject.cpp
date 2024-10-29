#include "GameObject.h"

GameObject::GameObject(GraphicsManager* graphicsManager) :
	graphicsManager(graphicsManager), model(graphicsManager), rotation(XMFLOAT3(0, 0, 0)), position(XMFLOAT3(0, 0, 0)), scale(XMFLOAT3(1, 1, 1))
{
}
GameObject::GameObject(GraphicsManager* graphicsManager, const char* filename) :
	graphicsManager(graphicsManager), model(graphicsManager, filename), rotation(XMFLOAT3(0, 0, 0)), position(XMFLOAT3(0, 0, 0)), scale(XMFLOAT3(1, 1, 1))
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	model.UpdateModelPosition(position);
	model.UpdateGlobalRotation(rotation);
}

void GameObject::LoadTexture(const char* fileName)
{
	model.LoadTexture(fileName);
}

void GameObject::LoadModel(const char* fileName)
{
	model.LoadModel(fileName);
}

XMFLOAT3 GameObject::GetScale()
{
	return scale;
}

void GameObject::ScaleObject(float newScale)
{
	scale.x = newScale;
	scale.y = newScale;
	scale.z = newScale;
	model.ScaleObject(scale);

}

void GameObject::ScaleObject(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
	model.ScaleObject(scale);
}

void GameObject::ScaleObject(XMFLOAT3 newScale)
{
	scale.x = newScale.x;
	scale.y = newScale.y;
	scale.z = newScale.z;
	model.ScaleObject(scale);
}

void GameObject::RenderAllMeshes()
{
	model.RenderAllMeshes();
}

XMFLOAT3 GameObject::GetPosition()
{
	return position;
}

void GameObject::SetPosition(float x, float y, float z, int meshIndex)
{
	if (meshIndex != -1)
	{
		model.UpdateLocalPosition(XMFLOAT3(x,y,z), meshIndex);


	}
	else
	{
		position.x = x;
		position.y = y;
		position.z = z;
		model.UpdateModelPosition(position);
	}

}

XMFLOAT3 GameObject::GetRotation()
{
	return rotation;
}

void GameObject::SetRotation(float x, float y, float z, int meshIndex)
{
	if (meshIndex != -1)
	{
		model.UpdateLocalRotation(XMFLOAT3(x, y, z), meshIndex);

	}
	else
	{
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
		model.UpdateGlobalRotation(rotation);
	}
}

Model GameObject::GetModel()
{
	return model;
}

MeshData GameObject::GetMesh(int i)
{
	return model.GetMesh(i);
}

void GameObject::Render()
{
	graphicsManager->RenderObject(&model);
}
