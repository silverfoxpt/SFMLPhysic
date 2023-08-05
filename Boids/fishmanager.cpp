#include "fishmanager.h"

void FishManager::Initialize(sf::RenderWindow* window) {
    this->window = window;
    this->SpawnFish();
}

void FishManager::Update(sf::Event event) {
    this->Seperation();
}

void FishManager::Visualize(sf::Event event) {

}

void FishManager::LateUpdate() {

}

void FishManager::Reset() {
    this->fishes.clear();
}

void FishManager::SpawnFish() {
    for (int i = 0; i < this->numFish; i++) {
        Fish newFish = Fish();
        newFish.Initialize(this->window);

        this->fishes.push_back(newFish);
    }
}

void FishManager::Seperation() {
    for (auto& fish: this->fishes) {
        
    }
}