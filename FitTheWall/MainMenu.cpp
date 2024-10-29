#include "MainMenu.h"

MainMenu::MainMenu(GraphicsManager* graphicsManager, XMFLOAT3 camPos):	
	titleBox(graphicsManager, "Models/titleBox2Inv.ftw", camPos, XMFLOAT2(0.0f, 0.5f)),
	playButton(graphicsManager, "Models/playBox2Inv.ftw", camPos, XMFLOAT2(0.0f, -0.75f)),
	highScoreButton(graphicsManager, "Models/highScoreButton.ftw", camPos, XMFLOAT2(0.0f, -1.50f)),
	guideButton(graphicsManager, "Models/guideButton.ftw",camPos, XMFLOAT2(0.0f, -2.25f)),
	quitButton(graphicsManager, "Models/quitBox2Inv.ftw", camPos, XMFLOAT2(0.0f, -3.0f)),
	activeButton(0), selectedButton(0), U_KeyDown(false), D_keyDown(false), ENTER_keyDown(false), time(0)
{	
	titleBox.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
	playButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
	highScoreButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
	guideButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
	quitButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
	titleBox.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));

	titleBox.SetRotation(0, 3.1415, 0);
	playButton.SetRotation(0, 3.1415, 0);
	highScoreButton.SetRotation(0, 3.1415, 0);
	guideButton.SetRotation(0, 3.1415, 0);
	quitButton.SetRotation(0, 3.1415, 0);
}

MainMenu::~MainMenu()
{

}

int MainMenu::GetSelectedButton()
{
	return selectedButton;
}

void MainMenu::SetSelectedButton(int number)
{
	this->selectedButton = number;
}

void MainMenu::move()
{
	if (GetKeyState(VK_DOWN) & 0x8000 && D_keyDown == false)
	{
		D_keyDown = true;
		if (activeButton < 3)
		{
			activeButton++;
		}
	}
	if (!(GetKeyState(VK_DOWN) & 0x8000) && D_keyDown == true)
	{
		D_keyDown = false;
	}

	if (GetKeyState(VK_UP) & 0x8000 && U_KeyDown == false)
	{
		U_KeyDown = true;
		if (activeButton > 0)
		{
			activeButton--;
		}
		
	}
	if (!(GetKeyState(VK_UP) & 0x8000) && U_KeyDown == true)
	{
		U_KeyDown = false;
	}

	if (GetKeyState(VK_RETURN) & 0x8000 && ENTER_keyDown == false)
	{
		ENTER_keyDown = true;
	}

	if (!(GetKeyState(VK_RETURN) & 0x8000) && ENTER_keyDown == true)
	{
		if (activeButton == 0)//Play
		{
			activeButton = 1;
		}
		else if (activeButton == 1)//Highscore
		{
			activeButton = 4;
		}
		else if (activeButton == 2)//Guide
		{
			activeButton = 6;
		}
		else if (activeButton == 3)//Quit
		{
			activeButton = 5;
		}

		selectedButton = activeButton;
		ENTER_keyDown = false;
	}

}

void MainMenu::Update()
{
	float activeScale = 1.2;

	if (activeButton == 0)
	{
		playButton.ScaleObject((XMFLOAT3(0.5 * activeScale, 0.5 * activeScale, 0.5 * activeScale)));
		highScoreButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
		guideButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
		quitButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));

		playButton.Update(1, time + 3, 1.0);
		highScoreButton.Update(1, time + 1, 0.25);
		guideButton.Update(1, time + 2, 0.25);
		quitButton.Update(1, time + 4, 0.25);
	}
	else if (activeButton == 1)
	{
		playButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
		highScoreButton.ScaleObject((XMFLOAT3(0.5 * activeScale, 0.5 * activeScale, 0.5 * activeScale)));
		guideButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
		quitButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
		guideButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));

		playButton.Update(1, time + 3, 0.25);
		highScoreButton.Update(1, time + 1, 1.0);
		guideButton.Update(1, time + 2, 0.25);
		quitButton.Update(1, time + 4, 0.25);
	}
	else if (activeButton == 2)
	{		
		playButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
		highScoreButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
		guideButton.ScaleObject((XMFLOAT3(0.5 * activeScale, 0.5 * activeScale, 0.5 * activeScale)));
		quitButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));

		playButton.Update(1, time + 3, 0.25);
		highScoreButton.Update(1, time + 1, 0.25);
		guideButton.Update(1, time + 2, 1.0);
		quitButton.Update(1, time + 4, 0.25);
	}
	else if (activeButton == 3)
	{
		playButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
		highScoreButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
		guideButton.ScaleObject(XMFLOAT3(0.5, 0.5, 0.5));
		quitButton.ScaleObject((XMFLOAT3(0.5 * activeScale, 0.5 * activeScale, 0.5 * activeScale)));

		playButton.Update(1, time + 3, 0.25);
		highScoreButton.Update(1, time + 1, 0.25);
		guideButton.Update(1, time + 2, 0.25);
		quitButton.Update(1, time + 4, 1.0);
	}
	

	titleBox.Update(0.5, time, 0.1);

	time += 0.1;
}

void MainMenu::Render()
{
	playButton.Render();
	highScoreButton.Render();
	guideButton.Render();
	quitButton.Render();
	titleBox.Render();
}

void MainMenu::ResetSelection()
{
	selectedButton = 0;
	activeButton = 0;
}
