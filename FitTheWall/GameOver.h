#pragma once
#include "GameObject.h"

class GameOver
{
private:
	GameObject gameOverWall;
	bool buttonPressed;
	int currenScreen;
	void SetScreen();

public:
	GameOver(GraphicsManager* graphicsManager);
	~GameOver();

	void Update();
	void Render();
	void ResetGameOver();
	int changeScreen();
};