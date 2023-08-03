#include "fish.h"

void Fish::Initialize(sf::RenderWindow* window, GameobjectManager* gameobjectManager, PhysicManager* physicManager) {
    this->window = window;
    this->gameobjectManager = gameobjectManager;
    this->physicManager = physicManager;

    //create stuffs
    this->physicPoint = physicManager->CreatePoint(PhysicPoint());
}

void Fish::Update(sf::Event event) {
}

void Fish::Visualize(sf::Event event) {

}

void Fish::LateUpdate() {

}

void Fish::Reset() {

}