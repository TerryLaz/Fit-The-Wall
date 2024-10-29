#pragma once
#include "../common.h"
#include <map>
#include <vector>

namespace AssetLoader
{
	struct FileData
	{
		FileInfo fileInfo;
		std::vector<MeshHeader> meshes = std::vector<MeshHeader>();
		std::vector<VertexHeader*> vertices = std::vector<VertexHeader*>();
		std::vector<MaterialHeader> materials = std::vector<MaterialHeader>();
		std::vector<CameraHeader> cameras = std::vector<CameraHeader>();
		std::vector<LightHeader> lights = std::vector<LightHeader>();
		std::vector<MorphHeader> morphs = std::vector <MorphHeader>();
		std::vector<Keyframe> keyframe = std::vector<Keyframe>();
		std::vector<SkeletonHeader> skeletons = std::vector<SkeletonHeader>();
		std::vector<Joint> joints = std::vector<Joint>();
		std::vector<CustomAttributesHeader> customAttributes = std::vector<CustomAttributesHeader>();
	};

	class AssetManager
	{
	private:
		std::map<const char*, FileData> loadedModels = std::map<const char*, FileData>();
		void LoadModel(const char* filepath);
	public:
		~AssetManager();
		//Get model specified by file path
		FileData GetModel(const char* filepath);
	};

}

