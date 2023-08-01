#include "flowfield.h"

void Flowfield::Initialize(sf::RenderWindow* window) {
    this->window = window;

    this->noise = PerlinNoise();
    this->clock.restart();

    //calculate field size
    this->row = GameManager::mainWindowSize.y / this->cellSize;
    this->col = GameManager::mainWindowSize.x / this->cellSize; 

    //calculate field values
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            //calculate angle
            float angle = this->noise.noise(i * 0.02, j * 0.02);
            angle += 1; //range from 0 -> 2
            angle *= 180; //range from 0 -> 360

            //save angle
            this->angleValues.push_back(std::vector<float>());
            this->angleValues[i].push_back(angle);
        }
    }
}

void Flowfield::Update(sf::Event event) {
}

void Flowfield::Visualize(sf::Event event) {
    //this->visualizeFlowField();
}

void Flowfield::LateUpdate() {

}

void Flowfield::Reset() {
    this->angleValues.clear();

    this->noise = PerlinNoise();
    this->clock.restart();
}

void Flowfield::visualizeFlowField() {
    //draw flowfield
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            //calculate angle
            float angle = this->angleValues[i][j];

            //calculate dir vec
            sf::Vector2f dir = Math::spinPoint(Math::getUpVec(), sf::Vector2f(0, 0), angle);

            //calculate strength
            float strength = (noise.noise1D(this->clock.getElapsedTime().asSeconds() * 0.5) + 1) / 2 * (this->cellSize / 2.0f);

            sf::Vector2f startPoint 
                = sf::Vector2f(j * this->cellSize + cellSize / 2.0f, i * this->cellSize + cellSize / 2.0f) + 
                  (-dir * (cellSize / 2.0f)); //first corner
            sf::Vector2f endPoint 
                = startPoint + dir * strength * 2.0f; //other corner

            //draw line
            DrawUtils::drawLine(this->window, startPoint, endPoint, sf::Color::White, 1);
        }
    }
}

sf::Vector2f Flowfield::getForceFromPos(float x, float y) {
    sf::Vector2f screenPos = GameManager::convertWorldToScreen(sf::Vector2f(x, y));

    int row = screenPos.y / this->cellSize;
    int col = screenPos.x / this->cellSize;
    if (row < 0 || col < 0 || row >= this->row || col >= this->col) {
        //std::cout << "Nani?" << '\n';
        return sf::Vector2f(0, 0);
    }
    
    auto angle = this->angleValues[row][col];

    //calculate dir vec
    sf::Vector2f dir = Math::spinPoint(Math::getUpVec(), sf::Vector2f(0, 0), angle);

    //calculate strength
    float strength = (noise.noise1D(this->clock.getElapsedTime().asSeconds() * 0.5) + 1) / 2; // rane from 0 -> 1
    return dir * strength;
}