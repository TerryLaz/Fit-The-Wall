#pragma once
#include "GameObject.h"

struct WallConfiguration
{
    int correctPose;
    int correctPosition;
    const char* filename;
};

class Wall :
    public GameObject
{
private:
    float speed;
    bool isDown;
    bool goingDown;
    WallConfiguration config;
    const int score = 100;

public:
    Wall(GraphicsManager* graphicsManager);
    Wall(GraphicsManager* graphicsManager, int type);
    Wall(GraphicsManager* graphicsManager, int type, float speed);
    ~Wall();

    void ConfigureWall(int type);

    void Update();
    int GetCorrectPosition();
    int GetCorrectPose();
    int GetScore();
};

