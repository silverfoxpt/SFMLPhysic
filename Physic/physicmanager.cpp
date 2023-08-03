#include "physicmanager.h"

PhysicManager* PhysicManager::instance = nullptr;

void PhysicManager::Initialize(sf::RenderWindow* window) {
    this->window = window;
    this->controlledComponents.reserve(100000);

    this->TestInitialize();
    if (this->enableGround) {
        this->AddGroundConstraint();
    }
}

void PhysicManager::Update(sf::Event event) {
    this->TestUpdate();
    //this->AddForceByInput(event);
    this->AddForceGravity();
    for (auto& spring: this->springs) { spring.AddSpringForce(); }

    this->AddForceAirResistance(); //always last

    for (auto& point: this->controlledComponents) {
        point.Update(event);
    }

    for (int i = 0; i < this->substep; i++) {
        for (auto& constraint: this->constraints) {
            constraint.Update(event);
        }

        for (auto& spring: this->springs) {
            spring.Update(event);
        }

        for (auto& smallConstraint: this->smallConstraints) {
            smallConstraint.Update(event);
        }

        for (auto& largeConstraint: this->largeConstraints) {
            largeConstraint.Update(event);
        }

        for (auto& downConstraint: this->downConstraints) {
            downConstraint.Update(event);
        }
    }
}

void PhysicManager::Visualize(sf::Event event) {
    for (auto& point: this->controlledComponents) {
        //point.Visualize(event); 
    }

    for (auto& constraint: this->constraints) {
        constraint.Visualize(event);
    }

    for (auto& spring: this->springs) {
        spring.Visualize(event);
    }
}

void PhysicManager::LateUpdate() {

}

void PhysicManager::Reset() {
    this->controlledComponents.clear();
    this->constraints.clear();
    this->springs.clear();
    this->smallConstraints.clear();
    this->largeConstraints.clear();

    this->downConstraints.clear();
}

void PhysicManager::TestInitialize() {
    //this->TestSpringSystem();
    //this->TestSoftbody();
}

void PhysicManager::TestSoftbody() {
    std::vector<std::vector<int>> pointIdx;

    int counter = 0;
    for (int i = 0; i < 5; i++) {
        std::vector<int> tt;
        pointIdx.push_back(tt);
        for (int j = 0; j < 5; j++) {
            auto pos = GameManager::convertScreenToWorld(sf::Vector2f(400, 400)) + sf::Vector2f(j * 50, -i * 50);
            PhysicPoint p1 = PhysicPoint(1, pos, this->timeStep);
            p1.Initialize(this->window); 

            pointIdx[i].push_back(counter); controlledComponents.push_back(p1);
            counter++;
        }
    }
    
    // Create springs
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // Create top spring
            if (j > 0) {
                SpringConstraint topSpring(this->GetControlledComponent(pointIdx[i][j]), this->GetControlledComponent(pointIdx[i][j - 1]), 50, 2, 20);
                topSpring.Initialize(this->window);
                this->springs.push_back(topSpring);
            }

            // Create bottom spring
            if (j < 4) {
                SpringConstraint bottomSpring(this->GetControlledComponent(pointIdx[i][j]), this->GetControlledComponent(pointIdx[i][j + 1]), 50, 2, 20);
                bottomSpring.Initialize(this->window);
                this->springs.push_back(bottomSpring);
            }

            // Create left spring
            if (i > 0) {
                SpringConstraint leftSpring(this->GetControlledComponent(pointIdx[i][j]), this->GetControlledComponent(pointIdx[i - 1][j]), 50, 2, 20);
                leftSpring.Initialize(this->window);
                this->springs.push_back(leftSpring);
            }

            // Create right spring
            if (i < 4) {
                SpringConstraint rightSpring(this->GetControlledComponent(pointIdx[i][j]), this->GetControlledComponent(pointIdx[i + 1][j]), 50, 2, 20);
                rightSpring.Initialize(this->window);
                this->springs.push_back(rightSpring);
            }

            // Create two diagonal springs
            if (i > 0 && j > 0) {
                SpringConstraint diag1Spring(this->GetControlledComponent(pointIdx[i][j]), this->GetControlledComponent(pointIdx[i - 1][j - 1]), 70.71067, 2, 20);
                diag1Spring.Initialize(this->window);
                this->springs.push_back(diag1Spring);
            }

            if (i < 4 && j > 0) {
                SpringConstraint diag2Spring(this->GetControlledComponent(pointIdx[i][j]), this->GetControlledComponent(pointIdx[i + 1][j - 1]), 70.71067, 2, 20);
                diag2Spring.Initialize(this->window);
                this->springs.push_back(diag2Spring);
            }
        }
    }

}

