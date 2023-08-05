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

    private:
        static FishManager* instance;

        void SpawnFish();

        void Seperation();
        
};

#endif