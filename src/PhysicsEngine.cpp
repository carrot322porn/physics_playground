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
    // ================= DRAG =================
    if (dragging) {
        mousePositions.push_back(GetMousePosition());
        if (mousePositions.size() > 7) mousePositions.erase(mousePositions.begin());

        if (index >= 0 && index < bodies.size()) drag(bodies[index]);
        else dragging = false;
    }

    if (timeIsStopped()) return;

    // ================= MERGE =================
    for (int i = 0; i < bodies.size(); i++) {
        for (int j = i + 1; j < bodies.size(); j++) {

            Vector2 d = {
                bodies[j].position.x - bodies[i].position.x,
                bodies[j].position.y - bodies[i].position.y
            };

            float distSq = d.x*d.x + d.y*d.y;
            float r = bodies[i].radius + bodies[j].radius;

            if (distSq <= r*r) {
                Body& a = bodies[i];
                Body& b = bodies[j];

                float newMass = a.mass + b.mass;

                Vector2 newVel = {
                    (a.velocity.x * a.mass + b.velocity.x * b.mass) / newMass,
                    (a.velocity.y * a.mass + b.velocity.y * b.mass) / newMass
                };

                Vector2 newPos = {
                    (a.position.x * a.mass + b.position.x * b.mass) / newMass,
                    (a.position.y * a.mass + b.position.y * b.mass) / newMass
                };

                a.mass = newMass;
                a.velocity = newVel;
                a.position = newPos;
                a.radius = sqrt(newMass);

                bodies.erase(bodies.begin() + j);
                j--;
            }
        }
    }

    // ================= GRAVITY =================
    for (int i = 0; i < bodies.size(); i++) {
        Vector2 force = {0.f, 0.f};

        for (int j = 0; j < bodies.size(); j++) {
            if (i == j) continue;

            Vector2 d = {
                bodies[j].position.x - bodies[i].position.x,
                bodies[j].position.y - bodies[i].position.y
            };

            float distSq = d.x*d.x + d.y*d.y;
            if (distSq < 25.0f) distSq = 25.0f;

            float dist = sqrt(distSq);
            float F = Gconst * bodies[i].mass * bodies[j].mass / distSq;

            force.x += (d.x / dist) * F;
            force.y += (d.y / dist) * F;
        }

        for (int j = 0; j < gravityPoints.size(); j++) {
            float dx = gravityPoints[j].position.x - bodies[i].position.x;
            float dy = gravityPoints[j].position.y - bodies[i].position.y;

            float distSq = dx*dx + dy*dy;
            if (distSq < 25.0f) distSq = 25.0f;

            float dist = sqrt(distSq);
            float F = Gconst * bodies[i].mass * gravityPoints[j].mass / distSq;

            force.x += (dx / dist) * F;
            force.y += (dy / dist) * F;
        }

        bodies[i].applyForce(force, timeX, dt);
    }

    // ================= INTEGRATION =================
    for (int i = 0; i < bodies.size(); i++) {
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