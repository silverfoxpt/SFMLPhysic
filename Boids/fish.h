#ifndef H_FISH
#define H_FISH

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
#include "../Reuseable/gameobjectmanager.h"

#include "../Physic/physicmanager.h"

class Fish: Monobehaviour<sf::RenderWindow*, GameobjectManager*, PhysicManager*> {
    public:
        sf::RenderWindow* window;
        PhysicManager* physicManager;
        GameobjectManager* gameobjectManager;

        //used var
        PhysicPoint* physicPoint;
        GameObject* gameObject;

        void Initialize(sf::RenderWindow* window, GameobjectManager* gameobjectManager, PhysicManager* physicManager) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

    private:
        
};

#endif