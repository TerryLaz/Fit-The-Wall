#include "Pose.h"


Pose::Pose(GraphicsManager* graphicsManager)
	:graphicsManager(graphicsManager), pose1(graphicsManager, "Models/quad.ftw"), pose2(graphicsManager, "Models/quad.ftw"), pose3(graphicsManager, "Models/quad.ftw")
{
	SetUpPose(&pose1, "Images/Pose1.png");
	SetUpPose(&pose2, "Images/Pose2.png");
	SetUpPose(&pose3, "Images/Pose3.png");
}
void Pose::SetUpPose(GameObject* pose, const char* textureName)
{
	pose->LoadTexture(textureName);
	pose->SetPosition(2.55f, 1.9f, -8.1f);
	pose->ScaleObject(2.1, 2.1, 1);
}

Pose::~Pose()
{

}

void Pose::Update()
{
	pose1.Update();
	pose2.Update();
	pose3.Update();
}

void Pose::Render(int id)
{
	if (id == 1)
		pose1.Render();
	else if (id == 2)
		pose2.Render();
	else if (id == 3)
		pose3.Render();
}