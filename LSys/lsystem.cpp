#include "lsystem.h"

void LSystem::Initialize(sf::RenderWindow* window) {
    this->window = window;

    this->pos           = this->start;
    this->instruction   = this->startInstruction;
    this->dir           = Math::getUpVec();
}

void LSystem::Update(sf::Event event) {
    this->CreateTree();
}

void LSystem::Visualize(sf::Event event) {
    
}

void LSystem::LateUpdate() {

}

void LSystem::Reset() {
    while(!mem.empty()) {mem.pop();}
    //this->updateMap.clear();
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
        cur = "";
    }

    //std::cout << this->instruction;

    //generate tree
    for (int i = 0; i < (int) this->instruction.size(); i++) {
        char c = this->instruction[i];

        if (c == 'F') {
            DrawUtils::drawLine(this->window, GameManager::convertWorldToScreen(this->pos), GameManager::convertWorldToScreen(this->pos + this->dir * this->lineLength),
                this->color, this->lineSize);
            this->pos = this->pos + this->dir * this->lineLength;
        } else if (c == '-') {
            this->dir = Math::spinPoint(this->dir, sf::Vector2f(0, 0), this->angle);
        } else if (c == '+') {
            this->dir = Math::spinPoint(this->dir, sf::Vector2f(0, 0), -this->angle);
        } else if (c == '[') {
            this->mem.push(std::make_pair(this->pos, this->dir));
        } else if (c == ']') {
            auto p = this->mem.top(); this->mem.pop();
            this->pos = p.first;
            this->dir = p.second;
        }
    }

    this->Initialize(this->window);
}