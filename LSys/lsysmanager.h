#ifndef H_LSYSMANAGER
#define H_LSYSMANAGER

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "lsystem.h"

class LSystemManager: Monobehaviour<sf::RenderWindow*, PhysicManager*, Flowfield*> {
    public:
        sf::RenderWindow* window;
        PhysicManager* physicManager;
        Flowfield* flowfield;

        //used vars
        std::vector<LSystem> lsystems;

        void Initialize(sf::RenderWindow* window, PhysicManager* physicManager, Flowfield* flowfield) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        static LSystemManager* GetInstance() {
            if (instance == nullptr) {
                instance = new LSystemManager();
            }
            return instance;
        }

    private:
        static LSystemManager* instance;

        void TestAddLSystems();
};

#endif