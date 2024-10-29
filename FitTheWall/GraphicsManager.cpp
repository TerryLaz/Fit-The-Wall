#include "GraphicsManager.h"
#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION
#include"../stb-master/stb_image.h"

GraphicsManager::GraphicsManager()
{
	shaderManager = new ShaderManager();
	guiShaderManager = new ShaderManager();
	assetManager = new AssetLoader::AssetManager();
	

}

GraphicsManager::~GraphicsManager()
{
	device->Release();
	context->Release();
	swapChain->Release();
	rtv->Release();
	dsTexture->Release();
	dsView->Release();
	transparency->Release();

	spriteBatch.reset();
	spriteFont.reset();
	spriteBatch.release();
	spriteFont.release();

	delete shaderManager;
	delete guiShaderManager;
	delete assetManager;

	//SHOW UNRELEASED COM POINTERS  (OM REF ÄR STÖRRE ÄN 0 == UNRELEASED. IGNORERA INREF: )
	//ID3D11Debug* debugger = nullptr;
	//device->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugger));
	//debugger->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	//debugger->Release();
}

AssetLoader::AssetManager* GraphicsManager::GetAssetManager()
{
	return assetManager;
}

SpriteBatch& GraphicsManager::GetSpriteBatch()
{
	return *spriteBatch;
}

SpriteFont& GraphicsManager::GetSpriteFont()
{
	return *spriteFont;
}

bool GraphicsManager::CreateInterfaces(UINT width, UINT height, HWND window)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Default settings
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = window;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	//if debug is activated create device debug flag
	UINT flags = 0;
	//if (_DEBUG)
	//	flags = D3D11_CREATE_DEVICE_DEBUG;

	//defines feature level to use
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	//Creates swap Chain Device
	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, featureLevels, 1, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, nullptr, &context);

	// initialize and connect sprite font to context
	spriteBatch = std::make_unique<DirectX::SpriteBatch>(this->context);
	spriteFont = std::make_unique<DirectX::SpriteFont>(this->device, L"Fonts\\font.spritefont");
	

	D3D11_BLEND_DESC blendDesc;

	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = device->CreateBlendState(&blendDesc, &transparency);


	return !FAILED(hr);

}

bool GraphicsManager::CreateRenderTargetView()
{
	ID3D11Texture2D* backBuffer = nullptr;

	//set values to backbuffer if posible
	if (FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
	{
		std::cerr << "Failed to get back buffer!" << std::endl;
		return false;
	}

	//assigne backbuffer to device
	HRESULT hr = device->CreateRenderTargetView(backBuffer, nullptr, &rtv);

	//release dynamic memory 
	backBuffer->Release();

	return !FAILED(hr);
}

bool GraphicsManager::CreateDepthStencil(UINT width, UINT height)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	//assigne new textureDesc values to dsTexture
	if (FAILED(device->CreateTexture2D(&textureDesc, nullptr, &dsTexture)))
	{
		std::cerr << "Faild to create depth stencil texture!" << std::endl;
		return false;
	}

	//save and add new information to my device
	HRESULT hr = device->CreateDepthStencilView(dsTexture, nullptr, &dsView);

	//return device if succesful
	return !FAILED(hr);
}

void GraphicsManager::SetViewport(UINT width, UINT height)
{
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
}

bool GraphicsManager::SetupD3D11(UINT width, UINT height, HWND window)
{
	if (!CreateInterfaces(width, height, window))
	{
		std::cerr << "Error creating interface!" << std::endl;
		return false;
	}
	if (!CreateRenderTargetView())
	{
		std::cerr << "Error creating rtv!" << std::endl;
		return false;
	}
	if (!CreateDepthStencil(width, height))
	{
		std::cerr << "Error creating depth stencil view!" << std::endl;
		return false;
	}

	SetViewport(width, height);

	shaderManager->SetupShaders(device, "Standard");
	guiShaderManager->SetupShaders(device, "GUI");
}

bool GraphicsManager::CreateVertexBuffer(Vertex* vertices, int nrVertices, ID3D11Buffer*& vertexBuffer)
{

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(Vertex) * nrVertices;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT; // buffer cannot be chnaged after created
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//descripes a vertex buffer
	bufferDesc.CPUAccessFlags = 0; //is immutable = unused
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertices; //data to write to buffer
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0; 

	HRESULT hr = device->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
	
	return !FAILED(hr);
}

bool GraphicsManager::CreateCameraBuffer(ID3D11Buffer*& cameraBuffer)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(CameraInfo);
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	HRESULT hr = device->CreateBuffer(&bufferDesc, NULL, &cameraBuffer);
	return !FAILED(hr);
}

bool GraphicsManager::CreateModelBuffer(ID3D11Buffer*& modelBuffer)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(ModelInfo);
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	HRESULT hr = device->CreateBuffer(&bufferDesc, NULL, &modelBuffer);

	return !FAILED(hr);
}

