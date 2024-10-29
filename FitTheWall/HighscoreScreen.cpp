#include "HighscoreScreen.h"

HighscoreScreen::HighscoreScreen(GraphicsManager* graphicsManager, UINT width, UINT height, Highscore* higscore):
	background(graphicsManager, "Models/quad.ftw"), highscore(higscore)
{
	Enter_KeyDown = false;
	currentScreen = 4;
	background.LoadTexture("Images/hsb.png");
	background.SetPosition(0, 3.65, -18);
	background.SetRotation(0.2, 0, 0);
	background.ScaleObject(3,1.6,1);
	background.Update();
	this->width = width;
	this->height = height;

	wordDistanceVertical = height / 4;
	wordDistanceHorizontal = width / 4;
}

void HighscoreScreen::HandleKeyInput()
{
	if (GetKeyState(VK_RETURN) & 0x8000 && Enter_KeyDown == false)
	{		

		Enter_KeyDown = true;
	}
	if (!(GetKeyState(VK_RETURN) & 0x8000) && Enter_KeyDown == true)
	{
		currentScreen = 0;
		Enter_KeyDown = false;
	}
}

int HighscoreScreen::Update()
{
	name[0] = highscore->ReadHigscore()[0];
	name[1] = highscore->ReadHigscore()[2];
	name[2] = highscore->ReadHigscore()[4];

	score[0] = stoi(highscore->ReadHigscore()[1]);
	score[1] = stoi(highscore->ReadHigscore()[3]);
	score[2] = stoi(highscore->ReadHigscore()[5]);

	HandleKeyInput();

	return currentScreen;
}

void HighscoreScreen::Render(DirectX::SpriteBatch& spriteBatch, DirectX::SpriteFont& spriteFont)
{
	background.Render();
	spriteBatch.Begin();
	spriteFont.DrawString(&spriteBatch, yourScore.c_str(), DirectX::XMFLOAT2(float(width) / 8, float(height) / 4 + (wordDistanceVertical * 3) - 50), DirectX::Colors::Cyan, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f));
	spriteFont.DrawString(&spriteBatch, highscore->GetNewName().c_str(), DirectX::XMFLOAT2(float(width) / 4, float(height) / 4 + (wordDistanceVertical * 3) - 50), DirectX::Colors::Cyan, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f));
	spriteFont.DrawString(&spriteBatch, std::to_string(highscore->GetNewScore()).c_str(), DirectX::XMFLOAT2(float(width) / 4 + (wordDistanceHorizontal * 2), float(height) / 4 + (wordDistanceVertical * 3) - 50), DirectX::Colors::Cyan, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f));
	spriteFont.DrawString(&spriteBatch, name[0].c_str(), DirectX::XMFLOAT2(float(width) / 4, float(height) / 4), DirectX::Colors::SpringGreen, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f));
	spriteFont.DrawString(&spriteBatch, name[1].c_str(), DirectX::XMFLOAT2(float(width) / 4, float(height) / 4+wordDistanceVertical), DirectX::Colors::SpringGreen, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f));
	spriteFont.DrawString(&spriteBatch, name[2].c_str(), DirectX::XMFLOAT2(float(width) / 4, float(height) / 4 + (wordDistanceVertical * 2)), DirectX::Colors::SpringGreen, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f));
	spriteFont.DrawString(&spriteBatch, std::to_string(score[0]).c_str(), DirectX::XMFLOAT2(float(width) / 4 + (wordDistanceHorizontal * 2), float(height) / 4), DirectX::Colors::SpringGreen, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f));
	spriteFont.DrawString(&spriteBatch, std::to_string(score[1]).c_str(), DirectX::XMFLOAT2(float(width) / 4 + (wordDistanceHorizontal * 2), float(height) / 4 + wordDistanceVertical), DirectX::Colors::SpringGreen, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f));
	spriteFont.DrawString(&spriteBatch, std::to_string(score[2]).c_str(), DirectX::XMFLOAT2(float(width) / 4 + (wordDistanceHorizontal * 2), float(height) / 4 + (wordDistanceVertical * 2)), DirectX::Colors::SpringGreen, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f));

	spriteBatch.End();
}

void HighscoreScreen::Reset()
{
	currentScreen = 4;
	Enter_KeyDown = false;
}


HighscoreScreen::~HighscoreScreen()
{

}

