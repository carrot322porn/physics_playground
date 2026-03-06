#include "KeyManager.h"
#include "raylib.h"
#include "Body.h"
#include "GravityPoint.h"

void KeyManager::update(PhysicsEngine& physics, RenderEngine& render, const Camera2D& camera) {
    static bool pressed = false;
    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        switch (mode) {
            case Mode::spawn:
                if (!pressed) {
                    physics.addBody(Body(mouseWorld, render.getMass(), render.getColor()));
                    pressed = true;
                }
                break;
            case Mode::drag: {
                int idx = physics.mouseOverBodyIndex(camera);
                if (idx != -1) {
                    if (!physics.dragging) physics.index = idx;
                    physics.dragging = true;
                }
                break;
            }
        }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        physics.dragging = false;
        pressed = false;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        physics.addGravityPoint(GravityPoint(mouseWorld, render.getMass(), RED));
    }
    if (IsKeyPressed(KEY_M)) switchMode();
    if (IsKeyPressed(KEY_SPACE)) physics.timeStop();
    if (IsKeyPressed(KEY_R)) physics.reset();

    const float massStep = 50.0f;
    if (IsKeyPressed(KEY_EQUAL) || IsKeyPressed(KEY_KP_ADD)) {
        render.changeMass(massStep);
    }
    if (IsKeyPressed(KEY_MINUS) || IsKeyPressed(KEY_KP_SUBTRACT)) {
        render.changeMass(-massStep);
    }

    const float timeStep = 0.25f;
    if (IsKeyPressed(KEY_PERIOD)) {
        physics.changeTimeX(timeStep);
        render.showTimeX();
    }
    if (IsKeyPressed(KEY_COMMA)) {
        physics.changeTimeX(-timeStep);
        render.showTimeX();
    }
}

void KeyManager::switchMode() {
    switch (mode) {
        case Mode::spawn:
            mode = Mode::drag; break;
        case Mode::drag:
            mode = Mode::spawn; break;
    }
}
