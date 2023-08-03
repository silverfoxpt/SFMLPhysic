#include "physicpoint.h"

PhysicPoint::PhysicPoint(float mass, sf::Vector2f currentPosition, float timeStep, GameObject* parent) : Component(parent) {
    this->mass = mass;

    this->currentPosition = currentPosition;
    this->previousPosition = currentPosition;

    this->timeStep = timeStep;
    this->idx = -1;
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
        //std::cout << velocity.x << " " << velocity.y << '\n';

        //euler intergration
        /*this->velocity += this->acceleration * timeStep;
        this->currentPosition += this->velocity * timeStep + (float) 0.5 * this->acceleration * timeStep * timeStep;*/

        /*auto tmp = this->currentPosition;
        this->currentPosition += Math::scaleVec((this->currentPosition - this->previousPosition), 0.995)  + Math::scaleVec(this->acceleration, this->timeStep * this->timeStep);
        this->previousPosition = tmp;
        this->acceleration = sf::Vector2f(0, 0); //reset acceleration*/

        /*auto newPos = this->currentPosition + this->velocity * this->timeStep + (float) 0.5 * this->acceleration * this->timeStep * this->timeStep;
        auto newVel = this->velocity + this->acceleration * this->timeStep;

        this->currentPosition = newPos;
        this->velocity = newVel;
        this->acceleration = sf::Vector2f(0, 0);

        /*auto halfVelo = this->velocity + (float) 0.5 * this->acceleration * timeStep;
        auto newPos = this->currentPosition + halfVelo * timeStep;
        this->currentPosition = newPos;

        this->velocity = halfVelo + (float) 0.5 * this->acceleration * timeStep;
        this->acceleration = sf::Vector2f(0, 0);*/
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