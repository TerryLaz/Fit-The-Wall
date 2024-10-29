#pragma once
#include<Windows.h>
#include<iostream>

class WindowManager
{
private:
	UINT width;
	UINT height;
	HWND window;

public:
	WindowManager();
	~WindowManager();
	bool SetupWindow(HINSTANCE instance, int nCmdShow);
	UINT GetWidth();
	UINT GetHeight();
	HWND GetWindow();


};

