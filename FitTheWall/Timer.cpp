#include "Timer.h"

Timer::Timer()
{
	elapsedSeconds = 0;
}

Timer::~Timer()
{
}

int Timer::GetElapsedTime()
{
	return elapsedSeconds;
}

float Timer::GetElapsedMS()
{
	return elapsedMilliseconds;
}

std::string Timer::getTime()
{
	return time;
}

void Timer::Start()
{
	start = std::chrono::steady_clock::now();
}

void Timer::Stop()
{
	end = std::chrono::steady_clock::now();
}

void Timer::Update()
{
	elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count();
	elapsedMilliseconds = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count()) - elapsedSeconds * 1000;
	time = std::to_string(elapsedSeconds) + "." + std::to_string(elapsedMilliseconds);
}

void Timer::Render(DirectX::SpriteBatch& spriteBatch, DirectX::SpriteFont& spriteFont)
{
	spriteFont.DrawString(&spriteBatch, time.c_str(), DirectX::XMFLOAT2(850, -50), DirectX::Colors::SpringGreen, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
}
