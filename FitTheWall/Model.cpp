#include "Model.h"


Model::Model(GraphicsManager* graphicsManager) :
	graphicsManager(graphicsManager) 
{
	meshes = std::vector<MeshData>();

	fileName = "Models/box2.ftw";
	LoadModel(fileName);
	LoadTexture("Images/hsb.png");

}

Model::Model(GraphicsManager* graphicsManager, const char* filename) :
	graphicsManager(graphicsManager)
{
	meshes = std::vector<MeshData>();
	fileName = filename;

	LoadModel(fileName);

}

Model::~Model()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		//delete[] meshes[i].vertices;
		meshes[i].vertexBuffer->Release();
		meshes[i].modelBuffer->Release();
		meshes[i].material.diffuseMap.resourceView->Release();
		meshes[i].material.diffuseMap.samplerState->Release();
	}
}

void Model::UpdateModelPosition(XMFLOAT3 newPosition)
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].localPosition = newPosition;
		meshes[i].transMatrix = XMMatrixTranslation(newPosition.x, newPosition.y, newPosition.z);

	}
	UpdateModelBuffer();
}

void Model::UpdateLocalPosition(XMFLOAT3 newPosition, int meshIndex)
{
	meshes[meshIndex].localPosition = newPosition;
	meshes[meshIndex].transMatrix = XMMatrixTranslation(newPosition.x, newPosition.y, newPosition.z);

	UpdateModelBuffer();
}

void Model::UpdateLocalRotation(XMFLOAT3 newRotation, int meshIndex)
{
	meshes[meshIndex].localRotation = newRotation;
	meshes[meshIndex].rotationMatrix = XMMatrixRotationX(newRotation.x) * XMMatrixRotationY(newRotation.y) * XMMatrixRotationZ(newRotation.z);

	UpdateModelBuffer();
}

void Model::UpdateGlobalRotation(XMFLOAT3 newRotation)
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].localRotation = newRotation;
		meshes[i].rotationMatrix = XMMatrixRotationX(newRotation.x) * XMMatrixRotationY(newRotation.y) * XMMatrixRotationZ(newRotation.z);

	}
	UpdateModelBuffer();
}

