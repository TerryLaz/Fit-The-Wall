#pragma once
#include "GameObject.h"

class Audiens:
	public GameObject
{
private:
	float newPosition;
	float currentPosition;
public:
	Audiens(GraphicsManager* graphicsManager, const char* filename);
	~Audiens();
	int groupOne[2];
	int groupTwo[2];
	int groupThree[2];

	void Update(float time);

	void moveAudiens(float scale, float time);
};

