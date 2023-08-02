#include "gameobjectmanager.h"

void GameobjectManager::Initialize(sf::RenderWindow* window) {
    this->window = window;
    this->controlledObjects.reserve(100000);
}

void GameobjectManager::Update(sf::Event event) {
    for (auto& obj: this->controlledObjects) {
        obj.Update(event);
    }
}

void GameobjectManager::Visualize(sf::Event event) {
    for (auto& obj: this->controlledObjects) {
        obj.Visualize(event);
    }
}

void GameobjectManager::LateUpdate() {
    for (auto& obj: this->controlledObjects) {
        obj.LateUpdate();
    }
}

void GameobjectManager::Reset() {
    for (auto& obj: this->controlledObjects) {
        obj.Reset();
    }
}

GameObject* GameobjectManager::GetControlledObject(int idx) {
    if (idx < 0 || idx > (int) this->controlledObjects.size()) {return nullptr;}
    return &this->controlledObjects[idx];
}

GameObject* GameobjectManager::AddNewControlledObject(GameObject obj) { 
    int idx = this->controlledObjects.size();
    this->controlledObjects.push_back(obj);

    return this->GetControlledObject(idx);
}