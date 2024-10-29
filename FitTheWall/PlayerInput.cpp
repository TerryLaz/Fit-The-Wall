#include "PlayerInput.h"


PlayerInput::PlayerInput(GraphicsManager* graphicsManager, UINT width, UINT height,WindowManager* win):
	background(graphicsManager, "Models/quad.ftw"), winman(win)
{
	name = "";
	Enter_KeyDown = false;
	background.LoadTexture("Images/pi.png");
	//background.SetPosition(0, 0, 1);
	background.SetPosition(0, 3.65, -18);
	background.SetRotation(0.2, 0, 0);
	background.ScaleObject(3, 1.6, 1);
	background.Update();
	currenScreen = 3;
	this->width = width;
	this->height=height;
	letterOne = 32;
	letterTwo = 32;
	letterThree = 32;
	UP_KeyDown = false;
	DOWN_KeyDown = false;
	LEFT_KeyDown = false;
	RIGHT_KeyDown = false;
	currentLetter = 0;
}


void PlayerInput::changeLetter(int &letter)
{
	// key Up
	if (GetKeyState(VK_UP) & 0x8000 && UP_KeyDown == false)
	{
		bool letterIncreast = false;
		if (letter == 32)
		{
			letter = 65;
			letterIncreast = true;
		}

		if (letter == 90)
		{
			letter = 65;
			letterIncreast = true;
		}
		else
		{
			if (letterIncreast == false)
			{
				letter++;
			}
			letterIncreast = true;
		}

		UP_KeyDown = true;

	}
	if (!(GetKeyState(VK_UP) & 0x8000) && UP_KeyDown == true)
	{
		UP_KeyDown = false;
	}


	// Key Down
	if (GetKeyState(VK_DOWN) & 0x8000 && DOWN_KeyDown == false)
	{
		bool letterDecreast = false;
		if (letter == 32)
		{
			letter = 90;
			letterDecreast = true;
		}

		if (letter == 65)
		{
			letter = 90;
			letterDecreast = true;
		}
		else
		{
			if (letterDecreast == false)
			{
				letter--;
			}
			letterDecreast = true;
		}

		DOWN_KeyDown = true;
	}
	if (!(GetKeyState(VK_DOWN) & 0x8000) && DOWN_KeyDown == true)
	{
		DOWN_KeyDown = false;
	}
}

void PlayerInput::HandleKeyInput()
{

	if (GetKeyState(VK_RETURN) & 0x8000 && Enter_KeyDown == false)
	{

		Enter_KeyDown = true;
	}
	if (!(GetKeyState(VK_RETURN) & 0x8000) && Enter_KeyDown == true)
	{
		name = one + two + three;
		currenScreen = 4;
		Enter_KeyDown = false;
	}

	if (currentLetter==0)
	{
		changeLetter(letterOne);

		//knapp höger
		if (GetKeyState(VK_RIGHT) & 0x8000 && RIGHT_KeyDown==false)
		{
			currentLetter = 1;
			RIGHT_KeyDown = true;
		}
		else if (!(GetKeyState(VK_RIGHT) & 0x8000) && RIGHT_KeyDown == true)
		{
			RIGHT_KeyDown = false;
		}
	}

	if (currentLetter==1)
	{
		changeLetter(letterTwo);

		//knapp höger
		
		if (GetKeyState(VK_RIGHT) & 0x8000 && RIGHT_KeyDown == false)
		{
			currentLetter = 2;
			RIGHT_KeyDown = true;
		}
		else if (!(GetKeyState(VK_RIGHT) & 0x8000) && RIGHT_KeyDown == true)
		{
			RIGHT_KeyDown = false;
		}
		//knapp vänster
		if (GetKeyState(VK_LEFT) & 0x8000 && LEFT_KeyDown == false)
		{
			currentLetter = 0;
			LEFT_KeyDown = true;
		}
		else if (!(GetKeyState(VK_LEFT) & 0x8000) && LEFT_KeyDown == true)
		{
			LEFT_KeyDown = false;
		}
	}

	if (currentLetter==2)
	{
		changeLetter(letterThree);
		//knapp vänster
		if (GetKeyState(VK_LEFT) & 0x8000 && LEFT_KeyDown == false)
		{
			currentLetter = 1;
			LEFT_KeyDown = true;
		}
		else if (!(GetKeyState(VK_LEFT) & 0x8000) && LEFT_KeyDown == true)
		{
			LEFT_KeyDown = false;
		}
	}

	one = (char)letterOne;
	two = (char)letterTwo;
	three = (char)letterThree;
}


int PlayerInput::Update()
{
	HandleKeyInput();
	return currenScreen;
}


void PlayerInput::Render(DirectX::SpriteBatch& spriteBatch, DirectX::SpriteFont& spriteFont)
{
	background.Render();
	spriteBatch.Begin();
	spriteFont.DrawString(&spriteBatch, one.c_str(), DirectX::XMFLOAT2(float(width) / 2 - 120, float(height) / 2 - 120), DirectX::Colors::Aqua, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
	spriteFont.DrawString(&spriteBatch, two.c_str(), DirectX::XMFLOAT2(float(width) / 2 - 25, float(height) / 2 - 120), DirectX::Colors::Aqua, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
	spriteFont.DrawString(&spriteBatch, three.c_str(), DirectX::XMFLOAT2(float(width) / 2 + 70, float(height) / 2 - 120), DirectX::Colors::Aqua, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
	float posX = 0;
	if (currentLetter == 0)
		posX = (float(width) / 2 - 120);
	else if(currentLetter == 1)
		posX = (float(width) / 2 - 25);
	else
		posX = (float(width) / 2 + 70);

	spriteFont.DrawString(&spriteBatch, "_", DirectX::XMFLOAT2(posX, float(height) / 2 - 110), DirectX::Colors::Aqua, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
	
	spriteBatch.End();
}

std::string PlayerInput::GetName()
{
	return name;
}

void PlayerInput::Reset()
{
	currenScreen = 3;
	letterOne = 32;
	letterTwo = 32;
	letterThree = 32;
	Enter_KeyDown = false;
	UP_KeyDown = false;
	DOWN_KeyDown = false;
	LEFT_KeyDown = false;
	RIGHT_KeyDown = false;
	currentLetter = 0;
}
PlayerInput::~PlayerInput()
{

}

