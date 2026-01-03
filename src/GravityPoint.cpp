#include "GravityPoint.h"
#include "raylib.h"
#include <cmath>

GravityPoint::GravityPoint(Vector2 pos, float m, Color col = RED) {
    position = pos;
    mass = m;
    radius = std::sqrt(m);
    color = col;
}
