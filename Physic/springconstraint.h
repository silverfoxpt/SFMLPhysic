#ifndef H_SPRINGCONSTRAINT
#define H_SPRINGCONSTRAINT

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
#include "inequalconstraint.h"

class SpringConstraint: Monobehaviour<sf::RenderWindow*> {
    public:
        sf::RenderWindow* window;

        //used vars
        PhysicPoint* p1;
        PhysicPoint* p2;
        float normalDis;
        float springCoefficient;
        float allowedMaxBend;

        LargerDistanceConstraint largeConstraint;
        SmallerDistanceConstraint smallConstraint;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        void AddSpringForce();

        SpringConstraint(PhysicPoint* p1, PhysicPoint* p2, float normalDis, float springCoefficient, float allowedMaxBend);

    private:
        float p1MassPortion, p2MassPortion;
        
};

#endif