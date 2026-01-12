#include "Body.h"
#include "raylib.h"
#include <cmath>

void Body::applyForce(Vector2 force, float timeX, float dt) {
    velocity.x += (force.x / mass) * dt * timeX;
    velocity.y += (force.y / mass) * dt * timeX;
}

void Body::update(float dt) {
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

Body::Body(Vector2 pos, float m, Color col = WHITE) {
    position = pos;
    velocity = {0.f, 0.f};
    mass = m;
    radius = std::sqrt(m);
    color = col;
}




