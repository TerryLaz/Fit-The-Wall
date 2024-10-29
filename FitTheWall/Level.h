#pragma once
#include "Wall.h"
#include <vector>
#include "Coin.h"

class Level
{
private:
	std::vector<Wall*> walls;
	Wall* currentWall;
	Coin* currentCoin;
	GameObject stageClear;
	GameObject wallLights;
	GraphicsManager* graphicsMan;

	int clearedWalls = 0;
	int coinRotation;
	bool coinSpawn;
	bool levelClear;

	void SpawnCoin(GraphicsManager* graphicsManager);

public:
	Level(GraphicsManager* graphicsManager, int nrOfWalls, float wallSpeed);
	~Level();

	void Update();
	void Render();
	void RenderGUIElements();

	bool IsLevelCleared();
	Wall* GetCurrentWall();

	void RemoveCoin();
	Coin* GetCoin();

	void EmptyWallVector();

	int GetClearedWalls();
};
