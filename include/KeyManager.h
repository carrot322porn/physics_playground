#pragma once
#include "PhysicsEngine.h"
#include "RenderEngine.h"

class KeyManager {
private:
    enum class Mode { spawn, drag };
    Mode mode = Mode::spawn;

    void switchMode();
public:
    void update(class PhysicsEngine& physics, class RenderEngine& render);
};