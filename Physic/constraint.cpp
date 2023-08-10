#include "constraint.h"

AbsoluteConstraint::AbsoluteConstraint(PhysicPoint* p1, PhysicPoint* p2, float dis, sf::Color color) {
    this->p1 = p1;
    this->p2 = p2;
    this->color = color;
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

    if (p1->animationStatus == PhysicState::Static && p2->animationStatus == PhysicState::Static) {
        return;
    }

    //std::cout << p1->currentPosition.x << " " << p1->currentPosition.y << " " << p2->currentPosition.x << " " << p2->currentPosition.y << " ; " << p1->idx << " " << p2->idx << '\n';
    float error = Math::Distance(p1->currentPosition, p2->currentPosition) - this->dis; 
    auto p1Vec = Math::normalizeVec(p2->currentPosition - p1->currentPosition); 
    auto p2Vec = Math::normalizeVec(p1->currentPosition - p2->currentPosition); 

    //if (error > 0.1) {std::cout << error << '\n';}

    if (p1->animationStatus == PhysicState::Static) {
        p2->currentPosition += Math::scaleVec(p2Vec, error);
    } else if (p2->animationStatus == PhysicState::Static) {
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
            GameManager::convertWorldToScreen(this->p2->currentPosition), this->color, 
            3.0);
    }
}

void AbsoluteConstraint::LateUpdate() {

}

void AbsoluteConstraint::Reset() {

}