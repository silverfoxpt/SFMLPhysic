#ifndef H_FLOWFIELD
#define H_FLOWFIELD

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

#include "../Physic/physicmanager.h"

#include "perlin.h"

class Flowfield: Monobehaviour<sf::RenderWindow*> {
    public:
        sf::RenderWindow* window;
        PerlinNoise noise;

        //some settings
        int row;
        int col;

        int cellSize = 10;

        //used vars
        std::vector<std::vector<float>> angleValues;
        sf::Clock clock;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

    private:
        void visualizeFlowField();
};

#endif