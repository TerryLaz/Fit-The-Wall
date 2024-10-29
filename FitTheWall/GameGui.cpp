#include "GameGui.h"


GameGui::GameGui(GraphicsManager* graphicsManager):
	GameObject(graphicsManager)
{
	position = XMFLOAT3(1, 0, 5);
}

GameGui::GameGui(GraphicsManager* graphicsManager, const char* filename, XMFLOAT3 cameraPos, XMFLOAT2 screenPos):
	GameObject(graphicsManager, filename)
{
	position = XMFLOAT3(cameraPos.x + screenPos.x, cameraPos.y + screenPos.y, cameraPos.z + 6);
	
}

GameGui::~GameGui()
{
	
}

void GameGui::Update(float speed, float time, float scale)
{
	double sineWave = sin(time * speed);
	double sineWave2 = sin(time * speed* 1.6);

	XMFLOAT3 originalPos = position;
	position = XMFLOAT3(0, 0, 0);
	rotation.x = scale * sineWave - 0.25;
	rotation.z = (scale * 0.2) * sineWave2;
	position = originalPos;

	GameObject::Update();


}

