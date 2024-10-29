#pragma once
#include "GameObject.h"

class Guide
{
private:
	GameObject guide;
	bool buttonPressed;
	int currentScreen;
	void SetScreen();

public:
	Guide(GraphicsManager* graphicsManager);
	~Guide();

	void Update();
	void Render();
	void ResetGuide();
	int changeScreen();
};