void Model::LoadModel(const char* path)
{
	//clear meshes when loading new model
	meshes.clear();

	AssetLoader::AssetManager* assetManager = graphicsManager->GetAssetManager();
	AssetLoader::FileData modelData = assetManager->GetModel(path);


	std::map<int, MaterialData> materialsByID = std::map<int, MaterialData>();

	for (int i = 0; i < modelData.materials.size(); i++)
	{
		MaterialData material;
		material.ambient = (XMFLOAT3)modelData.materials[i].ambient;
		material.diffuse = (XMFLOAT3)modelData.materials[i].diffuse;
		material.specular = (XMFLOAT3)modelData.materials[i].specular;

		material.diffuseMap.filename = modelData.materials[i].diffuseTexturePath;
		material.normalMap.filename = modelData.materials[i].normalTexturePath;
		material.specularMap.filename = modelData.materials[i].specularTexturePath;
		material.glowMap.filename = modelData.materials[i].glowTexturePath;

		materialsByID.insert(std::pair<int, MaterialData>(modelData.materials[i].materialID, material));
	}

	for (int i = 0; i < modelData.meshes.size(); i++)
	{
		MeshData mesh;
		//populate mesh data
		mesh.meshName = modelData.meshes[i].meshName;
		mesh.vertices = (Vertex*)modelData.vertices[i];
		mesh.nrVertices = modelData.meshes[i].numOfVertices;
		mesh.groupID = modelData.meshes[i].groupID;
		mesh.material = materialsByID.at(modelData.meshes[i].materialID);

		//Create vertex buffer
		graphicsManager->CreateVertexBuffer(mesh.vertices, mesh.nrVertices, mesh.vertexBuffer);

		mesh.transMatrix = XMMatrixTranslation(0, 0, 0);
		mesh.rotationMatrix = XMMatrixRotationRollPitchYaw(0, 0, 0);
		mesh.scaleMatrix = XMMatrixScaling(1, 1, 1);

		mesh.worldMatrix = XMMatrixMultiply(mesh.scaleMatrix, mesh.rotationMatrix);
		mesh.worldMatrix = XMMatrixMultiply(mesh.worldMatrix, mesh.transMatrix);
		graphicsManager->CreateModelBuffer(mesh.modelBuffer);

		for (int j = 0; j < modelData.joints.size(); j++)
		{
			JointData joint;
			joint.parentID = modelData.joints[j].parentID;
			float* r0 = modelData.joints[i].inverseBind0;
			float* r1 = modelData.joints[i].inverseBind1;
			float* r2 = modelData.joints[i].inverseBind2;
			float* r3 = modelData.joints[i].inverseBind3;
			joint.invBindPose = XMMATRIX(r0[0], r0[1], r0[2], r0[3], 
										 r1[0], r1[1], r1[2], r1[3],
										 r2[0], r2[1], r2[2], r2[3],
										 r3[0], r3[1], r3[2], r3[3]);
			mesh.skeleton.insert(std::pair<int, JointData>(modelData.joints[j].ID, joint));
		}

		//Create vertex buffer
		graphicsManager->CreateVertexBuffer(mesh.vertices, mesh.nrVertices, mesh.vertexBuffer);

		//Create texture buffers
		if (mesh.material.diffuseMap.filename[0] != 0)
		{
			graphicsManager->CreateTexture(mesh.material.diffuseMap.filename.c_str(), mesh.material.diffuseMap.samplerState, mesh.material.diffuseMap.resourceView);
		}
		if (mesh.material.normalMap.filename[0] != 0)
		{
			graphicsManager->CreateTexture(mesh.material.normalMap.filename.c_str(), mesh.material.normalMap.samplerState, mesh.material.normalMap.resourceView);
		}
		if (mesh.material.specularMap.filename[0] != 0)
		{
			graphicsManager->CreateTexture(mesh.material.specularMap.filename.c_str(), mesh.material.specularMap.samplerState, mesh.material.specularMap.resourceView);
		}
		if (mesh.material.glowMap.filename[0] != 0)
		{
			graphicsManager->CreateTexture(mesh.material.glowMap.filename.c_str(), mesh.material.glowMap.samplerState, mesh.material.glowMap.resourceView);
		}

		meshes.push_back(mesh);
	}
	//RenderSingleMesh(0);
}

void Model::LoadTexture(const char* path)
{
	//TODO: ladda textur till mesh enligt index
	graphicsManager->CreateTexture(path, meshes[0].material.diffuseMap.samplerState, meshes[0].material.diffuseMap.resourceView);
}

void Model::RenderSingleMesh(int i)
{
	for (int j = 0; j < meshes.size(); j++)
	{
		meshes[j].shouldRender = false;
	}
	meshes[i].shouldRender = true;
}

void Model::ScaleObject(XMFLOAT3 newScale)
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].scaleMatrix = XMMatrixScaling(newScale.x, newScale.y, newScale.z);

	}
	UpdateModelBuffer();
}

void Model::RenderAllMeshes()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].shouldRender = true;
	}
}

void Model::UpdateModelBuffer()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].worldMatrix = XMMatrixMultiply(meshes[i].scaleMatrix, meshes[i].rotationMatrix);
		meshes[i].worldMatrix = XMMatrixMultiply(meshes[i].worldMatrix, meshes[i].transMatrix);
		graphicsManager->UpdateModelBuffer(meshes[i].modelBuffer, meshes[i].worldMatrix);
	}
}

MeshData Model::GetMesh(int i)
{
	return meshes[i];
}

std::vector<MeshData> Model::GetMeshesToRender()
{
	return meshes;
}


