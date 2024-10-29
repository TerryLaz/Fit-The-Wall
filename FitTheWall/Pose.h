#pragma once
#include "GameObject.h"

class Pose
{
private:
	GraphicsManager* graphicsManager;
	GameObject pose1;
	GameObject pose2;
	GameObject pose3;

	void SetUpPose(GameObject* pose, const char* textureName);


public:
	Pose(GraphicsManager* graphicsManager);
	~Pose();

	void Update();
	void Render(int id);
};