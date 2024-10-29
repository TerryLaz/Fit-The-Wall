#include "Spotlight.h"



Spotlight::Spotlight(GraphicsManager* graphicsManager)
	:GameObject(graphicsManager, "Models/spotlightSet.ftw")
{
	model.RenderAllMeshes();
	SetPosition(-4.5f, 0.0f, 0.0f);
	ScaleObject(0.04f);

	// Every mesh share the same speed for each axis
	for (int i = 0; i < 3; i++)
	{
		rotationSpeed[i] = 0;
	}

	for (int i = 0; i < 9; i++)
	{
		rotSeconds[i] = 0.0f;
		stopTimer[i] = 0.0f;
		reachedBoundary[i] = false;
		randomStopTime[i] = 0.0f;
	}
}

void Spotlight::Update()
{
	for (int i = 0; i < 9; i++)
	{
		if (reachedBoundary[i] == true)
		{
			randomStopTime[i] = (float)(rand() % 3);
		}
	}
}

void Spotlight::RotateSpotlight(int meshIndex, XMFLOAT3 rotSpeedXYZ, float rotTimeX, float rotTimeY, float rotTimeZ)
{
	float rotTimeXYZ[] = { rotTimeX, rotTimeY, rotTimeZ };
	int padding = 0;

	if (meshIndex == 1)
	{
		padding = 3;
	}
	if (meshIndex == 2)
	{
		padding = 6;
	}

	for (int i = 0; i < 3; i++)
	{
		if (!reachedBoundary[i + padding])
		{
			rotSeconds[i + padding] += 0.03;
		}
		if (reachedBoundary[i + padding])
		{
			stopTimer[i + padding] += 0.03;
		}
	}

	// Time reset checks
	for (int i = 0; i < 3; i++)
	{
		if (rotSeconds[i + padding] > rotTimeXYZ[i])
		{
			rotSeconds[i + padding] = 0;
			reachedBoundary[i + padding] = true;
		}
	}

	// Rotation boundary checks
	for (int i = 0; i < 3; i++)
	{
		if (stopTimer[i + padding] == 0.0f)
		{
			if (rotSeconds[i + padding] < rotTimeXYZ[i] / 2)
			{
				rotationSpeed[i] += 0.005f;
			}
			if (rotSeconds[i + padding] > rotTimeXYZ[i] / 2)
			{
				rotationSpeed[i] -= 0.005f;
			}
		}
		else if (stopTimer[i + padding] >= randomStopTime[i + padding])
		{
			reachedBoundary[i] = false;
			stopTimer[i + padding] = 0.0f;
		}
	}

	float rotX = rotSpeedXYZ.x * rotationSpeed[0];
	float rotY = rotSpeedXYZ.y * rotationSpeed[1];
	float rotZ = rotSpeedXYZ.z * rotationSpeed[2];

	SetRotation(rotX, rotY, rotZ, meshIndex);
}
