#include "Level.h"

Level::Level(GraphicsManager* graphicsManager, int nrOfWalls, float wallSpeed)
	: stageClear(graphicsManager, "Models/quad.ftw"), wallLights(graphicsManager, "Models/quad.ftw")
{
	graphicsMan = graphicsManager;
	levelClear = false;
	coinRotation = 0;
	SpawnCoin(graphicsMan);
	coinSpawn = true;

	for (int i = 0; i < nrOfWalls; i++)
	{
		int wallType = rand() % 9;

		walls.push_back(new Wall(graphicsManager, wallType, wallSpeed));
	}

	//sets current wall to first wall in list and removes it from the list
	currentWall = walls.front();

	stageClear.LoadTexture("Images/stage-clear.png");
	stageClear.SetPosition(0, 3, -15);
	stageClear.ScaleObject(0);
	stageClear.Update();

	wallLights.LoadTexture("Images/wall-blur.png");
	wallLights.ScaleObject(7.5, 4.9, 1);
	wallLights.SetPosition(currentWall->GetPosition().x, currentWall->GetPosition().y + 2.3, currentWall->GetPosition().z - 0.6);
	wallLights.Update();
}

Level::~Level()
{
	delete currentCoin;
	EmptyWallVector();
}

void Level::Update()
{
	if (currentCoin->GetPosition().z > -2.5f)
	{
		currentCoin->Update();
		coinRotation += 5;
		if (coinRotation < 360)
		{
			currentCoin->SetRotation(0, XMConvertToRadians(coinRotation), 0);
		}
		else
		{
			coinRotation = 0;
		}
	}

	wallLights.SetPosition(currentWall->GetPosition().x, currentWall->GetPosition().y + 2.3, currentWall->GetPosition().z - 0.6);
	wallLights.Update();

	if (currentWall->GetPosition().z > -3.0)
	{
		currentWall->Update();
	}
	else
	{
		clearedWalls++;
		if (clearedWalls < walls.size())
		{
			currentWall = walls.at(clearedWalls);
		}
		else
		{
			if (stageClear.GetScale().x < 5)
			{
				stageClear.ScaleObject(stageClear.GetScale().x + 0.25);
			}
			else
			{
				levelClear = true;
			}
		}
	}
}

void Level::Render()
{
	currentCoin->Render();
	currentWall->Render();
}

void Level::RenderGUIElements()
{
	wallLights.Render();
	stageClear.Render();
}

bool Level::IsLevelCleared()
{
	return levelClear;
}

Wall* Level::GetCurrentWall()
{
	return currentWall;
}

void Level::SpawnCoin(GraphicsManager* graphicsManager)
{
	currentCoin = new Coin(graphicsManager, "Models/coin.ftw");
}

void Level::RemoveCoin()
{
	if (currentCoin != nullptr)
	{
		delete currentCoin;
	}

	SpawnCoin(graphicsMan);
}

Coin* Level::GetCoin()
{
	return currentCoin;
}

void Level::EmptyWallVector()
{
	for (int i = 0; i < walls.size(); i++)
	{
		delete walls.at(i);
	}
}

int Level::GetClearedWalls()
{
	return clearedWalls;
}
