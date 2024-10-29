#include "Wall.h"

Wall::Wall(GraphicsManager* graphicsManager):
	GameObject(graphicsManager)
{
	speed = 0.1f;
	isDown = false;
	goingDown = false;
	ConfigureWall(1);
}

Wall::Wall(GraphicsManager* graphicsManager, int type) :
	GameObject(graphicsManager)
{
	speed = 0.1f;
	isDown = false;
	goingDown = false;
	ConfigureWall(type);

	GameObject::LoadModel(config.filename);

	position = XMFLOAT3(0, -10, 30);
	GameObject::ScaleObject(0.25);
	GameObject::Update();
}

Wall::Wall(GraphicsManager* graphicsManager, int type, float wallSpeed) :
	GameObject(graphicsManager)
{
	speed = wallSpeed;
	isDown = false;
	goingDown = false;
	ConfigureWall(type);

	GameObject::LoadModel(config.filename);

	position = XMFLOAT3(0, -8, 30);
	GameObject::ScaleObject(0.25);
	GameObject::Update();
}

Wall::~Wall()
{
	
}

void Wall::ConfigureWall(int type)
{
	switch (type)
	{
	case 0:
		config.correctPose = 1;
		config.correctPosition = 0;
		config.filename = "Models/w0.ftw";
		break;
	case 1:
		config.correctPose = 1;
		config.correctPosition = 1;
		config.filename = "Models/w1.ftw";
		break;
	case 2:
		config.correctPose = 1;
		config.correctPosition = 2;
		config.filename = "Models/w2.ftw";
		break;
	case 3:
		config.correctPose = 2;
		config.correctPosition = 0;
		config.filename = "Models/w3.ftw";
		break;
	case 4:
		config.correctPose = 2;
		config.correctPosition = 1;
		config.filename = "Models/w4.ftw";
		break;
	case 5:
		config.correctPose = 2;
		config.correctPosition = 2;
		config.filename = "Models/w5.ftw";
		break;
	case 6:
		config.correctPose = 3;
		config.correctPosition = 0;
		config.filename = "Models/w6.ftw";
		break;
	case 7:
		config.correctPose = 3;
		config.correctPosition = 1;
		config.filename = "Models/w7.ftw";
		break;
	case 8:
		config.correctPose = 3;
		config.correctPosition = 2;
		config.filename = "Models/w8.ftw";
		break;
	default:
		config.correctPose = 0;
		config.correctPosition = 1;
		config.filename = "Models/w1.ftw";
		break;
	}
}

void Wall::Update()
{	

	if (position.y <= -2.2 && !goingDown)
	{
		position.y = position.y + speed;
	}	
	else if (position.z <= -2.9 && !isDown)
	{
		goingDown = true;
		position.y = position.y - speed;
		if (position.y <= -10)
			isDown = true;
	}
	else
	{
		position.z = position.z - speed;
	}

	//position.z = position.z - speed;


	//run base class update
	GameObject::Update();
}

int Wall::GetCorrectPosition()
{
	return config.correctPosition;
}

int Wall::GetCorrectPose()
{
	return config.correctPose;
}

int Wall::GetScore()
{
	return score;
}
