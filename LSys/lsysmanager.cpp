#include "lsysmanager.h"

LSystemManager* LSystemManager::instance = nullptr;

void LSystemManager::Initialize(sf::RenderWindow* window, PhysicManager* physicManager, Flowfield* flowfield) {
    this->window = window;
    this->physicManager = physicManager;
    this->flowfield = flowfield;

    //add trees
    this->TestAddLSystems();
}

void LSystemManager::Update(sf::Event event) {
    for (auto &sys : this->lsystems) {
        sys.Update(event);
    }
}

void LSystemManager::Visualize(sf::Event event) {

}

void LSystemManager::LateUpdate() {

}

void LSystemManager::Reset() {

}

void LSystemManager::TestAddLSystems() {
    LSystem test1(6, "X", {{'X', "F+[[X]-X]-F[-FX]+X"}, {'F', "FF"}}, 25, sf::Vector2f(300, -800), sf::Color::Green, 3);
    test1.Initialize(this->window, this->physicManager, this->flowfield);
    this->lsystems.push_back(test1);

    LSystem test2(5, "X", {{'X', "F+[[X]-X]-F[-FX]+X"}, {'F', "FF"}}, 25, sf::Vector2f(500, -800), sf::Color::Yellow, 3);
    test2.Initialize(this->window, this->physicManager, this->flowfield);
    this->lsystems.push_back(test2);
}