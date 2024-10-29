#include "GuideScreen.h"

Guide::Guide(GraphicsManager* graphicsManager)
	:guide(graphicsManager)
{
	currentScreen = 6;
	buttonPressed = false;
	guide.LoadTexture("Images/howToPlay.png");
	guide.SetPosition(0, 2, -10);
	guide.SetRotation(XMConvertToRadians(11), 0, 0);
	guide.ScaleObject(15.1, 9.0, 0.0);
}

Guide::~Guide()
{

}

void Guide::Update()
{
	guide.Update();
	SetScreen();
}

void Guide::Render()
{
	guide.Render();
}

int Guide::changeScreen()
{
	return currentScreen;
}

void Guide::SetScreen()
{
	if (GetKeyState(VK_RETURN) < 0 && buttonPressed == false)
	{
		buttonPressed = true;
	}
	if (GetKeyState(VK_RETURN) > 0 && buttonPressed == true)
	{
		currentScreen = 0;
	}
}

void Guide::ResetGuide()
{
	currentScreen = 6;
	buttonPressed = false;
}