bool GraphicsManager::CreateTexture(const char* filePath, 
	ID3D11SamplerState*& samplerState, ID3D11ShaderResourceView*& resourceView)
{
	int width;
	int height;
	int channels;
	
	unsigned char buf[8];
	
	std::ifstream in(filePath);
	in.seekg(16);
	in.read(reinterpret_cast<char*>(&buf), 8);

	width = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + (buf[3] << 0);
	height = (buf[4] << 24) + (buf[5] << 16) + (buf[6] << 8) + (buf[7] << 0);
	channels = 4;
	
	unsigned char* pData;

	pData = stbi_load(filePath, &width, &height, &channels, 0);

	if (!pData)
	{
		std::cerr << "cant load file image!" << std::endl;
	}

	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_IMMUTABLE;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = pData;
	data.SysMemPitch = width * channels;
	data.SysMemSlicePitch = width * height * channels;

	ID3D11Texture2D* textureBuffer;


	HRESULT hr = device->CreateTexture2D(&textureDesc, &data, &textureBuffer);
	if (FAILED(hr))
	{
		std::cerr << "Failed to create texture!" << std::endl;
		return false;
	}

	hr = device->CreateShaderResourceView(textureBuffer, nullptr, &resourceView);
	if (FAILED(hr))
	{
		std::cerr << "Failed to create resourceView!" << std::endl;
		return false;
	}
	textureBuffer->Release();

	D3D11_SAMPLER_DESC samplerDesc;

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP; //only used in 3D
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = device->CreateSamplerState(&samplerDesc, &samplerState);
	if (FAILED(hr))
	{
		std::cerr << "Failed to create sampleState!" << std::endl;
		return false;
	}
	free(pData);
	//delete pData;
	return true;
}

XMFLOAT3 GraphicsManager::NormalizeFloat3(const XMFLOAT3& v)
{
	XMFLOAT3 f;
	XMVECTOR vec = XMVector3Normalize(XMLoadFloat3(&v));
	XMStoreFloat3(&f, vec);
	return f;
}



void GraphicsManager::UpdateCameraBuffer(ID3D11Buffer*& cameraBuffer, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition)
{
	CameraInfo* dataptr;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	context->Map(cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	dataptr = (CameraInfo*)mappedResource.pData;
	dataptr->viewMatrix = viewMatrix;
	dataptr->projectionMatrix = projectionMatrix;
	dataptr->cameraPosition = cameraPosition;

	context->Unmap(cameraBuffer, 0);
}

void GraphicsManager::UpdateModelBuffer(ID3D11Buffer*& modelBuffer, XMMATRIX worldMatrix)
{
	ModelInfo* dataptr;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	context->Map(modelBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	dataptr = (ModelInfo*)mappedResource.pData;
	dataptr->worldMatrix = DirectX::XMMatrixTranspose(worldMatrix);

	context->Unmap(modelBuffer, 0);

}

bool GraphicsManager::CreateLightBuffer(ID3D11Buffer*& lightBuffer)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(LightInfo);
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.StructureByteStride = 0;
	bufferDesc.MiscFlags = 0;


	HRESULT hr = device->CreateBuffer(&bufferDesc, NULL, &lightBuffer);

	return !FAILED(hr);
}

void GraphicsManager::UpdateLightBuffer(ID3D11Buffer*& lightBuffer, DirectionalLight dirLight, DirectionalLight dirLight2, PointLight pLight, SpotLight sLight)
{
	LightInfo* dataPtr;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	context->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	dataPtr = (LightInfo*)mappedResource.pData;
	dataPtr->dirLight1 = dirLight;
	dataPtr->dirLight2 = dirLight2;
	dataPtr->pLight = pLight;
	dataPtr->sLight = sLight;

	context->Unmap(lightBuffer, 0);
}


void GraphicsManager::StartRenderPass(ID3D11Buffer* cameraBuffer)
{
	float clearColour[4] = { 0, 0.7, 0.7,0 };
	context->ClearRenderTargetView(rtv, clearColour);
	context->ClearDepthStencilView(dsView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	context->VSSetConstantBuffers(0, 1, &cameraBuffer);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->RSSetViewports(1, &viewport);
	context->OMSetRenderTargets(1, &rtv, dsView);
	context->IASetInputLayout(shaderManager->GetInputLayout());
	context->VSSetShader(shaderManager->GetVertexShader(), nullptr, 0);
	context->PSSetShader(shaderManager->GetPixelShader(), nullptr, 0);
}

void GraphicsManager::StartGUIBlendStateRenderPass()
{
	//Enable blend state for transparent objects
	float blendFactor[] = { 0.75f, 0.75f, 0.75f, 0.5f };
	context->OMSetBlendState(transparency, blendFactor, 1);
}

void GraphicsManager::StartGUIShaderRenderPass()
{
	context->IASetInputLayout(guiShaderManager->GetInputLayout());
	context->VSSetShader(guiShaderManager->GetVertexShader(), nullptr, 0);
	context->PSSetShader(guiShaderManager->GetPixelShader(), nullptr, 0);
	//context->ClearDepthStencilView(dsView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
}

void GraphicsManager::SetShaderBuffers(ID3D11Buffer* lightBuffer)
{
	context->PSSetConstantBuffers(0, 1, &lightBuffer);
}

void GraphicsManager::RenderObject(Model* model)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	for (int i = 0; i < model->GetMeshesToRender().size(); i++)
	{
		if (model->GetMesh(i).shouldRender == true)
		{
			context->VSSetConstantBuffers(1, 1, model->GetMesh(i).GetModelBuffer());
			context->IASetVertexBuffers(0, 1, model->GetMesh(i).GetVertexBuffer(), &stride, &offset);
			context->PSSetSamplers(0, 1, model->GetMesh(i).GetMaterial().diffuseMap.GetSamplerState());
			context->PSSetShaderResources(0, 1, model->GetMesh(i).GetMaterial().diffuseMap.GetShaderResourceView());
			context->Draw(model->GetMesh(i).nrVertices, 0);
		}
	}
}


void GraphicsManager::StopRenderPass()
{
	context->OMSetBlendState(nullptr, nullptr, 1);
	context->OMSetDepthStencilState(nullptr, 0);
	swapChain->Present(0, 0);
}