#pragma once
#include"GameObject.h"
#include"Highscore.h"

class HighscoreScreen
{

// MAINMENU = 0
// GAME = 1
// GAMEOVER = 2
// PLAYERINPUT = 3
// HIGHSCORE = 4
// QUITGAME = 5

private:
	GameObject background;
	Highscore* highscore;

	int currentScreen;
	int wordDistanceVertical;
	int wordDistanceHorizontal;
	int score[3];
	std::string name[3];
	UINT width;
	UINT height;

	void HandleKeyInput();
	bool Enter_KeyDown;
	std::string yourScore = "Your Score:";

public:
	HighscoreScreen(GraphicsManager* graphicsManager, UINT width, UINT height,Highscore* higscore);
	~HighscoreScreen();

	int Update();
	void Render(DirectX::SpriteBatch& spriteBatch, DirectX::SpriteFont& spriteFont);
	void Reset();
};

