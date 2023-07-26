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
}

void LargerDistanceConstraint::Visualize(sf::Event event) {

}

void LargerDistanceConstraint::LateUpdate() {

}

void LargerDistanceConstraint::Reset() {

}

