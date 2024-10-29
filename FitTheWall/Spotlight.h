#pragma once
#include "GameObject.h"
class Spotlight :
    public GameObject
{
private:
    GraphicsManager* graphicsManager;

    float rotationSpeed[3];
    float rotSeconds[9];
    float stopTimer[9];
    bool reachedBoundary[9];
    float randomStopTime[9];

public:
    Spotlight(GraphicsManager* graphicsManager);

    void Update();
    void RotateSpotlight(int meshIndex, XMFLOAT3 rotSpeedXYZ, float rotTimeX, float rotTimeY, float rotTimeZ);
};

