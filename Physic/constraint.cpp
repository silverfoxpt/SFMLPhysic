#include "constraint.h"

AbsoluteConstraint::AbsoluteConstraint(PhysicPoint* p1, PhysicPoint* p2, float dis) {
    this->p1 = p1;
    this->p2 = p2;
    if (p1 == nullptr || p2 == nullptr) {std::cout << "Error: point don't exist!"; return;}

    this->dis = dis;

    //custom
    this->p1MassPortion = (p1->mass / (p1->mass + p2->mass));
    this->p2MassPortion = (p2->mass / (p1->mass + p2->mass));
}

void AbsoluteConstraint::Initialize(sf::RenderWindow* window) {
    this->window = window;
}

void AbsoluteConstraint::Update(sf::Event event) {    
    if (p1 == nullptr || p2 == nullptr) {
        std::cout << "Error: this is what?" << '\n';
        return;
    }

    if (p1->isStatic && p2->isStatic) {
        return;
    }

    //std::cout << p1->currentPosition.x << " " << p1->currentPosition.y << " " << p2->currentPosition.x << " " << p2->currentPosition.y << " ; " << p1->idx << " " << p2->idx << '\n';
    float error = Math::Distance(p1->currentPosition, p2->currentPosition) - this->dis; 
    auto p1Vec = Math::normalizeVec(p2->currentPosition - p1->currentPosition); 
    auto p2Vec = Math::normalizeVec(p1->currentPosition - p2->currentPosition); 

    if (p1->isStatic) {
        p2->currentPosition += Math::scaleVec(p2Vec, error);
    } else if (p2->isStatic) {
        p1->currentPosition += Math::scaleVec(p1Vec, error);
    } else {
        p1->currentPosition += Math::scaleVec(p1Vec, error * this->p2MassPortion);
        p2->currentPosition += Math::scaleVec(p2Vec, error * this->p1MassPortion);
    }
}

void AbsoluteConstraint::Visualize(sf::Event event) {
    if (display) {
        DrawUtils::drawLine(this->window, 
            GameManager::convertWorldToScreen(this->p1->currentPosition), 
            GameManager::convertWorldToScreen(this->p2->currentPosition), sf::Color::Green, 
            3.0);
    }
}

void AbsoluteConstraint::LateUpdate() {

}

void AbsoluteConstraint::Reset() {

}