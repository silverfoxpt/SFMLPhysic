#include "lsystem.h"

void LSystem::Initialize(sf::RenderWindow* window, PhysicManager* physicManager, Flowfield* flowfield) {
    this->window = window;
    this->manager = physicManager;
    this->flowfield = flowfield;

    this->pos           = this->startPos;
    this->instruction   = this->startInstruction;
    this->dir           = Math::getUpVec();

    this->CreateTree();
    //this->CreatePhysicTree();
}

void LSystem::Update(sf::Event event) {
    this->UpdatePhysicTree();
}

void LSystem::Visualize(sf::Event event) {
    //this->DrawTree();
}

void LSystem::LateUpdate() {

}

void LSystem::Reset() {
    while(!mem.empty()) {mem.pop();}
    this->lines.clear();
    this->lastEndpointIndex.clear();
    this->allEndpointIndex.clear();
    
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

    std::vector<int> parentSegmentMiddlePointIdx;
    parentSegmentMiddlePointIdx.resize(this->lines.size());

    for (auto& line: this->lines) {
        auto p1 = line.startPoint;
        auto p2 = line.endPoint;
        auto pmid = Math::Middlepoint(p1, p2);

        PhysicPoint phy1 = PhysicPoint(0.01, p1, PhysicManager::GetInstance()->timeStep);
        PhysicPoint phy3 = PhysicPoint(0.01, p2, PhysicManager::GetInstance()->timeStep);
        PhysicPoint phy2 = PhysicPoint(0.01, pmid, PhysicManager::GetInstance()->timeStep);

        if (counter == 0) {phy1.animationStatus = PhysicState::Static;}

        int idx1 = -1;
        if (counter == 0) {
            idx1 = this->manager->AddNewControlledComponentReturnIdx(phy1);
        } else {
            idx1 = parentSegmentLastPointIdx[line.previousSegmentIndex];
        }
        int idx2 = this->manager->AddNewControlledComponentReturnIdx(phy2);
        int idx3 = this->manager->AddNewControlledComponentReturnIdx(phy3);

        //connect with absolute constraint between 3 points
        AbsoluteConstraint c1 = AbsoluteConstraint(this->manager->GetControlledComponent(idx1), this->manager->GetControlledComponent(idx2), 
            this->lineLength / 2.0); c1.display = false;
        AbsoluteConstraint c2 = AbsoluteConstraint(this->manager->GetControlledComponent(idx2), this->manager->GetControlledComponent(idx3), 
            this->lineLength / 2.0); c2.display = false;
        AbsoluteConstraint c3 = AbsoluteConstraint(this->manager->GetControlledComponent(idx1), this->manager->GetControlledComponent(idx3), 
            this->lineLength);
        c3.display = true;

        this->manager->addAbsoluteConstraint(c1);
        this->manager->addAbsoluteConstraint(c2);
        this->manager->addAbsoluteConstraint(c3);
        

        //add spring constraint
        if (counter != 0) {
            //anchor to each other
            auto mCurrent   = this->manager->GetControlledComponent(idx2);
            auto mPrev      = this->manager->GetControlledComponent(parentSegmentMiddlePointIdx[line.previousSegmentIndex]);
            AbsoluteConstraint m1 = AbsoluteConstraint(mCurrent, mPrev, 
                Math::Distance(mCurrent->currentPosition, mPrev->currentPosition)); m1.display = true;
            this->manager->addAbsoluteConstraint(m1);
            
            //anchor to ground
            float offset        = (phy3.currentPosition.x > this->startPos.x) ? 50 : -50;

            auto anchorPos      = sf::Vector2f(phy3.currentPosition.x + offset, this->manager->groundHeightValue);
            auto anchorCounterPos = sf::Vector2f(phy3.currentPosition.x - offset, this->manager->groundHeightValue);

            auto pAnchor        = PhysicPoint(1, anchorPos, PhysicManager::GetInstance()->timeStep); pAnchor.animationStatus = PhysicState::Static;
            auto pCounterAnchor = PhysicPoint(1, anchorCounterPos, PhysicManager::GetInstance()->timeStep); pCounterAnchor.animationStatus = PhysicState::Static;

            int idxAnchor       = this->manager->AddNewControlledComponentReturnIdx(pAnchor);     
            int idxCounterAnchor = this->manager->AddNewControlledComponentReturnIdx(pCounterAnchor);      

            SpringConstraint anchorConstraint = SpringConstraint(this->manager->GetControlledComponent(idx3), this->manager->GetControlledComponent(idxAnchor),
                Math::Distance(anchorPos, phy3.currentPosition), 2, 20); 
            anchorConstraint.display = false;

            SpringConstraint anchorConstraint2 = SpringConstraint(this->manager->GetControlledComponent(idx3), this->manager->GetControlledComponent(idxCounterAnchor),
                Math::Distance(anchorCounterPos, phy3.currentPosition), 2, 20); 
            anchorConstraint2.display = false;

            this->manager->addSpringConstraint(anchorConstraint);
            this->manager->addSpringConstraint(anchorConstraint2);
        } else { //for the first trunk, we need some absolute constraints
            float offset        = (phy3.currentPosition.x > this->startPos.x) ? 50 : -50;

            auto anchorPos      = sf::Vector2f(phy3.currentPosition.x + offset, this->manager->groundHeightValue);
            auto anchorCounterPos = sf::Vector2f(phy3.currentPosition.x - offset, this->manager->groundHeightValue);

            auto pAnchor        = PhysicPoint(1, anchorPos, PhysicManager::GetInstance()->timeStep); pAnchor.animationStatus = PhysicState::Static;
            auto pCounterAnchor = PhysicPoint(1, anchorCounterPos, PhysicManager::GetInstance()->timeStep); pCounterAnchor.animationStatus = PhysicState::Static;

            int idxAnchor       = this->manager->AddNewControlledComponentReturnIdx(pAnchor);     
            int idxCounterAnchor = this->manager->AddNewControlledComponentReturnIdx(pCounterAnchor);      
            
            AbsoluteConstraint anchorConstraint = AbsoluteConstraint(this->manager->GetControlledComponent(idx3), this->manager->GetControlledComponent(idxAnchor),
                Math::Distance(anchorPos, phy3.currentPosition)); 
            anchorConstraint.display = false;

            AbsoluteConstraint anchorConstraint2 = AbsoluteConstraint(this->manager->GetControlledComponent(idx3), this->manager->GetControlledComponent(idxCounterAnchor),
                Math::Distance(anchorCounterPos, phy3.currentPosition)); 
            anchorConstraint2.display = false;

            this->manager->addAbsoluteConstraint(anchorConstraint);
            this->manager->addAbsoluteConstraint(anchorConstraint2);
        }

        parentSegmentLastPointIdx[line.currentSegmentIndex] = idx3;
        parentSegmentMiddlePointIdx[line.currentSegmentIndex] = idx2;

        if (line.nextSegmentIndex == -1) {
            this->lastEndpointIndex.push_back(idx3);
        } else {
            this->allEndpointIndex.push_back(idx3);
        }
        

        counter++;
    }
    this->manager->Initialize(this->window);
}

void LSystem::UpdatePhysicTree() {
    for (auto endpoint: this->lastEndpointIndex) {
        auto p = this->manager->GetControlledComponent(endpoint);
        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            p->AddForce(sf::Vector2f(3.1, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            p->AddForce(sf::Vector2f(-3.1, 0));
        }*/
        auto pos = p->currentPosition;
        p->AddForce(this->flowfield->getForceFromPos(pos.x, pos.y) * 3.1f);
    }

    for (auto endpoint: this->allEndpointIndex) {
        auto p = this->manager->GetControlledComponent(endpoint);
        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            p->AddForce(sf::Vector2f(2, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            p->AddForce(sf::Vector2f(-2, 0));
        }
        p->AddForce(sf::Vector2f(0, 2));*/
        auto pos = p->currentPosition;
        p->AddForce(this->flowfield->getForceFromPos(pos.x, pos.y) * 2.0f);
    }
}