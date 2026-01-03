#pragma once
#include "Body.h"
#include "GravityPoint.h"
#include <vector>

class PhysicsEngine {
private:
    double Gconst;
    std::vector<Vector2> lastVelocity;
    std::vector<Vector2> mousePositions;
    bool stop;

    bool mouseOverBody(const Body& body);
    void drag(Body& body);
public:
    bool dragging = false;

    std::vector<Body> bodies;
    std::vector<GravityPoint> gravityPoints;

    PhysicsEngine();

    void addBody(Body body);
    void addGravityPoint(GravityPoint gravityPoint);
    void update(float dt);
    void timeStop();
    void reset();
    bool timeIsStopped();
};