#include "lsystem.h"

void LSystem::Initialize(sf::RenderWindow* window, PhysicManager* physicManager) {
    this->window = window;
    this->manager = physicManager;

    this->pos           = this->startPos;
    this->instruction   = this->startInstruction;
    this->dir           = Math::getUpVec();

    this->CreateTree();
    //this->CreatePhysicTree();
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
    int previousSegmentIndex = -1; // Initialize to -1 for the first segment
    for (int i = 0; i < (int) this->instruction.size(); i++) {
        char c = this->instruction[i];

        if (c == 'F') {
            // Save to lines and update segment indices
            int currentSegmentIndex = this->lines.size();
            this->lines.push_back(Segment{this->pos, this->pos + this->dir * this->lineLength, previousSegmentIndex, currentSegmentIndex, -1});

            if (previousSegmentIndex >= 0) {
                this->lines[previousSegmentIndex].nextSegmentIndex = currentSegmentIndex;
            }

            this->pos = this->pos + this->dir * this->lineLength;
            previousSegmentIndex = currentSegmentIndex;
        } else if (c == '-') {
            this->dir = Math::spinPoint(this->dir, sf::Vector2f(0, 0), this->angle);
        } else if (c == '+') {
            this->dir = Math::spinPoint(this->dir, sf::Vector2f(0, 0), -this->angle);
        } else if (c == '[') {
            this->mem.push(std::make_pair(this->pos, this->dir));
            this->stackIndices.push(previousSegmentIndex); // Push the current previousSegmentIndex to the stack
        } else if (c == ']') {
            auto p = this->mem.top(); this->mem.pop();
            this->pos = p.first;
            this->dir = p.second;

            if (!stackIndices.empty()) {
                previousSegmentIndex = stackIndices.top(); // Retrieve the previousSegmentIndex from the stack
                stackIndices.pop(); // Pop the top element from the stack
            } else {
                previousSegmentIndex = -1; // If the stack is empty, reset to -1 for the root segment
            }
        }
    }
}

void LSystem::DrawTree() {
    for (auto line: this->lines) {
        DrawUtils::drawLine(this->window, 
            GameManager::convertWorldToScreen(line.startPoint), 
            GameManager::convertWorldToScreen(line.endPoint), 
            this->color, this->lineSize);
    }
}

void LSystem::CreatePhysicTree() {
    int counter = 0;

    std::vector<int> parentSegmentLastPointIdx;
    parentSegmentLastPointIdx.resize(this->lines.size());

    for (auto& line: this->lines) {
        auto p1 = line.startPoint;
        auto p2 = line.endPoint;
        auto pmid = Math::Middlepoint(p1, p2);

        PhysicPoint phy1 = PhysicPoint(1, p1, this->manager->timeStep);
        PhysicPoint phy3 = PhysicPoint(1, p2, this->manager->timeStep);
        PhysicPoint phy2 = PhysicPoint(1, pmid, this->manager->timeStep);

        if (counter == 0) {phy1.isStatic = true;}

        int idx1 = -1;
        if (counter == 0) {
            idx1 = this->manager->addPoint(phy1);
        } else {
            idx1 = parentSegmentLastPointIdx[line.previousSegmentIndex];
        }
        int idx2 = this->manager->addPoint(phy2);
        int idx3 = this->manager->addPoint(phy3);

        //connect with absolute constraint between 3 points
        AbsoluteConstraint c1 = AbsoluteConstraint(this->manager->getPoint(idx1), this->manager->getPoint(idx2), 
            this->lineLength / 2.0); c1.display = false;
        AbsoluteConstraint c2 = AbsoluteConstraint(this->manager->getPoint(idx2), this->manager->getPoint(idx3), 
            this->lineLength / 2.0); c2.display = false;
        AbsoluteConstraint c3 = AbsoluteConstraint(this->manager->getPoint(idx1), this->manager->getPoint(idx3), 
            this->lineLength);
        c3.display = true;

        this->manager->addAbsoluteConstraint(c1);
        this->manager->addAbsoluteConstraint(c2);
        this->manager->addAbsoluteConstraint(c3);
        counter++;

        //std::cout << this->manager->constraints[this->manager->constraints.size()-1].p1->currentPosition.x << '\n';
        parentSegmentLastPointIdx[line.currentSegmentIndex] = idx3;
    }
    this->manager->Initialize(this->window);
}