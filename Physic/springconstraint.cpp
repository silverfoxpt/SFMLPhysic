#include "springconstraint.h"

SpringConstraint::SpringConstraint(PhysicPoint* p1, PhysicPoint* p2, float normalDis, float springCoefficient) {
    this->p1 = p1;
    this->p2 = p2;
    if (p1 == nullptr || p2 == nullptr) {std::cout << "Error: point don't exist!"; return;}

    this->normalDis = normalDis;
    this->springCoefficient = springCoefficient;

    //custom
    this->p1MassPortion = (p1->mass / (p1->mass + p2->mass));
    this->p2MassPortion = (p2->mass / (p1->mass + p2->mass));
}

void SpringConstraint::Initialize(sf::RenderWindow* window) {
    this->window = window;
}

void SpringConstraint::Update(sf::Event event) {
    if (p1->isStatic && p2->isStatic) {
        return;
    }

    float error = Math::Distance(p1->currentPosition, p2->currentPosition) - this->normalDis;
    auto p1Vec = Math::normalizeVec(p2->currentPosition - p1->currentPosition);
    auto p2Vec = Math::normalizeVec(p1->currentPosition - p2->currentPosition);

    if (p1->isStatic) {
        p2->AddForce(Math::scaleVec(p2Vec, error * (this->springCoefficient)));
    } else if (p2->isStatic) {
        p1->AddForce(Math::scaleVec(p1Vec, error * (this->springCoefficient)));
    } else {
        p1->AddForce(Math::scaleVec(p1Vec, error * (this->springCoefficient) * this->p2MassPortion));
        p2->AddForce(Math::scaleVec(p2Vec, error * (this->springCoefficient) * this->p1MassPortion));
    }
}

void SpringConstraint::Visualize(sf::Event event) {
    DrawUtils::drawLine(this->window, 
        GameManager::convertWorldToScreen(this->p1->currentPosition), 
        GameManager::convertWorldToScreen(this->p2->currentPosition), sf::Color::Red, 
        3.0);
}

void SpringConstraint::LateUpdate() {

}

void SpringConstraint::Reset() {

}