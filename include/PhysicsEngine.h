#pragma once
#include "Body.h"
#include "GravityPoint.h"
#include <vector>

class PhysicsEngine {
private:
    double Gconst;
    std::vector<Vector2> lastVelocity;
    std::vector<Vector2> mousePositions;
    float timeX;

    void drag(Body& body);
public:
    bool dragging = false;
    int index = -1;

    std::vector<Body> bodies;
    std::vector<GravityPoint> gravityPoints;

    PhysicsEngine();

    void addBody(Body body);
    void addGravityPoint(GravityPoint gravityPoint);
    void update(float dt);
    void timeStop();
    void reset();
    int mouseOverBodyIndex();
    bool timeIsStopped();
};