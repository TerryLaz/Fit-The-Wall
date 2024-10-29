#pragma once
#include "GameObject.h"

class GameGui : public GameObject
{
private:
	
public:
	GameGui(GraphicsManager* graphicsManager);
	GameGui(GraphicsManager* graphicsManager, const char* filename, XMFLOAT3 cameraPosition, XMFLOAT2 desiredScreenPosition);
	~GameGui();

	void Update(float speed, float startTime, float scale);
};

