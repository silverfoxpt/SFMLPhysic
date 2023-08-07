#ifndef H_FISHMANAGER
#define H_FISHMANAGER

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

#include "fish.h"

class FishManager: Monobehaviour<sf::RenderWindow*> {
    public:
        sf::RenderWindow* window;

        //used vars
        int numFish = 200;

        std::vector<Fish> fishes;
        std::vector<GameObject*> fishObjects;
        std::vector<PhysicPoint*> fishPhysics;

        //settings
        float avoidFactor = 0.05f;
        float matchingFactor = 0.05f;
        float centeringFactor = 0.0005f;

        float protectedRange = 20;
        float visualRange = 80;

        float minVelocity = 5; //test
        float maxVelocity = 15; //test

        float leftMargin = 100;
        float rightMargin = /*GameManager::mainWindowSize.x - leftMargin*/ 700;
        float topMargin = -100;
        float bottomMargin = /*-(GameManager::mainWindowSize.y - topMargin)*/ -700; 

        float turnFactor = 0.2f;

        //functions
        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        static FishManager* GetInstance() {
            if (!instance) {
                instance = new FishManager();
            }
            return instance;
        }

        Fish* getFish(int idx) {
            if (idx < 0 || idx >= (int) this->fishes.size()) {
                std::cout << "Fish not found!" << '\n';
                return nullptr;
            }
            return &this->fishes[idx];
        }

    private:
        static FishManager* instance;

        void SpawnFish();

        void Seperation();
        void Alignment();        
        void Cohesion();
        void TurnOnEdge();
        void LimitVelocity();
};

#endif