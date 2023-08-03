#include "fish.h"

void Fish::Initialize(sf::RenderWindow* window) {
    this->window = window;

    //create stuffs
    this->gameObject = GameobjectManager::GetInstance()->AddNewControlledComponent(GameObject(10, 10));
    this->gameObject->SetWorldPosition(sf::Vector2f(400, -400));
    this->gameObject->SetColor(sf::Color::Red);

    this->physicPoint = PhysicManager::GetInstance()->AddNewControlledComponent(PhysicPoint(this->gameObject));
}

void Fish::Update(sf::Event event) {
}

void Fish::Visualize(sf::Event event) {

}

void Fish::LateUpdate() {

}

void Fish::Reset() {

}