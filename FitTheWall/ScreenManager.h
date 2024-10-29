#include "GraphicsManager.h"
#include "GameOver.h"
#include"Highscore.h"
#include"PlayerInput.h"
#include "MainMenu.h"
#include "GameGui.h"
#include "Camera.h"
#include "GameManager.h"
#include"Light.h"
#include"HighscoreScreen.h"
#include "GuideScreen.h"
#include "MyMouse.h"

class ScreenManager
{
private:
	GraphicsManager* graphicsManager;
	Camera camera;//nej
	GameOver gameOver;//nej
	Highscore highscore;//nej
	PlayerInput playerInput;//nej
	MainMenu mainMenu;//nej
	GameManager game; //2 läckor
	HighscoreScreen highscoreScreen;//nej
	Guide guideScreen;
	WindowManager* winman;

	int currentScreen;
	bool scoreCompaired;
	bool menuExists;
	bool gameExists;
	bool spaceButtonPressed;

public:
	ScreenManager(GraphicsManager* graphicsManager, UINT width, UINT height,WindowManager* winman);
	~ScreenManager();

	void Update();
	void Render();
	int GetCurrenScreen();

};
