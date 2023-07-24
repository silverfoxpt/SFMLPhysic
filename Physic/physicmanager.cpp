#include "physicmanager.h"

void PhysicManager::Initialize(sf::RenderWindow* window) {
    this->window = window;

    this->TestInitialize();
}

void PhysicManager::Update(sf::Event event) {
    for (auto& point: this->points) {
        point.Update(event);
    }
}

void PhysicManager::Visualize(sf::Event event) {
    for (auto& point: this->points) {
        point.Visualize(event);
    }
}

void PhysicManager::LateUpdate() {

}

void PhysicManager::Reset() {
    this->points.clear();
    this->constraints.clear();
}

void PhysicManager::TestInitialize() {
    PhysicPoint point = PhysicPoint(1, GameManager::convertWorldToScreen(sf::Vector2f(400, 400)), 0.01);
    point.Initialize(this->window);

    this->points.push_back(point);
}