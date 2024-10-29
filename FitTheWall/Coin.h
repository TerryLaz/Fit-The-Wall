#pragma once
#include"GameObject.h"

class Coin:
	public GameObject
{
private:
	const int score = 10;
	float speed;
	float pose;
	int poseIndex;
	void SetRandomPosition();


public:
	Coin(GraphicsManager* graphicsManager, const char* filename);
	~Coin();

	void Update();
	int GetScore();
	float GetSpawnPosition();
	void setSpeed(float speed);
	void Restet();
	XMFLOAT3 getPosition();
};

