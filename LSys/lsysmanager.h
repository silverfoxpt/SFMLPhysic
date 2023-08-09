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

class LSystemManager: Monobehaviour<sf::RenderWindow*> {
    public:
        sf::RenderWindow* window;

        //used vars

        void Initialize(sf::RenderWindow* window) override;
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
};

#endif