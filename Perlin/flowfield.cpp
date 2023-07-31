#include "flowfield.h"

void Flowfield::Initialize(sf::RenderWindow* window) {
    this->window = window;
    this->noise = PerlinNoise();

    //calculate field size
    this->row = GameManager::mainWindowSize.y / this->cellSize;
    this->col = GameManager::mainWindowSize.x / this->cellSize; 

    //calculate field values
}

void Flowfield::Update(sf::Event event) {
}

void Flowfield::Visualize(sf::Event event) {

}

void Flowfield::LateUpdate() {

}

void Flowfield::Reset() {
    this->angleValues.clear();
    
    this->noise = PerlinNoise();
}