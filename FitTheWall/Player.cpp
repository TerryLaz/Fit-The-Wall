#include "Player.h"

Player::Player(GraphicsManager* graphicsManager, const char* filename) :
	GameObject(graphicsManager, filename)
{
	position = XMFLOAT3(0, -2.2, 5);
	PlayerSetUp();
	model.RenderSingleMesh(0);
	GameObject::ScaleObject(0.25);
}

Player::~Player()
{
}

void Player::HandleInput()
{
	if ((GetKeyState(VK_LEFT) & 0x8000 || GetKeyState(0x41) & 0x8000)  && L_KeyDown == false)
	{
		L_KeyDown = true;
		if (currentPosition > 0)
		{
			currentPosition--;
		}
	}
	if (!(GetKeyState(VK_LEFT) & 0x8000 || GetKeyState(0x41) & 0x8000) && L_KeyDown == true)
	{
		L_KeyDown = false;
	}

	if ((GetKeyState(VK_RIGHT) & 0x8000 || GetKeyState(0x44) & 0x8000) && R_keyDown == false)
	{
		R_keyDown = true;
		if (currentPosition < 2)
		{
			currentPosition++;
		}
	}
	if (!(GetKeyState(VK_RIGHT) & 0x8000 || GetKeyState(0x44) & 0x8000) && R_keyDown == true)
	{
		R_keyDown = false;
	}

	//number 1 pressed
	if (GetKeyState(0x31) & 0x8000)
	{
		SetCurrentPose(1);
	}
	//number 2 pressed
	if (GetKeyState(0x32) & 0x8000)
	{
		SetCurrentPose(2);
	}
	//number 3 pressed
	if (GetKeyState(0x33) & 0x8000)
	{
		SetCurrentPose(3);
	}
	/////////////////////////// Knockback testing ///////////////////////////
	//number 4 pressed
	if (GetKeyState(0x34) & 0x8000)
	{
		Knockback(0.05);
	}
	//number 5 pressed
	if (GetKeyState(0x35) & 0x8000)
	{
		FallDown();
	}
	//number 6 pressed
	if (GetKeyState(0x36) & 0x8000)
	{
		RotateFall();
	}
}

void Player::Update()
{
	HandleInput();

	if (currentPosition==0)
	{
		position.x = -2.2f;
	}
	if (currentPosition==1)
	{
		position.x = 0.f;
	}
	if (currentPosition == 2)
	{
		position.x = 2.2f;
	}

	//run base class update
	GameObject::Update();
}

void Player::ResetPosition()
{
	GameObject::SetRotation(0.0f, 0.0f, 0.0f);
	GameObject::SetPosition(0.0f, -2.2f, 5.0f);
	currentPosition = 1;
}

void Player::SetCurrentPose(int pose)
{
	currentPose = pose;
	//TODO: Debug code, ändra till rätt värde när modeller finns
	int meshToRender = currentPose;
	model.RenderSingleMesh(meshToRender);
}

int Player::GetCurrentPosition()
{
	return currentPosition;
}

int Player::GetCurrentPose()
{
	return currentPose;
}

void Player::Knockback(float knockbackSpeed)
{
	float xPos = GameObject::GetPosition().x;
	float yPos = GameObject::GetPosition().y;
	float zPos = GameObject::GetPosition().z;
	GameObject::SetPosition(xPos, yPos, zPos - knockbackSpeed); //Hämta wallSpeed, - 0.05
}

void Player::FallDown()
{
	float xPos = GameObject::GetPosition().x;
	float yPos = GameObject::GetPosition().y;
	float zPos = GameObject::GetPosition().z;
	GameObject::SetPosition(xPos, yPos - 0.03f, zPos);
}

void Player::RotateFall()
{
	float xRot = GameObject::GetRotation().x;
	float yRot = GameObject::GetRotation().y;
	float zRot = GameObject::GetRotation().z;
	GameObject::SetRotation(xRot - 0.3f, yRot, zRot);
}

void Player::SetCollisionWithWall(bool collidedWithWall)
{
	hitByWall = collidedWithWall;
}

void Player::SetOutsidePlayArea(bool isOutside)
{
	outSidePlayArea = isOutside;
}

bool Player::IsHitByWall() const
{
	return hitByWall;
}

bool Player::IsOutSidePlayArea() const
{
	return outSidePlayArea;
}

bool Player::HasLostGame()
{
	return false;
}

//private funktion to set start values of variables
void Player::PlayerSetUp()
{
	currentPosition = 1;
	currentPose = 0;
	L_KeyDown=false;
	R_keyDown = false;
	hitByWall = 0;
	outSidePlayArea = 0;

	for (int i = 0; i < totalNrOfPositions; i++)
	{
		positions[i] = i;
	}
}
