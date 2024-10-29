#pragma once
#include "GameGui.h"

class MainMenu
{
private:
	GameGui playButton;
	GameGui highScoreButton;
	GameGui guideButton;
	GameGui quitButton;
	GameGui titleBox;

	int activeButton;
	int selectedButton;
	float time;

	bool U_KeyDown;
	bool D_keyDown;	
	bool ENTER_keyDown;

public:
	MainMenu(GraphicsManager* graphicsManager, XMFLOAT3 camPos);
	~MainMenu();

	int GetSelectedButton();
	void SetSelectedButton(int number);
	void move();
	void Update();
	void Render();
	void ResetSelection();

};