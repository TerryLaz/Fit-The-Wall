#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	vShader->Release();
	pShader->Release();
	inputLayout->Release();
}

bool ShaderManager::LoadShaders(ID3D11Device* device, std::string& vShaderByteCode, std::string shaderName)
{

	std::string shaderData;
	std::ifstream reader;
	reader.open("Shaders/" + shaderName + "VertexShader.cso", std::ios::binary | std::ios::ate);
	if (!reader.is_open())
	{
		std::cerr << "Could not open vertex shader file!" << std::endl;
		return false;
	}
	//jump to end of file
	reader.seekg(0, std::ios::end);

	//reseve nessecary space for the bytes
	shaderData.reserve(static_cast<unsigned int>(reader.tellg()));

	// jump to begining of file
	reader.seekg(std::ios::beg);

	shaderData.assign((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());

	if (FAILED(device->CreateVertexShader(shaderData.c_str(), shaderData.length(), nullptr, &vShader)))
	{
		std::cerr << "Failed to create vertex shader!" << std::endl;
		return false;
	}
	vShaderByteCode = shaderData;
	shaderData.clear();
	reader.close();
	reader.open("Shaders/" + shaderName + "PixelShader.cso", std::ios::binary | std::ios::ate);
	if (!reader.is_open())
	{
		std::cerr << "Could not open pixel shader file!" << std::endl;
		return false;
	}
	reader.seekg(0, std::ios::end);
	shaderData.reserve(static_cast<unsigned int>(reader.tellg()));
	reader.seekg(0, std::ios::beg);

	shaderData.assign((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());

	if (FAILED(device->CreatePixelShader(shaderData.c_str(), shaderData.length(), nullptr, &pShader)))
	{
		std::cerr << "Failed to create pixel shader!" << std::endl;
		return false;
	}
	return true;
}

bool ShaderManager::CreateInputLayout(ID3D11Device* device, const std::string& vShaderByteCode)
{
	const int nrElements = 5;
	D3D11_INPUT_ELEMENT_DESC inputDesc[nrElements] =
	{
		//descibes a vertex
		{"POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },	//0
		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12, D3D11_INPUT_PER_VERTEX_DATA,0},	//3
		{"UV",0, DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0},			//6
		{"BONE",0, DXGI_FORMAT_R32G32B32A32_FLOAT,0,32,D3D11_INPUT_PER_VERTEX_DATA,0},	//8
		{"WEIGHT",0, DXGI_FORMAT_R32G32B32A32_FLOAT,0,48,D3D11_INPUT_PER_VERTEX_DATA,0}	//12
	};

	HRESULT hr = device->CreateInputLayout(inputDesc, nrElements, vShaderByteCode.c_str(), vShaderByteCode.length(), &inputLayout);

	return !FAILED(hr);

}

bool ShaderManager::CreateGUIInputLayout(ID3D11Device* device, const std::string& vShaderByteCode)
{
	const int nrElements = 2;
	D3D11_INPUT_ELEMENT_DESC inputDesc[nrElements] =
	{
		//descibes a vertex
		{"POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },	//0
		{"UV",0, DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0},			//6
	};

	HRESULT hr = device->CreateInputLayout(inputDesc, nrElements, vShaderByteCode.c_str(), vShaderByteCode.length(), &inputLayout);

	return !FAILED(hr);
}


bool ShaderManager::SetupShaders(ID3D11Device* device, std::string shaderName)
{
	std::string vShaderByteCode;
	if (!LoadShaders(device, vShaderByteCode, shaderName))
	{
		std::cerr << "Error loading shaders!" << std::endl;
		return false;
	}
	if (shaderName.find("GUI") != std::string::npos)
	{
		if (!CreateGUIInputLayout(device, vShaderByteCode))
		{
			std::cerr << "Error creating input layout!" << std::endl;
			return false;
		}
	}
	else
	{
		if (!CreateInputLayout(device, vShaderByteCode))
		{
			std::cerr << "Error creating input layout!" << std::endl;
			return false;
		}
	}

	return true;
}


ID3D11VertexShader* ShaderManager::GetVertexShader()
{
	return vShader;
}

ID3D11PixelShader* ShaderManager::GetPixelShader()
{
	return pShader;
}

ID3D11InputLayout* ShaderManager::GetInputLayout()
{
	return inputLayout;
}

