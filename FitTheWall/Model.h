#pragma once
#include <d3d11.h>
#include "GraphicsManager.h"
#include <DirectXMath.h>

struct TextureData
{
	std::string filename;
	ID3D11SamplerState* samplerState;
	ID3D11ShaderResourceView* resourceView;

	ID3D11SamplerState* const* GetSamplerState() { return &samplerState; }
	ID3D11ShaderResourceView* const* GetShaderResourceView() { return &resourceView; }

};

struct MaterialData
{
	XMFLOAT3 ambient;
	XMFLOAT3 diffuse;
	XMFLOAT3 specular;
	XMFLOAT3 emissive;

	TextureData diffuseMap;
	TextureData normalMap;
	TextureData specularMap;
	TextureData glowMap;

};

struct JointData
{
	unsigned int parentID;
	XMMATRIX invBindPose;
};

struct MeshData 
{
	bool shouldRender = true;
	char* meshName;
	int groupID;
	int nrVertices;
	Vertex* vertices;
	MaterialData material;
	ID3D11Buffer* vertexBuffer = 0;
	std::map<int, JointData> skeleton;
	XMFLOAT3 localPosition;
	XMFLOAT3 localRotation;
	XMFLOAT3 localScale;
	XMMATRIX transMatrix;
	XMMATRIX rotationMatrix;
	XMMATRIX scaleMatrix;
	XMMATRIX worldMatrix;
	ID3D11Buffer* modelBuffer = 0;

	ID3D11Buffer* const* GetVertexBuffer() { return &vertexBuffer; }
	ID3D11Buffer* const* GetModelBuffer() { return &modelBuffer; }
	XMMATRIX GetWorldMatrix() { return worldMatrix; }
	MaterialData GetMaterial() { return material; }

};

class Model
{
private:
	const char* fileName;

	GraphicsManager* graphicsManager;

	//TODO: lista med meshar
	//MeshData mesh;
	std::vector<MeshData> meshes;

	XMFLOAT3 modelPosition;
	XMFLOAT3 modelRotation;
	XMFLOAT3 modelScale;


public:
	Model(GraphicsManager* graphicsManager);
	Model(GraphicsManager* graphicsManager, const char* filename);
	~Model();

	void UpdateModelPosition(XMFLOAT3 newPosition);
	void UpdateLocalPosition(XMFLOAT3 newPosition, int meshIndex);
	void UpdateLocalRotation(XMFLOAT3 newRotation, int meshIndex);
	void UpdateGlobalRotation(XMFLOAT3 newRotation);
	void ScaleObject(XMFLOAT3 newScale);
	void LoadModel(const char* path);
	void LoadTexture(const char* path);
	void RenderSingleMesh(int i);
	void RenderAllMeshes();

	void UpdateModelBuffer();

	MeshData GetMesh(int i);

	
	std::vector<MeshData> GetMeshesToRender();
};