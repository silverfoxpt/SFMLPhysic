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
        this->currentPosition = Math::scaleVec(this->currentPosition, 2) - this->previousPosition + Math::scaleVec(this->acceleration, this->timeStep * this->timeStep);
        this->previousPosition = tmp;

        this->acceleration = sf::Vector2f(0, 0); //reset acceleration

        // Update the velocity
        this->velocity = (this->currentPosition - this->previousPosition) / this->timeStep;
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
    this->acceleration  += Math::scaleVec(force, 1.0 / this->mass); //F = ma
    this->force         += force;
}