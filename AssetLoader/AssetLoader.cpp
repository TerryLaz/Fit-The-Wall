// AssetLoader.cpp
#include "AssetLoader.h"
#include <fstream>
#include <iostream>

namespace AssetLoader
{
	AssetManager::~AssetManager()
	{
		for (auto const& x : loadedModels)
		{
			for (int j = 0; j < x.second.vertices.size(); j++)
			{
				delete x.second.vertices[j];
			}
		}
	}
	void AssetManager::LoadModel(const char* filepath)
	{
		FileInfo info;
		unsigned int ID = 0;
		int nrJoints = 0;
		int nrKeyframes = 0;
		int nrCustomAttributes = 0;
		int nrObjects = 0;
		std::ifstream input(filepath, std::ifstream::binary);
		if (input.is_open())
		{
			std::ofstream log;

			log.open("assetloader_log.txt", std::ios_base::app);
			log << "File loaded: " << filepath << std::endl;

			input.read((char*)&info, sizeof(FileInfo));
			log << "Nr meshes: " << info.nrMeshes << std::endl;
			log << "Nr materials: " << info.nrMaterials << std::endl;
			log << "Nr cameras: " << info.nrCameras << std::endl;
			log << "Nr lights: " << info.nrLights << std::endl;
			log << "Nr animations: " << info.nrMorphAnim << std::endl;
			log << "Nr skeletons: " << info.nrSkeletons << std::endl;
			log << "Nr custom attributes: " << info.nrCustomAttributes << "\n" << std::endl;

			FileData fileData;
			for (int i = 0; i < info.nrMeshes; i++)
			{
				MeshHeader mesh;
				VertexHeader* vertices;
				input.read((char*)&mesh, sizeof(MeshHeader));
				vertices = new VertexHeader[mesh.numOfVertices];
				for (int j = 0; j < mesh.numOfVertices; j++)
				{
					input.read((char*)&vertices[j], sizeof(VertexHeader));
				}
				fileData.meshes.push_back(mesh);
				fileData.vertices.push_back(vertices);
			}

			for (int i = 0; i < info.nrMaterials; i++)
			{
				MaterialHeader material;
				input.read((char*)&material, sizeof(MaterialHeader));
				fileData.materials.push_back(material);
			}

			for (int i = 0; i < info.nrCameras; i++)
			{
				CameraHeader camera;
				input.read((char*)&camera, sizeof(CameraHeader));
				fileData.cameras.push_back(camera);

				log << "camera loaded: " << std::endl;
				log << "\t position: [" << camera.position[0] << ", " << camera.position[1] << ", " << camera.position[2] << "]\n";
				log << "\t up vector: [" << camera.upVector[0] << ", " << camera.upVector[1] << ", " << camera.upVector[2] << "]\n";
				log << "\t forward vector: [" << camera.forwardVector[0] << ", " << camera.forwardVector[1] << ", " << camera.forwardVector[2] << "]\n";
				log << "\t field of view: " << camera.fov << std::endl;
				log << "\t near plane distance: " << camera.nearDistance << std::endl;
				log << "\t far plane distance: " << camera.farDistance << std::endl;
			}

			for (int i = 0; i < info.nrLights; i++)
			{
				LightHeader light;
				input.read((char*)&light, sizeof(LightHeader));
				fileData.lights.push_back(light);

				log << "light loaded: " << std::endl;
				log << "\t light type: " << light.lightType << std::endl;
				log << "\t color: [" << light.color[0] << ", " << light.color[1] << ", " << light.color[2] << "]\n";
				log << "\t postition: [" << light.position[0] << ", " << light.position[1] << ", " << light.position[2] << "]\n";
				log << "\t direction: [" << light.direction[0] << ", " << light.direction[1] << ", " << light.direction[2] << "]\n";
				log << "\t falloff: " << light.fallOff << std::endl;
				log << "\t intesity: " << light.intensity << std::endl;

			}
			for (int i = 0; i < info.nrMorphAnim; i++)
			{
				MorphHeader morph;
				input.read((char*)&morph, sizeof(MorphHeader));
				nrKeyframes += morph.nrOfKeyframes;
				fileData.morphs.push_back(morph);

				log << "animation loaded: " << std::endl;
				log << "\t animation ID: " << morph.animationID << std::endl;
				log << "\t nr of keyframes: " << morph.nrOfKeyframes << std::endl;
			}
			for (int i = 0; i < info.nrSkeletons; i++)
			{
				SkeletonHeader skeleton;
				input.read((char*)&skeleton, sizeof(SkeletonHeader));
				nrJoints += skeleton.nrOfJoints;
				fileData.skeletons.push_back(skeleton);

				log << "skeleton loaded: " << std::endl;
				log << "\t skeleton ID: " << skeleton.skeletonID << std::endl;
				log << "\t number of joints: " << skeleton.nrOfJoints << std::endl;
			}
			for (int i = 0; i < nrJoints; i++)
			{
				Joint joint;
				input.read((char*)&joint, sizeof(Joint));
				fileData.joints.push_back(joint);

				log << "joint loaded" << std::endl;
				log << "\t joint ID: " << joint.ID << std::endl;
				log << "\t parent ID: " << joint.parentID << std::endl;
				log << "\t inverse bind pose matrix: " << std::endl;
				log << "\t\t[" << joint.inverseBind0[0] << ", " << joint.inverseBind0[1] << ", " << joint.inverseBind0[2] << ", " << joint.inverseBind0[3] << std::endl;
				log << "\t\t" << joint.inverseBind1[0] << ", " << joint.inverseBind1[1] << ", " << joint.inverseBind1[2] << ", " << joint.inverseBind1[3] << std::endl;
				log << "\t\t" << joint.inverseBind2[0] << ", " << joint.inverseBind2[1] << ", " << joint.inverseBind2[2] << ", " << joint.inverseBind2[3] << std::endl;
				log << "\t\t" << joint.inverseBind3[0] << ", " << joint.inverseBind3[1] << ", " << joint.inverseBind3[2] << ", " << joint.inverseBind3[3] << "]\n";
			}
			for (int i = 0; i < nrKeyframes; i++)
			{
				Keyframe keyframe;
				input.read((char*)&keyframe, sizeof(Keyframe));
				fileData.keyframe.push_back(keyframe); 
				
				log << "animation keyframe loaded" << std::endl;
				log << "\t animation ID: " << keyframe.animationID << std::endl;
				log << "\t timestamp: " << keyframe.timestamp << std::endl;
				log << "\t translation: " << keyframe.translation[0] << ", " << keyframe.translation[1] << ", " << keyframe.translation[2] << "]\n";
				log << "\t rotation: " << keyframe.rotation[0] << ", " << keyframe.rotation[1] << ", " << keyframe.rotation[2] << "]\n";
				log << "\t scale: " << keyframe.scale[0] << ", " << keyframe.scale[1] << ", " << keyframe.scale[2] << "]\n";
			}
			
			for (int i = 0; i < info.nrCustomAttributes; i++)
			{
				CustomAttributesHeader customAttribute;
				input.read((char*)&customAttribute, sizeof(CustomAttributesHeader));
				fileData.customAttributes.push_back(customAttribute);

				log << "custom attribute loaded" << std::endl;
				log << "\t object ID: " << customAttribute.objID << std::endl;
				log << "\t attribute display name: " << customAttribute.attributeDisplayName << std::endl;
				log << "\t attribute internal name: " << customAttribute.attributeInternalName << std::endl;
				log << "\t data type: " << customAttribute.dataType << std::endl;
				log << "\t min value: " << customAttribute.minValue << std::endl;
				log << "\t max value: " << customAttribute.maxValue << std::endl;
				log << "\t is animatable: " << customAttribute.isAnimatable << std::endl;
				log << "\t\t vector: [" << customAttribute.vector[0] << ", " << customAttribute.vector[1] << ", " << customAttribute.vector[2] << "]\n";
				log << "\t\t real: " << customAttribute.real << std::endl;
				log << "\t\t integer: " << customAttribute.integer << std::endl;
				log << "\t\t boolean: " << customAttribute.boolean << std::endl;
				log << "\t\t string: " << customAttribute.string << std::endl;
				log << "\t\t enumeration: " << customAttribute.enumeration << std::endl;
			}

			log << "\n----------------------------------\n" << std::endl;

			input.close();
			log.close();

			ID = (unsigned int)loadedModels.size();
			loadedModels.insert({ filepath, fileData });
		}
	}

	FileData AssetManager::GetModel(const char* filepath)
	{
		if (loadedModels.find(filepath) == loadedModels.end())
		{
			LoadModel(filepath);
		}

		return loadedModels[filepath];
	}

}