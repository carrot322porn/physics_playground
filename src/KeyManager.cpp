#include "KeyManager.h"
#include "raylib.h"
#include "Body.h"
#include "GravityPoint.h"

void KeyManager::update(PhysicsEngine& physics, RenderEngine& render) {
    static bool pressed = false;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        switch (mode) {
            case Mode::spawn:
                if (!pressed) {
                    physics.addBody(Body(GetMousePosition(), render.getMass(), render.getColor()));
                    pressed = true;
                }
                break;
            case Mode::drag:
                int idx = physics.mouseOverBodyIndex();
                if (idx != -1) {
                    if (!physics.dragging) physics.index = idx;
                    physics.dragging = true;
                }
                break;
        }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        physics.dragging = false;
        pressed = false;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) physics.addGravityPoint(GravityPoint(GetMousePosition(), render.getMass(), RED));
    if (IsKeyPressed(KEY_M)) switchMode();
    if (IsKeyPressed(KEY_SPACE)) physics.timeStop();
    if (IsKeyPressed(KEY_R)) physics.reset();
}

void KeyManager::switchMode() {
    switch (mode) {
        case Mode::spawn:
            mode = Mode::drag; break;
        case Mode::drag:
            mode = Mode::spawn; break;
    }
}
