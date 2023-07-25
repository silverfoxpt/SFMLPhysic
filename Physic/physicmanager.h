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

class PhysicManager: Monobehaviour<sf::RenderWindow*> {
    public:
        sf::RenderWindow* window;

        //used vars
        float timeStep = 0.01;
        int substep = 10;

        std::vector<PhysicPoint> points;
        std::vector<AbsoluteConstraint> constraints;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        PhysicPoint* getPoint(int idx) {
            if (idx < 0 || idx >= (int) this->points.size()) {std::cout << "Point not found!"; return nullptr;}
            return &this->points[idx];
        }

    private:
        void TestInitialize();
        void TestUpdate();
};


#endif