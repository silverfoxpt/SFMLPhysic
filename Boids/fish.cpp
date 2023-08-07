#include "fish.h"

void Fish::Initialize(sf::RenderWindow* window) {
    this->window = window;

    //create stuffs
    this->gameObject = GameobjectManager::GetInstance()->AddNewControlledComponent(GameObject(5, 10));
    this->gameObject->SetWorldPosition(sf::Vector2f(400, -400));
    this->gameObject->SetColor(sf::Color::Red);

    this->physicPoint = PhysicManager::GetInstance()->AddNewControlledComponent(PhysicPoint(1, this->gameObject->GetWorldPosition(), PhysicManager::GetInstance()->timeStep, this->gameObject));
    this->physicPoint->animationStatus = PhysicState::Kinematic;
    this->physicPoint->intergrationMethod = IntergrationMethod::Euler; //test

    this->gameObject->AddComponent(this->physicPoint);
}

void Fish::Update(sf::Event event) {
    //test
    //
}

void Fish::Visualize(sf::Event event) {

}

void Fish::LateUpdate() {

}

void Fish::Reset() {

}