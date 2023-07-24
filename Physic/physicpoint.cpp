#include "physicpoint.h"

PhysicPoint::PhysicPoint(float mass, sf::Vector2f currentPosition, float timeStep) {
    this->mass = mass;
    this->currentPosition = currentPosition;
    this->previousPosition = currentPosition;
    this->timeStep = timeStep;
}

void PhysicPoint::Initialize(sf::RenderWindow* window) {
    this->window = window;
}

void PhysicPoint::Update(sf::Event event) {
    if (!this->isStatic) {
        auto tmp = this->currentPosition;
        this->currentPosition =  Math::scaleVec(this->currentPosition, 2) - this->previousPosition + Math::scaleVec(this->acceleration, this->timeStep);
        this->previousPosition = tmp;
    }
}

void PhysicPoint::Visualize(sf::Event event) {
    DrawUtils::drawCircle(this->window, GameManager::convertWorldToScreen(this->currentPosition), 5, sf::Color::Red);
}

void PhysicPoint::LateUpdate() {

}

void PhysicPoint::Reset() {

}

void PhysicPoint::AddForce(sf::Vector2f force) {
    this->acceleration += force / this->mass; //F = ma
}