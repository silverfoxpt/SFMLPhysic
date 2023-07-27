#ifndef H_LSYSTEM
#define H_LSYSTEM

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>
#include <stack>

#include "../Reuseable/gameManager.h"
#include "../Reuseable/gameobject.h"
#include "../Reuseable/templateclass.h"
#include "../Reuseable/drawshapes.h"

#include "../Physic/physicmanager.h"

class LSystem: Monobehaviour<sf::RenderWindow*> {
    public:
        sf::RenderWindow* window;

        //used vars
        int numIter         = 6;
        std::string instruction = "X";
        std::map<char, std::string> updateMap = {
            {'X', "F+[[X]-X]-F[-FX]+X"},
            {'F', "FF"}
        };

        //move
        sf::Vector2f dir        = Math::getUpVec();
        sf::Vector2f pos;
        std::stack<std::pair<sf::Vector2f, sf::Vector2f>> mem;

        //settings
        sf::Vector2f start      = sf::Vector2f(400, -800);
        sf::Color color         = sf::Color::White;
        float lineSize      = 5;
        float lineLength    = 10;
        float angle         = 25;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

    private:
        void CreateTree();
        
};

#endif