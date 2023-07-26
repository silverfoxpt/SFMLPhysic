#ifndef H_INEQUALCONSTRAINT
#define H_INEQUALCONSTRAINT

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

class LargerDistanceConstraint: Monobehaviour<sf::RenderWindow*> {
    public:
        sf::RenderWindow* window;

        //used vars
        float largerThanDis = 0;
        PhysicPoint* p1;
        PhysicPoint* p2;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        LargerDistanceConstraint(float largerThanDis, PhysicPoint* p1, PhysicPoint* p2);
    private:
        float p1MassPortion, p2MassPortion;
};

class SmallerDistanceConstraint: Monobehaviour<sf::RenderWindow*> {
    public:
        sf::RenderWindow* window;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

    private:
        
};

#endif