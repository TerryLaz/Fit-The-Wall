#include "WindowManager.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		//destroys window if exited
		break;
	}

	//run default if window not exited
	return DefWindowProc(hWnd, message, wParam, lParam);
}

WindowManager::WindowManager()
{
	width = 1920;
	height = 1080;
}

WindowManager::~WindowManager()
{
}

bool WindowManager::SetupWindow(HINSTANCE instance, int nCmdShow)
{
	//create window by assigning nessesary windows info.
	const wchar_t CLASS_NAME[] = L"WindowManager";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = instance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	//create a pop-up/child of the window defined abowe, inputs are design choices, visable text on pop-up window etc.
	window = CreateWindowEx(0, CLASS_NAME, L"Fit The Wall", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, width, height, nullptr, nullptr, instance, nullptr);
	
	//check if window contains nessesary values, else print assigned error message
	if (window==nullptr)
	{
		std::cerr << "HWND was nullptr, last error: " << GetLastError() << std::endl;
		return false;
	}

	//show window to the user, inserts are our window diffined above and flag containing main application about window size (maximaze, minimaze or normal)
	ShowWindow(window, nCmdShow);

	return true;
}

UINT WindowManager::GetWidth()
{
	return width;
}
UINT WindowManager::GetHeight()
{
	return height;
}
HWND WindowManager::GetWindow()
{
	return window;
}