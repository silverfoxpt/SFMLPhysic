#include "boundaryconstraint.h"

DownYConstraint::DownYConstraint(PhysicPoint* p1, float yValue) {
    this->p1 = p1;
    this->yValue = yValue;

    if (p1 == nullptr) {
        std::cout << "Error: Point not found!"; return;
    }
}

void DownYConstraint::Initialize(sf::RenderWindow* window) {
    this->window = window;
}

void DownYConstraint::Update(sf::Event event) {
    if (p1->isStatic) {return;}

    float error = p1->currentPosition.y - this->yValue;
    auto p1Vec = sf::Vector2f(0, 1);

    if (error < 0) { //x is under presumed value
        //p1->currentPosition += Math::scaleVec(p1Vec, std::abs(error));
        p1->currentPosition.y = this->yValue;
    }
}

void DownYConstraint::Visualize(sf::Event event) {

}

void DownYConstraint::LateUpdate() {

}

void DownYConstraint::Reset() {

}