#pragma once
#include<iostream>
#include<string>
#include"GameObject.h"
#include <stdio.h>
#include"WindowManager.h"
#include <sstream> 

class PlayerInput
{
private:
	std::string name;
	std::string one, two, three;

	GameObject background;
	WindowManager* winman;

	UINT width;
	UINT height;
	int currenScreen;
	int currentLetter;
	int letterOne, letterTwo, letterThree;
	bool Enter_KeyDown;
	bool UP_KeyDown;
	bool DOWN_KeyDown;
	bool RIGHT_KeyDown;
	bool LEFT_KeyDown;

	void HandleKeyInput();
	void changeLetter(int &letter);

public:
	PlayerInput(GraphicsManager* graphicsManager, UINT width, UINT height,WindowManager* win);
	~PlayerInput();

	int Update();
	void Render(DirectX::SpriteBatch& spriteBatch, DirectX::SpriteFont& spriteFont);
	void Reset();
	std::string GetName();
};

