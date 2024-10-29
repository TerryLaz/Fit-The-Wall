#pragma once
#include <Windows.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <string>

class MyMouse
{
private:
	float posX;
	float posY;
	bool isPressed;
	bool isCorrect;
	bool insideCoords;
	POINT ptCursor;
	HWND window;

	bool check1 = false;
	bool check2 = false;
	bool check3 = false;
	bool check4 = false;
public:
	MyMouse();
	~MyMouse();

	float GetPosX();
	float GetPosY();
	std::string GetPosAsString();
	bool IsPressed();
	bool IsCorrect();

	bool isInsideCoords(float xMin1, float xMax1, float xMin2, float xMax2, float yMin1, float yMax1, float yMin2, float yMax2);
	bool puzzleCheck(float checkX1, float checkX2, float checkY1, float checkY2);

	void SetIsCorrect(bool correct);
	void HandleInput();
	void Update(HWND window);
	void Render(DirectX::SpriteBatch& spriteBatch, DirectX::SpriteFont& spriteFont);
};