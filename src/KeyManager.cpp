#include "KeyManager.h"
#include "raylib.h"
#include "Body.h"
#include "GravityPoint.h"

void KeyManager::update(class PhysicsEngine& physics, class RenderEngine& render) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        switch (mode) {
            case Mode::spawn:
                physics.addBody(Body(GetMousePosition(), render.getMass(), render.getColor()));
                break;
            case Mode::drag:
                physics.dragging = true;
                break;
        }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        physics.dragging = false;
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
