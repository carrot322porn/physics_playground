#include "raylib.h"
#include "RenderEngine.h"
#include "Timer.h"

float RenderEngine::getMass() {
    return currmass;
}

Color RenderEngine::getColor() {
    return currcolor;
}

void RenderEngine::draw(PhysicsEngine& physics, float dt) {
    std::vector<Body> b = physics.bodies;
    std::vector<GravityPoint> g = physics.gravityPoints;

    for (int i = 0; i < b.size(); i++) {
        DrawCircleV(b[i].position, b[i].radius, b[i].color);
    }
    for (int i = 0; i < g.size(); i++) {
        DrawCircleV(g[i].position, g[i].radius, g[i].color);
    }

    if (tim) {
        if (!timer.update(dt)) {
            DrawText(TextFormat("Mass = %.0f", currmass), 1920 / 2.5, 900.f, 50, WHITE);
        }
        else {
            tim = false;
            timer.reset();
        }
    }

    if (physics.timeIsStopped()) DrawText("TIME IS STOPPED", 1920 / 2.7, 100.f, 50, WHITE);
}

void RenderEngine::update() {
    float wheel = GetMouseWheelMove();

    if (wheel > 0) {
        currmass += wheel * 10;
        tim = true;
        timer.reset();
    }

    if (wheel < 0) {
        if (currmass > 10.f) {
            currmass -= -wheel * 10;
            tim = true;
            timer.reset();
        }
    }
}
