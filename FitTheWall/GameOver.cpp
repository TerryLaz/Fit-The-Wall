#include "GameOver.h"

GameOver::GameOver(GraphicsManager* graphicsManager)
	:gameOverWall(graphicsManager, "Models/quad.ftw")
{
	currenScreen = 2;
	buttonPressed = false;
	gameOverWall.LoadTexture("Images/GameOverBild.png");
	gameOverWall.SetPosition(0, 3.6, -18);
	gameOverWall.SetRotation(0.2, 0, 0);
}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
	gameOverWall.Update();
	SetScreen();
}

void GameOver::Render()
{
	gameOverWall.Render();
}

int GameOver::changeScreen()
{
	return currenScreen;
}

void GameOver::SetScreen()
{
	if (GetKeyState(VK_RETURN)<0 && buttonPressed == false)
	{
		buttonPressed = true;
	}
	if (GetKeyState(VK_RETURN) > 0 && buttonPressed == true)
	{
		currenScreen = 3;
	}
}

void GameOver::ResetGameOver()
{
	
	currenScreen = 2;
	buttonPressed = false;
}
