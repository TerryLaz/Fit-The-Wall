#pragma once

#include"Model.h"
#include <DirectXMath.h>


class GameObject
{
private:
	//Model model;
	GraphicsManager* graphicsManager;

	bool meshHasSingleMeshToUpdate = false;

protected:
	XMFLOAT3 position;
	XMFLOAT3 scale;
	XMFLOAT3 rotation;

	Model model;
	int nrOfMeshesToRender = 0;

public:
	GameObject(GraphicsManager* graphicsManager);
	GameObject(GraphicsManager* graphicsManager, const char* filename);
	~GameObject();

	void Update();
	void Render();
	void RenderAsGUI();

	void LoadTexture(const char* fileName);
	void LoadModel(const char* fileName);
	void RenderAllMeshes();

	XMFLOAT3 GetPosition();
	void SetPosition(float x, float y, float z, int meshIndex = -1);

	XMFLOAT3 GetRotation();
	void SetRotation(float x, float y, float z, int meshIndex = -1);

	XMFLOAT3 GetScale();
	void ScaleObject(float newScale);
	void ScaleObject(float x, float y, float z);
	void ScaleObject(XMFLOAT3 newScale);

	Model GetModel();
	MeshData GetMesh(int i =0);
};

