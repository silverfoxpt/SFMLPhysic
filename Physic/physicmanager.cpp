#include "physicmanager.h"

void PhysicManager::Initialize(sf::RenderWindow* window) {
    this->window = window;

    this->TestInitialize();
}

void PhysicManager::Update(sf::Event event) {
    this->TestUpdate();
    this->AddForceByInput(event);
    this->AddForceGravity();
    this->AddForceAirResistance();

    for (auto& point: this->points) {
        point.Update(event);
    }

    for (int i = 0; i < this->substep; i++) {
        for (auto& constraint: this->constraints) {
            constraint.Update(event);
        }

        for (auto& spring: this->springs) {
            spring.Update(event);
        }
    }
}

void PhysicManager::Visualize(sf::Event event) {
    for (auto& point: this->points) {
        point.Visualize(event);
    }

    for (auto& constraint: this->constraints) {
        constraint.Visualize(event);
    }

    for (auto& spring: this->springs) {
        spring.Visualize(event);
    }
}

void PhysicManager::LateUpdate() {

}

void PhysicManager::Reset() {
    this->points.clear();
    this->constraints.clear();
}

void PhysicManager::TestInitialize() {
    PhysicPoint p1 = PhysicPoint(1, GameManager::convertScreenToWorld(sf::Vector2f(400, 400)), this->timeStep);
    p1.Initialize(this->window); 
    p1.isStatic = true;
    this->points.push_back(p1);

    PhysicPoint p2 = PhysicPoint(1, GameManager::convertScreenToWorld(sf::Vector2f(400, 450)), this->timeStep);
    p2.Initialize(this->window); 
    this->points.push_back(p2);

    PhysicPoint p3 = PhysicPoint(1, GameManager::convertScreenToWorld(sf::Vector2f(400, 500)), this->timeStep);
    p3.Initialize(this->window); 
    this->points.push_back(p3);

    PhysicPoint p4 = PhysicPoint(2, GameManager::convertScreenToWorld(sf::Vector2f(400, 510)), this->timeStep);
    p4.Initialize(this->window); 
    this->points.push_back(p4);

    /*AbsoluteConstraint constraint(this->getPoint(0), this->getPoint(1), 50);
    constraint.Initialize(this->window);
    this->constraints.push_back(constraint);*/

    /*AbsoluteConstraint constraint2(this->getPoint(1), this->getPoint(2), 50);
    constraint2.Initialize(this->window);
    this->constraints.push_back(constraint2);

    AbsoluteConstraint cosntraint3(this->getPoint(1), this->getPoint(3), 60);
    cosntraint3.Initialize(this->window);
    this->constraints.push_back(cosntraint3);*/

    SpringConstraint spring(this->getPoint(0), this->getPoint(1), 70, 0.02);
    spring.Initialize(this->window);
    this->springs.push_back(spring);

    SpringConstraint spring2(this->getPoint(1), this->getPoint(2), 70, 0.02);
    spring2.Initialize(this->window);
    this->springs.push_back(spring2);
}

void PhysicManager::TestUpdate() {
    
}

void PhysicManager::AddForceAirResistance() {
    for (auto& point: this->points) {
        float len = Math::Length(point.velocity);
        auto p = Math::scaleVec(Math::normalizeVec(point.velocity), -this->dampingCoefficient * len * len); //debug this tomorrow
        //point.AddForce();
    }
}

void PhysicManager::AddForceGravity() {
    for (auto& point: this->points) {
        point.AddForce(sf::Vector2f(0.0, -this->gravityCoefficient * point.mass));
    }
}

void PhysicManager::AddForceByInput(sf::Event event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        for (auto& point: this->points) {
            point.AddForce(sf::Vector2f(10, 0));
        }
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        for (auto& point: this->points) {
            point.AddForce(sf::Vector2f(-10, 0));
        }
    }
}