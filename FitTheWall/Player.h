#pragma once
#include<Windows.h>
#include "GameObject.h"

class Player :
	public GameObject
{
private:
	static const int totalNrOfPositions = 3;
	int positions[totalNrOfPositions];
	int currentPosition;
	int currentPose;

	bool L_KeyDown;
	bool R_keyDown;
	bool hitByWall;
	bool outSidePlayArea;
	bool inWaterTank;

	void PlayerSetUp();
	void HandleInput();

public:
	Player(GraphicsManager* graphicsManager, const char* filename);
	~Player();
	void Update();
	void ResetPosition();
	void SetCurrentPose(int pose);
	void Knockback(float knockbackSpeed);
	void FallDown();
	void RotateFall();
	void SetCollisionWithWall(bool collidedWithWall);
	void SetOutsidePlayArea(bool isOutside);
	int GetCurrentPosition();
	int GetCurrentPose();
	bool IsHitByWall() const;
	bool IsOutSidePlayArea() const;
	bool HasLostGame();
};