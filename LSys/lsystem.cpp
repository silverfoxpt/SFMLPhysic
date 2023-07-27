#include "lsystem.h"

void LSystem::Initialize(sf::RenderWindow* window) {
    this->window = window;

    this->CreateTree();
}

void LSystem::Update(sf::Event event) {
    
}

void LSystem::Visualize(sf::Event event) {

}

void LSystem::LateUpdate() {

}

void LSystem::Reset() {
    while(!mem.empty()) {mem.pop();}
    this->updateMap.clear();
}

void LSystem::CreateTree() {
    //create instructions
    std::string cur = "";
    for (int i = 0; i < this->numIter; i++) {
        for (int j = 0; j < (int) this->instruction.size(); j++) {
            char c = this->instruction[j];
            if (this->updateMap.find(c) != this->updateMap.end()) {
                cur += this->updateMap[c];
            } else {
                cur += c;
            }
        }
        this->instruction = cur;
    }

    //generate tree
}