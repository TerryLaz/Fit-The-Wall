#include "Audiens.h"
Audiens::Audiens(GraphicsManager* graphicsManager, const char* filename) :
	GameObject(graphicsManager, filename)
{
	model.RenderAllMeshes();
	newPosition = 0.15;
	groupOne[0] = 0;
	groupOne[1] = 1;
	groupTwo[0] = 2;
	groupTwo[1] = 3;
	groupThree[0] = 4;
	groupThree[1] = 5;
	SetPosition(0, -3, 25);
	SetRotation(0, 3.14, 0);
	currentPosition = 0;
	GameObject::Update();
}

Audiens::~Audiens()
{
}

void Audiens::Update(float time)
{
	moveAudiens(0.2,time);
}

void Audiens::moveAudiens(float scale, float time)
{
	double sinewave1 = sin(time * 1);
	double sinewave2 = sin((time+2) * 1);
	double sinewave3 = sin((time+3) * 1);

	float reScaled1 = (sinewave1 * scale) + (time / time * scale);
	float reScaled2 = (sinewave2 * scale) + (time / time * scale);
	float reScaled3 = (sinewave3 * scale) + (time / time * scale);



	for (int i = 0; i < 2; i++)
	{
		SetPosition(0, reScaled1-3, 25, groupOne[i]);
		SetPosition(0, reScaled2-3, 25, groupTwo[i]);
		SetPosition(0, reScaled3-3, 25, groupThree[i]);
	}
}
