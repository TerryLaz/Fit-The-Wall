#pragma once
#include <d3d11.h>
#include <string>
#include <iostream>
#include <fstream>
class ShaderManager
{
private:

	ID3D11VertexShader* vShader;
	ID3D11PixelShader* pShader;
	ID3D11InputLayout* inputLayout;

	bool LoadShaders(ID3D11Device* device, std::string& vShaderByteCode, std::string shaderName);
	bool CreateInputLayout(ID3D11Device* device, const std::string& vShaderByteCode);
	bool CreateGUIInputLayout(ID3D11Device* device, const std::string& vShaderByteCode);

	

public:

	ShaderManager();
	~ShaderManager();
	bool SetupShaders(ID3D11Device* device, std::string shaderName);

	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();
	ID3D11InputLayout* GetInputLayout();

};

