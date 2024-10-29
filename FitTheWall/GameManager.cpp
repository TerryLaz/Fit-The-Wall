#include "GameManager.h"


GameManager::GameManager(GraphicsManager* graphicsManager) :
	graphicsManager(graphicsManager), player(graphicsManager, "Models/Player.ftw"), score(0), pose(graphicsManager),
	scene(graphicsManager, "Models/sceenTextured.ftw"), lightManager(graphicsManager), audiens(graphicsManager, "Models/publik2.ftw"),
	spot1(graphicsManager), spot2(graphicsManager), spot3(graphicsManager), spot4(graphicsManager), gameCamera(graphicsManager), time(0)
{
	gameover = false;
	wallSpeed = 0.01f;

	level = new Level(graphicsManager, 3, wallSpeed);
	timer.Start();
	currentScreen = 1;
	wallSucces = false;
	wallScoreAdded = false;
	scene.SetPosition(0, -3, 25);
	scene.SetRotation(0, 3.14, 0);

	//update once to set position and rotation
	scene.Update();

	lightManager.SetDirectionalLight(XMFLOAT3(0.2f, -0.5f, 1.0f), XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f), XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f));
	lightManager.SetDirectionalLight2(XMFLOAT3(0.2f, -0.5f, -1.0f), XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f), XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f));
	lightManager.SetPointLight(XMFLOAT3(0.0f, 0, -0.5), 100.0f, XMFLOAT3(0.4f, 0.2f, 0.1f));
	lightManager.SetSpotLight(XMFLOAT3(0.0f, 3.0f, -10.0f), 100.0f, XMFLOAT3(0.4f, 0.2f, 0.0f), 50.0f);

	spot1.SetPosition(-6, 0, -4);
	spot2.SetPosition(6, 0, -4);
	spot3.SetPosition(-9, 0, 0);
	spot4.SetPosition(9, 0, 0);
	spot1.SetRotation(0.0f, XMConvertToRadians(30), 0.0f);
	spot2.SetRotation(0.0f, -XMConvertToRadians(30), 0.0f);
	spot3.SetRotation(0.0f, XMConvertToRadians(90), 0.0f);
	spot4.SetRotation(0.0f, -XMConvertToRadians(90), 0.0f);

	gameCamera.InitCamera(1920.f / 1080.f);
	gameCamera.SetPosition(XMFLOAT3(0, 1, 20));
	gameCamera.SetForward(XMFLOAT3(0, 0, 5));
}

GameManager::~GameManager()
{
	delete level;
}

