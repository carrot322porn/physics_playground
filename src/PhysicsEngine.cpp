#include "raylib.h"
#include "PhysicsEngine.h"
#include <cmath>

PhysicsEngine::PhysicsEngine() {
    Gconst = 100.f;
    timeX = 1.f;
}

void PhysicsEngine::addBody(Body body) {
    bodies.push_back(body);
}

void PhysicsEngine::addGravityPoint(GravityPoint point) {
    gravityPoints.push_back(point);
}

void PhysicsEngine::update(float dt) {
    if (dragging) {
        mousePositions.push_back(GetMousePosition());
        if (mousePositions.size() > 7) mousePositions.erase(mousePositions.begin());

        if (!bodies.empty()) drag(bodies[index]);
    }

    if (timeIsStopped()) return;

    for (int i = 0; i < bodies.size(); i++) {
        Vector2 force = {0.0, 0.0};
        //bodies
        for (int j = 0; j < bodies.size(); j++) {
            if (i == j) continue;

            double dx = bodies[j].position.x - bodies[i].position.x;
            double dy = bodies[j].position.y - bodies[i].position.y;

            double distSq = dx*dx + dy*dy;
            if (distSq < 25.0) distSq = 25.0;

            double dist = sqrt(distSq);
            double F = Gconst * bodies[i].mass * bodies[j].mass / distSq;

            force.x += (dx / dist) * F;
            force.y += (dy / dist) * F;
        }
        //gravity points
        for (int j = 0; j < gravityPoints.size(); j++) {
            double dx = gravityPoints[j].position.x - bodies[i].position.x;
            double dy = gravityPoints[j].position.y - bodies[i].position.y;

            double distSq = dx*dx + dy*dy;
            if (distSq < 25.0) distSq = 25.0;

            double dist = sqrt(distSq);
            double F = Gconst * bodies[i].mass * gravityPoints[j].mass / distSq;

            force.x += (dx / dist) * F;
            force.y += (dy / dist) * F;
        }

        bodies[i].applyForce(force, timeX, dt);
        bodies[i].update(dt);
    }
}

void PhysicsEngine::timeStop() {
    static float lastTime = timeX;
    if (timeX != 0.f) {
        lastTime = timeX;
        timeX = 0.f;
    }
    else timeX = lastTime;
}

void PhysicsEngine::reset() {
    bodies.clear();
    gravityPoints.clear();
    lastVelocity.clear();
    timeX = 1.f;
    Gconst = 100.f;
}

void PhysicsEngine::drag(Body& body) {
    body.position = GetMousePosition();
    body.velocity.x = (mousePositions.back().x - mousePositions.front().x) * 3;
    body.velocity.y = (mousePositions.back().y - mousePositions.front().y) * 3;
}


bool PhysicsEngine::timeIsStopped() {
    if (timeX == 0.f) return true;
    else return false;
}

int PhysicsEngine::mouseOverBodyIndex() {
    for (int i = 0; i < bodies.size(); i++) {
        double dx = GetMousePosition().x - bodies[i].position.x;
        double dy = GetMousePosition().y - bodies[i].position.y;

        double distSq = dx*dx + dy*dy;
        double radiusSq = bodies[i].radius * bodies[i].radius;

        if (distSq <= radiusSq) return i;
    }
    return -1;
}