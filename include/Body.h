#pragma once
#include "raylib.h"

class Body {
public:
    Vector2 position;
    Vector2 velocity;
    float mass;
    float radius;
    Color color;

    Body(Vector2 pos, float m, Color col);
    void applyForce(Vector2 force, float dt);
    void update(float dt);
};