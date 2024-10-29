#pragma once

#include "GraphicsManager.h"
#include "Camera.h"
#include "Level.h"
#include "Player.h"
#include "Timer.h"
#include "MyMouse.h"
#include "Pose.h"
#include "Light.h"
#include "Coin.h"
#include "Spotlight.h"
#include "Audiens.h"

class GameManager
{
private:

	GraphicsManager* graphicsManager;
	Level* level;
	Player player;
	Timer timer;
	MyMouse mouse;
	Pose pose;
	GameObject scene;
	Light lightManager;
	Spotlight spot1;
	Spotlight spot2;
	Spotlight spot3;
	Spotlight spot4;
	Camera gameCamera;
	Audiens audiens;

	float time;
	float wallSpeed;
	bool gameover;
	bool coinCollected;
	bool wallSucces;
	int score = 0;
	int currentScreen;
	int clearedStages = 0;
	bool playerIsHit;
	bool gameStarting = true;
	bool wallScoreAdded;

public:
	GameManager(GraphicsManager* graphicsManager);
	~GameManager();

	int Update(HWND window);
	void Render();
	void ResetGame();
	int GetScore();

	void DestroyPlayerLeak()
	{
		player.GetMesh().GetMaterial().diffuseMap.resourceView->Release();
	}
};