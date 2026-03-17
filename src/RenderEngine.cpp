#include "raylib.h"
#include "RenderEngine.h"
#include "Timer.h"

float RenderEngine::getMass() {
    return currmass;
}

Color RenderEngine::getColor() {
    return currcolor;
}

void RenderEngine::changeMass(float delta) {
    currmass += delta;
    if (currmass < 50.0f) currmass = 50.0f;
    tim = true;
    timer.reset();
}

void RenderEngine::showTimeX() {
    showTimeXLabel = true;
    timeXTimer.reset();
}

void RenderEngine::drawWorld(PhysicsEngine& physics) {
    const auto& b = physics.bodies;
    const auto& g = physics.gravityPoints;

    for (int i = 0; i < b.size(); i++) {
        DrawCircleV(b[i].position, b[i].radius, b[i].color);
    }
    for (int i = 0; i < g.size(); i++) {
        DrawCircleV(g[i].position, g[i].radius, g[i].color);
    }
}

void RenderEngine::drawUI(PhysicsEngine& physics, float dt) {
    if (showTimeXLabel) {
        if (!timeXTimer.update(dt)) {
            DrawText(TextFormat("TimeX = %.1f", physics.getTimeX()), 40, 40, 40, WHITE);
        }
        else {
            showTimeXLabel = false;
            timeXTimer.reset();
        }
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

    if (physics.timeIsStopped()) {
        DrawText("TIME IS STOPPED", 1920 / 2.7, 100.f, 50, WHITE);
    }
}

void RenderEngine::update(Camera2D& camera) {
    float wheel = GetMouseWheelMove();

    if (wheel != 0) {
        camera.zoom += wheel * 0.1f;
        if (camera.zoom < 0.1f) camera.zoom = 0.1f;
    }

    Vector2 delta = GetMouseDelta();
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
        camera.target.x -= delta.x / camera.zoom;
        camera.target.y -= delta.y / camera.zoom;
    }
}
