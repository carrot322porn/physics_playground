#pragma once
#include "raylib.h"

class GravityPoint {
public:
    Vector2 position;
    float mass;
    float radius;
    Color color;

    GravityPoint(Vector2 pos, float m, Color col);
};
