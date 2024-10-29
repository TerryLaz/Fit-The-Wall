#pragma once
#include "GraphicsManager.h"
#include <chrono>
#include <string>

class Timer
{
private:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::string time;
	int elapsedSeconds;
	int elapsedMilliseconds;
public:
	Timer();
	~Timer();

	int GetElapsedTime();
	float GetElapsedMS();
	std::string getTime();

	void Start();
	void Stop();

	void Update();
	void Render(DirectX::SpriteBatch& spriteBatch, DirectX::SpriteFont& spriteFont);
};