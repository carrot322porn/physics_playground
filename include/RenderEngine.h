#pragma once
#include "PhysicsEngine.h"
#include "Timer.h"
#include "raylib.h"

class RenderEngine {
private:
    Timer timer;
    bool tim = false;
    float currmass = 100.f;
    Color currcolor = WHITE;
public:
    float getMass();
    Color getColor();
    void drawWorld(PhysicsEngine& physics);
    void drawUI(PhysicsEngine& physics, float dt);
    void update(Camera2D& camera);
    void changeMass(float delta);
};
