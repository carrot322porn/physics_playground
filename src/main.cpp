#include "raylib.h"
#include "PhysicsEngine.h"
#include "RenderEngine.h"
#include "KeyManager.h"

int main() {
    InitWindow(1920, 1080, "Physics playground");
    SetTargetFPS(60);

    PhysicsEngine physics;
    RenderEngine render;
    KeyManager keys;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        keys.update(physics, render);

        render.update();
        physics.update(dt);

        BeginDrawing();
        ClearBackground(BLACK);
        render.draw(physics, dt);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}