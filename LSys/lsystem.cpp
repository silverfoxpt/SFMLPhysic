#include "lsystem.h"

void LSystem::Initialize(sf::RenderWindow* window, PhysicManager* physicManager) {
    this->window = window;
    this->manager = physicManager;

    this->pos           = this->startPos;
    this->instruction   = this->startInstruction;
    this->dir           = Math::getUpVec();

    this->CreateTree();
    this->CreatePhysicTree();
}

void LSystem::Update(sf::Event event) {

}

void LSystem::Visualize(sf::Event event) {
    //this->DrawTree();
}

void LSystem::LateUpdate() {

}

void LSystem::Reset() {
    while(!mem.empty()) {mem.pop();}
    this->lines.clear();
    
    this->pos           = this->startPos;
    this->instruction   = this->startInstruction;
    this->dir           = Math::getUpVec();
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

    //generate tree
    for (int i = 0; i < (int) this->instruction.size(); i++) {
        char c = this->instruction[i];

        if (c == 'F') {
            //save to lines
            this->lines.push_back(std::make_pair(this->pos, this->pos + this->dir * this->lineLength));
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
}

void LSystem::DrawTree() {
    for (auto line: this->lines) {
        DrawUtils::drawLine(this->window, 
            GameManager::convertWorldToScreen(line.first), 
            GameManager::convertWorldToScreen(line.second), 
            this->color, this->lineSize);
    }
}

void LSystem::CreatePhysicTree() {
    int counter = 0;
    for (auto line: this->lines) {
        auto p1 = line.first;
        auto p2 = line.second;
        auto pmid = Math::Middlepoint(p1, p2);

        PhysicPoint phy1 = PhysicPoint(1, p1, this->manager->timeStep);
        PhysicPoint phy3 = PhysicPoint(1, p2, this->manager->timeStep);
        PhysicPoint phy2 = PhysicPoint(1, pmid, this->manager->timeStep);

        if (counter == 0) {phy1.isStatic = true;}

        int idx1 = this->manager->addPoint(phy1);
        int idx2 = this->manager->addPoint(phy2);
        int idx3 = this->manager->addPoint(phy3);

        //connect with absolute constraint between 3 points
        AbsoluteConstraint c1 = AbsoluteConstraint(this->manager->getPoint(idx1), this->manager->getPoint(idx2), 
            this->lineLength / 2.0);
        AbsoluteConstraint c2 = AbsoluteConstraint(this->manager->getPoint(idx2), this->manager->getPoint(idx3), 
            this->lineLength / 2.0);
        AbsoluteConstraint c3 = AbsoluteConstraint(this->manager->getPoint(idx1), this->manager->getPoint(idx3), 
            this->lineLength);

        this->manager->addAbsoluteConstraint(c1);
        this->manager->addAbsoluteConstraint(c2);
        this->manager->addAbsoluteConstraint(c3);
        counter++;
    }

    this->manager->Initialize(this->window);
}