int GameManager::Update(HWND window)
{

	// Rotate spotlights
	spot1.RotateSpotlight(3, { -2.0f, 2.0f, 0.0f }, 4.0f, 6.0f, 0.0f);
	spot1.RotateSpotlight(0, { -2.0f, 2.0f, 0.0f }, 4.0f, 6.0f, 0.0f);
	spot1.RotateSpotlight(1, { 0.0f, 2.0f, 0.0f }, 0.0f, 6.0f, 0.0f);
	spot1.Update();

	spot2.RotateSpotlight(3, { -2.0f, -2.0f, 0.0f }, 4.0f, 6.0f, 0.0f);
	spot2.RotateSpotlight(0, { -2.0f, -2.0f, 0.0f }, 4.0f, 6.0f, 0.0f);
	spot2.RotateSpotlight(1, { 0.0f, -2.0f, 0.0f }, 0.0f, 6.0f, 0.0f);
	spot2.Update();

	spot3.RotateSpotlight(3, { -2.0f, 2.0f, 0.0f }, 4.0f, 6.0f, 0.0f);
	spot3.RotateSpotlight(0, { -2.0f, 2.0f, 0.0f }, 4.0f, 6.0f, 0.0f);
	spot3.RotateSpotlight(1, { 0.0f, 2.0f, 0.0f }, 0.0f, 6.0f, 0.0f);
	spot3.Update();

	spot4.RotateSpotlight(3, { -2.0f, -2.0f, 0.0f }, 4.0f, 6.0f, 0.0f);
	spot4.RotateSpotlight(0, { -2.0f, -2.0f, 0.0f }, 4.0f, 6.0f, 0.0f);
	spot4.RotateSpotlight(1, { 0.0f, -2.0f, 0.0f }, 0.0f, 6.0f, 0.0f);
	spot4.Update();

	player.Update();
	lightManager.Update();
	gameCamera.Update();
	timer.Update();
	audiens.Update(time);
	time += 0.15;

	if (gameStarting)
	{
		float posZ = gameCamera.getPosition().z;
		if (posZ > -20)
		{
			posZ -= 0.4;
		}
		float posX = gameCamera.getPosition().x;
		if (posZ > 0 && posX < 20)
		{
			posX += 0.4;
		}
		else
		{
			posX -= 0.4;
		}
		gameCamera.SetPosition(XMFLOAT3(posX, 4, posZ));
		if (posZ <= -20 && posX < 0)
		{
			gameStarting = false;
			gameCamera.SetPosition(XMFLOAT3(3, 1, 10));
			gameCamera.SetForward(XMFLOAT3(0, 0, 30));
		}
	}
	else
	{
		Wall* lastWall = level->GetCurrentWall();

		level->Update();
		//audiens.Update(time);
		pose.Update();

		mouse.Update(window);
		level->GetCoin()->setSpeed(wallSpeed);
		//game logic

		//check if level has changed number of cleared walls, meaning last wall is cleared and score is updated 
		if (lastWall != level->GetCurrentWall())
		{
			score += 100;
			player.SetCurrentPose(0);
			gameCamera.SetPosition(XMFLOAT3(3, 1, 10));
			gameCamera.SetForward(XMFLOAT3(0, 0, 30));
		}

		if (level->GetCurrentWall()->GetPosition().z < 26)
		{
			gameCamera.SetPosition(XMFLOAT3(0, 4, -20));
			gameCamera.SetForward(XMFLOAT3(0, 0, 1));
		}


		// puzzle
		if (level->GetCurrentWall()->GetCorrectPose() == 1)
		{
			mouse.isInsideCoords(1150 - 30, 1305 + 30, 1221 - 30, 1221 + 30, 433 - 30, 433 + 30, 433 - 30, 560 + 30);
			mouse.puzzleCheck(1150, 1221, 433, 560);
			if (mouse.IsCorrect())
			{
				player.SetCurrentPose(1);
			}
		}
		else if (level->GetCurrentWall()->GetCorrectPose() == 2)
		{
			mouse.isInsideCoords(1152 - 30, 1152 + 30, 1152 - 30, 1295 + 30, 430 - 30, 560 + 30, 560 - 30, 560 + 30);
			mouse.puzzleCheck(1152, 1295, 430, 560);
			if (mouse.IsCorrect())
			{
				player.SetCurrentPose(2);
			}
		}
		else if (level->GetCurrentWall()->GetCorrectPose() == 3)
		{
			mouse.isInsideCoords(1153 - 30, 1292 + 30, 1292 - 30, 1292 + 30, 432 - 30, 432 + 30, 432 - 30, 544 + 30);
			mouse.puzzleCheck(1153, 1292, 432, 544);
			if (mouse.IsCorrect())
			{
				player.SetCurrentPose(3);
			}
		}

		if (level->GetCurrentWall()->GetPosition().z <= 6 && level->GetCurrentWall()->GetPosition().z >= 4)
		{
			if (level->GetCurrentWall()->GetCorrectPosition() != player.GetCurrentPosition()
				|| level->GetCurrentWall()->GetCorrectPose() != player.GetCurrentPose())
			{
				playerIsHit = true;
			}
			else if (level->GetCurrentWall()->GetCorrectPosition() == player.GetCurrentPosition() && level->GetCurrentWall()->GetCorrectPose() == player.GetCurrentPose() && wallSucces == false)
			{
				wallSucces = true;
				if (wallScoreAdded == false)
				{
					score += level->GetCurrentWall()->GetScore();
					wallScoreAdded = true;
				}
			}
		}
		if (wallScoreAdded == true && level->GetCurrentWall()->GetPosition().z >= 8)
		{
			wallScoreAdded = false;
		}

		if (playerIsHit)
		{
			// Player knockback on collision with wall
			player.Knockback(wallSpeed);
		}
		if (player.GetPosition().z <= 1.3f)
		{
			// Player transformation after collision with wall
			player.FallDown();
			if (player.GetRotation().x >= -2.0f)
			{
				player.RotateFall();
			}
			if (player.GetPosition().z <= 0.0f)
			{
				gameover = true;
			}
		}
		if (wallSucces == true)
		{
			wallSucces = false;
		}

		if (level->GetCoin()->GetPosition().z <= 5 && level->GetCoin()->GetSpawnPosition() == player.GetCurrentPosition() && coinCollected == false && level->GetCoin()->GetPosition().z >= 3)
		{
			coinCollected = true;
			score += level->GetCoin()->GetScore();
			level->RemoveCoin();
		}
		else if (level->GetCoin()->getPosition().z <= -2.5f)
		{
			level->RemoveCoin();
		}
		if (coinCollected == true && level->GetCoin()->GetPosition().z >= 8)
		{
			coinCollected = false;
		}
		if (level->IsLevelCleared())
		{
			clearedStages++;
			wallSpeed += +0.05f;

			score += 100;
			player.SetCurrentPose(0);

			//Tömmer Förgående omgång väggar innan nya kommer.
			level->EmptyWallVector();
			level = new Level(graphicsManager, 3, wallSpeed);
			gameCamera.SetPosition(XMFLOAT3(3, 1, 10));
			gameCamera.SetForward(XMFLOAT3(0, 0, 30));
		}
	}
	if (gameover)
	{
		currentScreen = 3;
		lightManager.ClearLightBuffer();
	}
	return currentScreen;
}

