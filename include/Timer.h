#pragma once

class Timer {
public:
    float time = 0.0f;
    float limit = 1.3f;
    bool repeat = false;

    bool update(float dt) {
        time += dt;
        if (time >= limit) {
            if (repeat) time = 0.0f;
            return true;
        }
        return false;
    }

    void reset() {
        time = 0.0f;
    }
};