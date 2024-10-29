#include <windows.h>
#include <chrono>
#include "WindowManager.h"
#include "GraphicsManager.h"
#include "ScreenManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);



	srand(static_cast<unsigned int>(time(0)));

	//Update Frequency Timer
	std::chrono::time_point<std::chrono::steady_clock> fpsTimer(std::chrono::steady_clock::now());
	std::chrono::duration<int32_t, std::ratio<1, 30>> FPS{};

	WindowManager* windowManager = new WindowManager();
	if (!windowManager->SetupWindow(hInstance, nCmdShow))
	{
		std::cerr << "failed to setup window!" << std::endl;
		return -1;
	} 

	GraphicsManager *graphicsManager = new GraphicsManager();

	if (!graphicsManager->SetupD3D11(windowManager->GetWidth(), windowManager->GetHeight(), windowManager->GetWindow()))
	{
		std::cerr << "failed to setup D3D11!" << std::endl;
		return -1;
	}

	ScreenManager screen = ScreenManager(graphicsManager, windowManager->GetWidth(), windowManager->GetHeight(),windowManager);

	// make window stay open until exited
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		//check if message is called and run it (to close window)
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		FPS = std::chrono::duration_cast<std::chrono::duration<int32_t, std::ratio<1, 30>>> (std::chrono::steady_clock::now() - fpsTimer);
		
		if (FPS.count() >= 1)
		{
			fpsTimer = std::chrono::steady_clock::now();
			
			//UPDATE LOGIC
			screen.Update();
			
			//RENDER LOGIC
			screen.Render();
		}
		if (screen.GetCurrenScreen() == 5)
		{
			msg.message = WM_QUIT;
		}

	}

	delete graphicsManager;
	delete windowManager;


}
