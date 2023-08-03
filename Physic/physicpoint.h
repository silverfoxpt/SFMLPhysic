#ifndef H_PHYSICPOINT
#define H_PHYSICPOINT

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

enum PhysicState {
    
};

class PhysicPoint : public Monobehaviour<sf::RenderWindow*>{
    public:
        bool isStatic       = false;
        float mass          = 1;
        float timeStep      = 0.01;
        int idx             = -1; //debug purpose

        sf::Vector2f force                  = sf::Vector2f(0, 0);

        sf::Vector2f velocity               = sf::Vector2f(0, 0);
        sf::Vector2f currentPosition        = sf::Vector2f(0, 0);
        sf::Vector2f previousPosition       = sf::Vector2f(0, 0);
        sf::Vector2f acceleration           = sf::Vector2f(0, 0);

        sf::RenderWindow* window;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        PhysicPoint(float mass, sf::Vector2f currentPosition, float timeStep);
        PhysicPoint() {}

        void AddForce(sf::Vector2f force);

    private:
        void VerletUpdate();
};

#endif