void GameManager::Render()
{
	if (!gameover)
	{
		graphicsManager->StartRenderPass(gameCamera.GetCameraBuffer());
		graphicsManager->SetShaderBuffers(lightManager.GetLightBuffer());
		//RENDER OPAQUE OBJECTS
		player.Render();
		scene.Render();
		level->Render();
		audiens.Render();

		//RENDER GUI ELEMENTS
		graphicsManager->StartGUIBlendStateRenderPass();
		spot1.Render();
		spot2.Render();
		spot3.Render();
		spot4.Render();

		graphicsManager->StartGUIShaderRenderPass();
		level->RenderGUIElements();

		pose.Render(level->GetCurrentWall()->GetCorrectPose());
		graphicsManager->GetSpriteBatch().Begin();
		timer.Render(graphicsManager->GetSpriteBatch(), graphicsManager->GetSpriteFont());
		graphicsManager->GetSpriteFont().DrawString(&graphicsManager->GetSpriteBatch(),
			("Score: " + std::to_string(score)).c_str(), XMFLOAT2(1600, 50), DirectX::Colors::SpringGreen, 0.0f,
			DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f));
		graphicsManager->GetSpriteFont().DrawString(&graphicsManager->GetSpriteBatch(),
			("Stage: " + std::to_string(clearedStages + 1)).c_str(), XMFLOAT2(1600, 100), DirectX::Colors::SpringGreen, 0.0f,
			DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f));
		//mouse.Render(graphicsManager->GetSpriteBatch(), graphicsManager->GetSpriteFont());
		graphicsManager->GetSpriteBatch().End();
	}
}


void GameManager::ResetGame()
{
	delete level;
	gameover = false;
	wallSpeed = 0.1f;
	level = new Level(graphicsManager, 3, wallSpeed);
	timer.Start();
	currentScreen = 1;
	score = 0;
	wallSucces = false;
	playerIsHit = false;
	player.ResetPosition();
	clearedStages = 0;
	gameStarting = true;
	gameCamera.SetPosition(XMFLOAT3(0, 1, 20));
	gameCamera.SetForward(XMFLOAT3(0, 0, 5));

	lightManager.SetDirectionalLight(XMFLOAT3(0.2f, -0.5f, 1.0f), XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f), XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f));
	lightManager.SetPointLight(XMFLOAT3(0.5f, 0, -0.5), 100.0f, XMFLOAT3(0.4f, 0.2f, 0.1f));
	lightManager.SetSpotLight(XMFLOAT3(0.0f, 3.0f, -1.0f), 100.0f, XMFLOAT3(0.4f, 0.2f, 0.0f), 50.0f);
}

int GameManager::GetScore()
{
	return score;
}
