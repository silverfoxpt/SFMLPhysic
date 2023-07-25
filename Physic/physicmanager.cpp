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

    for (int i = 0; i < this->substep; i++) {
        for (auto& constraint: this->constraints) {
            constraint.Update(event);
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

    PhysicPoint p3 = PhysicPoint(1, GameManager::convertScreenToWorld(sf::Vector2f(400, 500)), 0.01);
    p3.Initialize(this->window); 
    this->points.push_back(p3);

    PhysicPoint p4 = PhysicPoint(2, GameManager::convertScreenToWorld(sf::Vector2f(400, 510)), 0.01);
    p4.Initialize(this->window); 
    this->points.push_back(p4);

    AbsoluteConstraint constraint(this->getPoint(0), this->getPoint(1), 50);
    constraint.Initialize(this->window);
    this->constraints.push_back(constraint);

    AbsoluteConstraint constraint2(this->getPoint(1), this->getPoint(2), 50);
    constraint2.Initialize(this->window);
    this->constraints.push_back(constraint2);

    AbsoluteConstraint cosntraint3(this->getPoint(1), this->getPoint(3), 60);
    cosntraint3.Initialize(this->window);
    this->constraints.push_back(cosntraint3);
}

void PhysicManager::TestUpdate() {
    this->points[2].AddForce(sf::Vector2f(0.01, 0));
    this->points[3].AddForce(sf::Vector2f(0.02, 0));
}