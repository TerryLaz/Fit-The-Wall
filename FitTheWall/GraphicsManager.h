#pragma once

#include "ShaderManager.h"
#include "Light.h"

#include<Windows.h>
#include<d3d11.h>
#include<list>
#include<iostream>
#include<DirectXMath.h>
#include <AssetLoader.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>


class Model;

using namespace DirectX;
struct Vertex
{
	XMFLOAT3 positions;
	XMFLOAT3 normals;
	XMFLOAT2 uvs;
	XMFLOAT4 jointID;
	XMFLOAT4 weight;
};

struct CameraInfo
{
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;
	XMFLOAT3 cameraPosition;
};

struct ModelInfo
{
	XMMATRIX worldMatrix;
};

struct LightInfo
{
	DirectionalLight dirLight1;
	DirectionalLight dirLight2;
	PointLight pLight;
	SpotLight sLight;
};


class GraphicsManager
{
private:
	ShaderManager* shaderManager;
	ShaderManager* guiShaderManager;

	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* rtv;
	ID3D11Texture2D* dsTexture;
	ID3D11DepthStencilView* dsView;
	ID3D11BlendState* transparency;
	D3D11_VIEWPORT viewport;


	AssetLoader::AssetManager* assetManager;

	std::unique_ptr<SpriteBatch> spriteBatch;
	std::unique_ptr<SpriteFont> spriteFont;

	bool CreateInterfaces(UINT width, UINT height, HWND window);
	bool CreateRenderTargetView();
	bool CreateDepthStencil(UINT width, UINT height);
	void SetViewport(UINT width, UINT height);

public:
	GraphicsManager();
	~GraphicsManager();

	AssetLoader::AssetManager* GetAssetManager();

	SpriteBatch& GetSpriteBatch();
	SpriteFont& GetSpriteFont();

	bool SetupD3D11(UINT width, UINT height, HWND window);
	bool CreateVertexBuffer(Vertex* vertices, int nrVertices, ID3D11Buffer*& vertexBuffer);
	bool CreateCameraBuffer(ID3D11Buffer*& cameraBuffer);
	void UpdateCameraBuffer(ID3D11Buffer*& cameraBuffer, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition);
	bool CreateModelBuffer(ID3D11Buffer*& modelBuffer);
	void UpdateModelBuffer(ID3D11Buffer*& modelBuffer, XMMATRIX worldMatrix);

	//Light
	bool CreateLightBuffer(ID3D11Buffer*& lightBuffer);
	void UpdateLightBuffer(ID3D11Buffer*& lightBuffer, DirectionalLight dirLight, DirectionalLight dirLight2, PointLight pLight, SpotLight sLight);

	void StartRenderPass(ID3D11Buffer* cameraBuffer);
	void SetShaderBuffers(ID3D11Buffer* lightBuffer);
	void RenderObject(Model* model);
	void StartGUIBlendStateRenderPass();
	void StartGUIShaderRenderPass();
	void StopRenderPass();
	bool CreateTexture(const char* filePath, ID3D11SamplerState*& samplerState, ID3D11ShaderResourceView*& resourceView);

	XMFLOAT3 NormalizeFloat3(const XMFLOAT3& v);
};

