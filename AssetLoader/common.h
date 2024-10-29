#pragma once

//TODO: add morph, skeleton, animation, group and custom attributes
enum SectionType
{
	UNKNOWN,
	FILE_INFO,
	MESH,
	MATERIAL,
	CAMERA,
	LIGHT,
	MORPH,
	SKELETON,
	ANIMATION,
	GROUP,
	CUSTOM_ATTRIBUTES
};

struct SectionHeader
{
	SectionType type;
	SectionHeader(SectionType t)
	{
		type = t;
	}
	SectionHeader()
	{
		type = UNKNOWN;
	}
};

struct FileInfo :SectionHeader
{
	int nrMeshes;
	int nrMaterials;
	int nrCameras;
	int nrLights;
	int nrMorphAnim;
	int nrSkeletons;
	int nrCustomAttributes;
	FileInfo() :SectionHeader(FILE_INFO) {}

};

struct MeshHeader :SectionHeader
{
	char meshName[32];
	int groupID;
	int materialID;
	int numOfVertices;

	MeshHeader() :SectionHeader(MESH) {}
};

struct MaterialHeader :SectionHeader
{
	char materialName[32];
	int materialID;
	float ambient[3];
	float diffuse[3];
	float specular[3];

	char diffuseTexturePath[64] = "";
	char normalTexturePath[64] = "";
	char specularTexturePath[64] = "";
	char glowTexturePath[64] = "";

	MaterialHeader() :SectionHeader(MATERIAL) {}
};
struct CameraHeader :SectionHeader
{
	float position[3];
	float upVector[3];
	float forwardVector[3];
	float fov;
	float nearDistance;
	float farDistance;

	CameraHeader() :SectionHeader(CAMERA) {}
};

struct LightHeader :SectionHeader
{
	char lightType[16];
	float color[3];
	float position[3];
	float direction[3];
	float fallOff;
	float intensity;

	LightHeader() :SectionHeader(LIGHT) {}
};

struct MorphHeader :SectionHeader
{
	int animationID;
	int nrOfKeyframes;

	MorphHeader() :SectionHeader(MORPH) {}
};

struct SkeletonHeader :SectionHeader
{
	int skeletonID;
	int nrOfJoints;

	SkeletonHeader() :SectionHeader(SKELETON) {}
};

struct AnimationHeader :SectionHeader
{
	int animationID;
	int skeletonID;
	float duration;
	float framerate;
	int nrOfKeyFrames;

	AnimationHeader() :SectionHeader(ANIMATION) {}
};

struct GroupHeader :SectionHeader
{
	int ID;
	// translation
	// roation
	// scene

	GroupHeader() :SectionHeader(GROUP) {}
};

struct CustomAttributesHeader : SectionHeader
{
	int objID;
	char attributeDisplayName[32];
	char attributeInternalName[32];

	// Scalar values
	char dataType[8];
	float minValue;
	float maxValue;
	bool isAnimatable;
	char defaultValue[32];

	// Data types
	float vector[4];
	float real;
	int integer;
	bool boolean;
	char string[32];
	char enumeration[32];

	CustomAttributesHeader() :SectionHeader(CUSTOM_ATTRIBUTES) {}
};

//TODO: add bone weight
struct VertexHeader
{
	float position[3];
	float normal[3];
	float uv[2];
	float joints[4];
	float weights[4];
	/*Binormal + Tangent*/
	float tangent[3];
	float binormal[3];
};

struct Joint
{
	unsigned int ID;
	unsigned int parentID;

	//store matrix rows as 4x4 float array
	float inverseBind0[4];
	float inverseBind1[4];
	float inverseBind2[4];
	float inverseBind3[4];
};

struct Keyframe
{
	unsigned int animationID;
	unsigned int timestamp;
	float translation[3];
	float rotation[3];
	float scale[3];
};