void PhysicManager::TestSpringSystem() {
    PhysicPoint p1 = PhysicPoint(1, GameManager::convertScreenToWorld(sf::Vector2f(400, 400)), this->timeStep);
    p1.Initialize(this->window); 
    p1.animationStatus = PhysicState::Static;
    this->controlledComponents.push_back(p1);

    PhysicPoint p2 = PhysicPoint(1, GameManager::convertScreenToWorld(sf::Vector2f(400, 450)), this->timeStep);
    p2.Initialize(this->window); 
    this->controlledComponents.push_back(p2);

    PhysicPoint p3 = PhysicPoint(1, GameManager::convertScreenToWorld(sf::Vector2f(400, 500)), this->timeStep);
    p3.Initialize(this->window); 
    this->controlledComponents.push_back(p3);

    PhysicPoint p4 = PhysicPoint(1, GameManager::convertScreenToWorld(sf::Vector2f(400, 510)), this->timeStep);
    p4.Initialize(this->window); 
    this->controlledComponents.push_back(p4);

    /*AbsoluteConstraint constraint(this->GetControlledComponent(0), this->GetControlledComponent(1), 50);
    this->addAbsoluteConstraint(constraint);

    AbsoluteConstraint constraint2(this->GetControlledComponent(1), this->GetControlledComponent(2), 50);
    this->addAbsoluteConstraint(constraint2); */

    /*AbsoluteConstraint cosntraint3(this->GetControlledComponent(1), this->GetControlledComponent(3), 60);
    cosntraint3.Initialize(this->window);
    this->constraints.push_back(cosntraint3);*/

    SpringConstraint spring(this->GetControlledComponent(0), this->GetControlledComponent(1), 70, 2, 20);
    spring.Initialize(this->window);
    this->springs.push_back(spring);

    SpringConstraint spring2(this->GetControlledComponent(1), this->GetControlledComponent(2), 70, 2, 20);
    spring2.Initialize(this->window);
    this->springs.push_back(spring2);

    /*SmallerDistanceConstraint smallCon(25, this->GetControlledComponent(0), this->GetControlledComponent(1));
    smallCon.Initialize(this->window);
    this->smallConstraints.push_back(smallCon);*/

    /*LargerDistanceConstraint largeCon(100, this->GetControlledComponent(0), this->GetControlledComponent(1));
    largeCon.Initialize(this->window);
    this->largeConstraints.push_back(largeCon);*/
}

void PhysicManager::TestUpdate() {
    
}

void PhysicManager::AddGroundConstraint() {
    for (int i = 0; i < (int) this->controlledComponents.size(); i++) {
        DownYConstraint yConstraint(this->GetControlledComponent(i), this->groundHeightValue);
        this->downConstraints.push_back(yConstraint);
    }
}

void PhysicManager::AddForceAirResistance() {
    for (auto& point: this->controlledComponents) {
        float length = Math::Length(point.velocity);

        auto p = Math::scaleVec(Math::normalizeVec(point.velocity), -this->dampingCoefficient * length); 
        point.AddForce(p);
    }
}

void PhysicManager::AddForceGravity() {
    for (auto& point: this->controlledComponents) {
        point.AddForce(sf::Vector2f(0.0, -this->gravityCoefficient * point.mass));
    }
}

void PhysicManager::AddForceByInput(sf::Event event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        for (auto& point: this->controlledComponents) {
            point.AddForce(sf::Vector2f(2, 0));
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        for (auto& point: this->controlledComponents) {
            point.AddForce(sf::Vector2f(-2, 0));
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        for (auto& point: this->controlledComponents) {
            point.AddForce(sf::Vector2f(0, 20));
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        for (auto& point: this->controlledComponents) {
            point.AddForce(sf::Vector2f(0, -20));
        }
    }
}