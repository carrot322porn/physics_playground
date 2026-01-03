#include "raylib.h"
#include "PhysicsEngine.h"
#include <cmath>

PhysicsEngine::PhysicsEngine() {
    Gconst = 100.f;
    stop = false;
}

void PhysicsEngine::addBody(Body body) {
    bodies.push_back(body);
}

void PhysicsEngine::addGravityPoint(GravityPoint point) {
    gravityPoints.push_back(point);
}

void PhysicsEngine::update(float dt) {
    if (dragging) {
        static int index = 0;

        mousePositions.push_back(GetMousePosition());
        if (mousePositions.size() > 7) mousePositions.erase(mousePositions.begin());

        for (int i = 0; i < bodies.size(); i++) {
            if (mouseOverBody(bodies[i])) {
                index = i;
                break;
            }
        }

        drag(bodies[index]);
    }

    if (stop) return;

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

        bodies[i].applyForce(force, dt);
        bodies[i].update(dt);
    }
}

void PhysicsEngine::timeStop() {
    if (!stop) stop = true;
    else stop = false;
}

void PhysicsEngine::reset() {
    bodies.clear();
    gravityPoints.clear();
    lastVelocity.clear();
    stop = false;
    Gconst = 100.f;
}

void PhysicsEngine::drag(Body& body) {
    body.position = GetMousePosition();
    body.velocity.x = (mousePositions.back().x - mousePositions.front().x) * 3;
    body.velocity.y = (mousePositions.back().y - mousePositions.front().y) * 3;
}


bool PhysicsEngine::timeIsStopped() {
    if (stop) return true;
    else return false;
}

bool PhysicsEngine::mouseOverBody(const Body& body) {
    double dx = GetMousePosition().x - body.position.x;
    double dy = GetMousePosition().y - body.position.y;

    double distSq = dx*dx + dy*dy;
    double radiusSq = body.radius * body.radius;

    if (distSq <= radiusSq) return true;
    else return false;
}