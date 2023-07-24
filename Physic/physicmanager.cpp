#include "physicmanager.h"

void PhysicManager::Initialize(sf::RenderWindow* window) {
    this->window = window;

    this->TestInitialize();
}

void PhysicManager::Update(sf::Event event) {
    this->TestUpdate();

    for (auto& point: this->points) {
        point.Update(event);
    }

    for (auto& constraint: this->constraints) {
        constraint.Update(event);
    }
}

void PhysicManager::Visualize(sf::Event event) {
    for (auto& point: this->points) {
        point.Visualize(event);
    }

    for (auto& constraint: this->constraints) {
        constraint.Visualize(event);
    }
}

void PhysicManager::LateUpdate() {

}

void PhysicManager::Reset() {
    this->points.clear();
    this->constraints.clear();
}

void PhysicManager::TestInitialize() {
    PhysicPoint p1 = PhysicPoint(1, GameManager::convertScreenToWorld(sf::Vector2f(400, 400)), 0.01);
    p1.Initialize(this->window); 
    p1.isStatic = true;
    this->points.push_back(p1);

    PhysicPoint p2 = PhysicPoint(1, GameManager::convertScreenToWorld(sf::Vector2f(400, 450)), 0.01);
    p2.Initialize(this->window); 
    this->points.push_back(p2);

    AbsoluteConstraint constraint(this->getPoint(0), this->getPoint(1), 50);
    constraint.Initialize(this->window);
    this->constraints.push_back(constraint);
}

void PhysicManager::TestUpdate() {
    this->points[1].AddForce(sf::Vector2f(0.01, 0));
}