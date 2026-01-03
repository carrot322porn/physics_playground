#include "Body.h"
#include "raylib.h"
#include <cmath>

void Body::applyForce(Vector2 force, float dt) {
    velocity.x += (force.x / mass) * dt;
    velocity.y += (force.y / mass) * dt;
}

void Body::update(float dt) {
    Body::position.x += Body::velocity.x * dt;
    Body::position.y += Body::velocity.y * dt;
}

Body::Body(Vector2 pos, float m, Color col = WHITE) {
    Body::position = pos;
    Body::velocity = {0.f, 0.f};
    Body::mass = m;
    Body::radius = std::sqrt(m);
    Body::color = col;
}




