#include "inequalconstraint.h"

LargerDistanceConstraint::LargerDistanceConstraint(float largerThanDis, PhysicPoint* p1, PhysicPoint* p2) {
    this->largerThanDis = largerThanDis;
    this->p1 = p1;
    this->p2 = p2;

    if (p1 == nullptr || p2 == nullptr) {
        std::cout << "Error: point not found!"; return;
    }

    this->p1MassPortion = (p1->mass / (p1->mass + p2->mass));
    this->p2MassPortion = (p2->mass / (p1->mass + p2->mass));
}

void LargerDistanceConstraint::Initialize(sf::RenderWindow* window) {
    this->window = window;
}

void LargerDistanceConstraint::Update(sf::Event event) {
    if (p1->isStatic && p2->isStatic) {
        return;
    }

    float error = Math::Distance(p1->currentPosition, p2->currentPosition) - this->largerThanDis;
    auto p1Vec = Math::normalizeVec(p2->currentPosition - p1->currentPosition);
    auto p2Vec = Math::normalizeVec(p1->currentPosition - p2->currentPosition);

    if (error < 0) { //if distance smaller than lower limit
        if (p1->isStatic) {
            p2->currentPosition += Math::scaleVec(p2Vec, error);
        } else if (p2->isStatic) {
            p1->currentPosition += Math::scaleVec(p1Vec, error);
        } else {
            p1->currentPosition += Math::scaleVec(p1Vec, error * this->p2MassPortion);
            p2->currentPosition += Math::scaleVec(p2Vec, error * this->p1MassPortion);
        }
    }
}

void LargerDistanceConstraint::Visualize(sf::Event event) {

}

void LargerDistanceConstraint::LateUpdate() {

}

void LargerDistanceConstraint::Reset() {

}

SmallerDistanceConstraint::SmallerDistanceConstraint(float smallerThanDis, PhysicPoint* p1, PhysicPoint* p2) {
    this->smallerThanDis = smallerThanDis;
    this->p1 = p1;
    this->p2 = p2;

    if (p1 == nullptr || p2 == nullptr) {
        std::cout << "Error: point not found!"; return;
    }

    this->p1MassPortion = (p1->mass / (p1->mass + p2->mass));
    this->p2MassPortion = (p2->mass / (p1->mass + p2->mass));
}

void SmallerDistanceConstraint::Initialize(sf::RenderWindow* window) {
    this->window = window;
}

void SmallerDistanceConstraint::Update(sf::Event event) {
    if (p1->isStatic && p2->isStatic) {
        return;
    }

    float error = Math::Distance(p1->currentPosition, p2->currentPosition) - this->smallerThanDis;
    auto p1Vec = Math::normalizeVec(p2->currentPosition - p1->currentPosition);
    auto p2Vec = Math::normalizeVec(p1->currentPosition - p2->currentPosition);

    if (error > 0) { //if distance larger than lower limit
        if (p1->isStatic) {
            p2->currentPosition += Math::scaleVec(p2Vec, error);
        } else if (p2->isStatic) {
            p1->currentPosition += Math::scaleVec(p1Vec, error);
        } else {
            p1->currentPosition += Math::scaleVec(p1Vec, error * this->p2MassPortion);
            p2->currentPosition += Math::scaleVec(p2Vec, error * this->p1MassPortion);
        }
    }
}

void SmallerDistanceConstraint::Visualize(sf::Event event) {

}

void SmallerDistanceConstraint::LateUpdate() {

}

void SmallerDistanceConstraint::Reset() {

}

