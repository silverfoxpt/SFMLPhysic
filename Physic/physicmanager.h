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

class PhysicManager: Monobehaviour<sf::RenderWindow*>, Manager<PhysicPoint> {
    public:
        sf::RenderWindow* window;

        //used vars
        float timeStep = 0.06; //old is 0.06
        int substep = 4;  //old is 30

        float dampingCoefficient = 0.02; //old is 0.1
        float gravityCoefficient = 9.81; //old is 9.81 - Earth gravity

        bool enableGround = true; //old is true
        float groundHeightValue = -800;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        void addAbsoluteConstraint(AbsoluteConstraint constraint) {
            constraint.Initialize(this->window);
            this->constraints.push_back(constraint);
        }

        void addSpringConstraint(SpringConstraint constraint) {
            constraint.Initialize(this->window);
            this->springs.push_back(constraint);
        }

        PhysicPoint* AddNewControlledComponent(PhysicPoint point) override{
            point.Initialize(this->window);
            point.idx = this->controlledComponents.size();
            
            this->controlledComponents.push_back(point);
            return this->GetControlledComponent(this->controlledComponents.size() - 1);
        }

        int AddNewControlledComponentReturnIdx(PhysicPoint point) {
            point.Initialize(this->window);
            point.idx = this->controlledComponents.size();
            
            this->controlledComponents.push_back(point);
            return point.idx;
        }

        PhysicPoint* GetControlledComponent(int idx) override{
            if (idx < 0 || idx >= (int) this->controlledComponents.size()) {std::cout << "Point not found!"; return nullptr;}
            return &this->controlledComponents[idx];
        }

        void AddGroundConstraint();
        
        static PhysicManager* GetInstance() {
            if (!instance) {
                instance = new PhysicManager();
            }
            return instance;
        }

    private:
        void TestInitialize();
        void TestSpringSystem();
        void TestSoftbody();

        void TestUpdate();
        
        void AddForceByInput(sf::Event event);
        void AddForceAirResistance();
        void AddForceGravity();

        //std::vector<PhysicPoint> points;
        std::vector<AbsoluteConstraint> constraints;
        std::vector<SpringConstraint> springs;
        std::vector<SmallerDistanceConstraint> smallConstraints;
        std::vector<LargerDistanceConstraint> largeConstraints;
        std::vector<DownYConstraint> downConstraints;

        static PhysicManager* instance;
};


#endif