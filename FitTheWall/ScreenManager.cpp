#include "ScreenManager.h"

ScreenManager::ScreenManager(GraphicsManager* graphicsManager, UINT width, UINT height, WindowManager* winman):
	graphicsManager(graphicsManager), camera(graphicsManager), gameOver(graphicsManager), winman(winman),
	currentScreen(0), playerInput(graphicsManager, width, height,winman), mainMenu(graphicsManager, camera.getPosition()), game(graphicsManager),
	highscoreScreen(graphicsManager,width,height,&highscore), guideScreen(graphicsManager)
{
	camera.InitCamera(static_cast<float>(width) / height);
	menuExists = true;
	gameExists = true;
	scoreCompaired = false;
	spaceButtonPressed = false;
}

ScreenManager::~ScreenManager()
{
	
}

// MAINMENU = 0
// GAME = 1
// GAMEOVER = 2
// PLAYERINPUT = 3
// HIGHSCORE = 4
// QUITGAME = 5
// Guide = 6

void ScreenManager::Update()
{
	camera.Update();

	if(currentScreen == 0)
	{
		mainMenu.move();
		mainMenu.Update();
		currentScreen = mainMenu.GetSelectedButton();

		if (currentScreen != 0)
		{
			mainMenu.ResetSelection();
			highscore.Reset();
			scoreCompaired = false;
			spaceButtonPressed = false;
			//reset game if game is started
			if (currentScreen == 1)
			{
				game.ResetGame();
			}
		}
	}
	else if(currentScreen == 1)
	{
		currentScreen = game.Update(winman->GetWindow());
		if (currentScreen!=1)
		{
			highscore.SetNewScore(game.GetScore());
		}
	}
	else if (currentScreen == 2)
	{
		currentScreen = gameOver.changeScreen();
		if (currentScreen != 2)
		{
			gameOver.ResetGameOver();
		}
	}
	else if(currentScreen == 3)
	{
		currentScreen = playerInput.Update();

		if (currentScreen != 3)
		{
			highscore.setNewName(playerInput.GetName());
			playerInput.Reset();
		}
	}
	else if (currentScreen == 4)
	{
		if (scoreCompaired == false)
		{
			highscore.compairHigScore();
			scoreCompaired = true;
		}

		currentScreen = highscoreScreen.Update();
		if (currentScreen != 4)
		{
			highscoreScreen.Reset();
		}
	}
	else if (currentScreen == 6)
	{
		guideScreen.Update();
		currentScreen = guideScreen.changeScreen();
		if (currentScreen != 6)
		{
			guideScreen.ResetGuide();
		}
	}
}

void ScreenManager::Render()
{
	//Start this render pass
	graphicsManager->StartRenderPass(camera.GetCameraBuffer());

	if (currentScreen == 0)
	{
		//Orsakar 9 minnesläckor i början
		mainMenu.Render();
	}
	else if (currentScreen == 1)
	{
		//orsakar 13 minnesläckor!
		game.Render();
	}

	if (currentScreen==2)
	{
		//orsakar 4 minnesläcka
		gameOver.Render();
	}
	else if (currentScreen==3)
	{
		//Orsakar 4 minnesläckor!
		playerInput.Render(graphicsManager->GetSpriteBatch(), graphicsManager->GetSpriteFont());
	}

	if (currentScreen==4)
	{
		//Orsakar ingen minnesläcka
		highscoreScreen.Render(graphicsManager->GetSpriteBatch(), graphicsManager->GetSpriteFont());
	}
	if (currentScreen == 6)
	{
		//Orsakar ingen minnesläcka
		guideScreen.Render();
	}

	//Render pass done 
	graphicsManager->StopRenderPass();
}

int ScreenManager::GetCurrenScreen()
{
	return currentScreen;
}
