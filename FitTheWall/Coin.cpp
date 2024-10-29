#include "Coin.h"

Coin::Coin(GraphicsManager* graphicsManager, const char* filename):
	GameObject(graphicsManager, filename)
{
	poseIndex = 0;
	pose = 0;
	SetRandomPosition();
	position = XMFLOAT3(pose, -1, 30);
	GameObject::ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
	speed = 0.15;
	GameObject::Update();
}

Coin::~Coin()
{

}

void Coin::SetRandomPosition()
{
	std::srand((int)time(0));
	poseIndex = rand() % (0 + 3);
	if (poseIndex==0)
	{
		pose = -2;
	}
	else if(poseIndex==1)
	{
		pose = 0;
	}
	else
	{
		pose = 2;
	}
}

XMFLOAT3 Coin::getPosition()
{
	return position;
}

void Coin::Update()
{
	position.z = position.z - speed;
	GameObject::Update();
}

int Coin::GetScore()
{
	return score;
}

float Coin::GetSpawnPosition()
{
	return poseIndex;
}

void Coin::setSpeed(float speed)
{
	this->speed = 0.1 + speed;
}

void Coin::Restet()
{
	poseIndex = 0;
	pose = 0;
	SetRandomPosition();
	position = XMFLOAT3(pose, -2, 20);
	speed = 0.2;
}