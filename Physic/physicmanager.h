#ifndef H_PHYSICMANAGER
#define H_PHYSICMANAGER

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "../Reuseable/gameManager.h"
#include "../Reuseable/gameobject.h"
#include "../Reuseable/templateclass.h"
#include "../Reuseable/drawshapes.h"

#include "physicpoint.h"

#include "constraint.h"
#include "springconstraint.h"
#include "inequalconstraint.h"
#include "boundaryconstraint.h"

class PhysicManager: Monobehaviour<sf::RenderWindow*> {
    public:
        sf::RenderWindow* window;

        //used vars
        float timeStep = 0.06; //old is 0.005
        int substep = 30;  //old is 30

        float dampingCoefficient = 0.1; //old is 0.1
        float gravityCoefficient = 9.81;

        bool enableGround = true; //old is true
        float groundHeightValue = -750;

        std::vector<PhysicPoint> points;
        std::vector<AbsoluteConstraint> constraints;
        std::vector<SpringConstraint> springs;
        std::vector<SmallerDistanceConstraint> smallConstraints;
        std::vector<LargerDistanceConstraint> largeConstraints;

        std::vector<DownYConstraint> downConstraints;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        PhysicPoint* getPoint(int idx) {
            if (idx < 0 || idx >= (int) this->points.size()) {std::cout << "Point not found!"; return nullptr;}
            return &this->points[idx];
        }

        int addPoint(PhysicPoint point) {
            point.Initialize(this->window);
            point.idx = this->points.size();
            
            this->points.push_back(point);

            return this->points.size() - 1;
        }

        void addAbsoluteConstraint(AbsoluteConstraint constraint) {
            constraint.Initialize(this->window);
            this->constraints.push_back(constraint);
        }

        void AddGroundConstraint();

    private:
        void TestInitialize();
        void TestSpringSystem();
        void TestSoftbody();

        void TestUpdate();
        
        void AddForceByInput(sf::Event event);
        void AddForceAirResistance();
        void AddForceGravity();
};


#endif