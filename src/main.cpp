#include "raylib.h"
#include "PhysicsEngine.h"
#include "RenderEngine.h"
#include "KeyManager.h"

int main() {
    InitWindow(1920, 1080, "Physics playground");
    SetTargetFPS(60);

    Camera2D camera;
    PhysicsEngine physics;
    RenderEngine render;
    KeyManager keys;

    camera.target = {0, 0};
    camera.offset = {1920 / 2.0f, 1080 / 2.0f};
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        render.update(camera);
        keys.update(physics, render, camera);

        physics.update(dt, camera);

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
        render.drawWorld(physics);
        EndMode2D();
        render.drawUI(physics, dt);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}