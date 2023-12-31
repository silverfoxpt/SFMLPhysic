#include "physicpoint.h"

PhysicPoint::PhysicPoint(float mass, sf::Vector2f currentPosition, float timeStep, GameObject* parent) : Component(parent) {
    this->mass = mass;

    this->currentPosition = currentPosition;
    this->previousPosition = currentPosition;

    this->timeStep = timeStep; //for safety purpose, please for god sake don't remove this and fall into hell
    this->idx = -1;
}

void PhysicPoint::Initialize(sf::RenderWindow* window) {
    this->window = window;
}

void PhysicPoint::Update(sf::Event event) {
    if (!this->animationStatus == PhysicState::Static) {
        if (this->intergrationMethod == IntergrationMethod::Verlet) {
            auto tmp = this->currentPosition;
            this->currentPosition = Math::scaleVec(this->currentPosition, 2) - this->previousPosition + Math::scaleVec(this->acceleration, this->timeStep * this->timeStep); // Error O(dt^4)
            this->previousPosition = tmp;

            this->acceleration = sf::Vector2f(0, 0); //reset acceleration

            // Update the velocity
            this->velocity = (this->currentPosition - this->previousPosition) / this->timeStep; // Error O(dt^2)
        } else if (this->intergrationMethod == IntergrationMethod::Euler) {
            this->velocity += this->acceleration * this->timeStep;
            this->currentPosition += this->velocity * this->timeStep;

            //std::cout << velocity.x << " " << velocity.y << '\n';
        }

        if (this->parentObj != nullptr) {
            this->ModifyGameobject();
        }
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

void PhysicPoint::ModifyGameobject() {
    auto dir = this->velocity;

    //std::cout << dir.x << " " << dir.y << '\n';
    if (std::abs(dir.x) < 0.00001) {dir.x = 0;}
    if (std::abs(dir.y) < 0.00001) {dir.y = 0;}

    //std::cout << this->currentPosition.x << " " << this->currentPosition.y << '\n';

    this->parentObj->SetWorldPosition(this->currentPosition);
    this->parentObj->SetRotation(Math::angleBetweenVectors(Math::getUpVec(), dir));
}