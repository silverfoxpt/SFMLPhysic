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

struct Segment {
    sf::Vector2f startPoint;
    sf::Vector2f endPoint;
    int previousSegmentIndex;
    int currentSegmentIndex;
    int nextSegmentIndex;
};

class LSystem: Monobehaviour<sf::RenderWindow*, PhysicManager*> {
    public:
        sf::RenderWindow* window;
        PhysicManager* manager;

        //used vars
        //settings
        int numIter         = 6; //old is 6
        /*std::string startInstruction = "X";
        std::map<char, std::string> updateMap = {
            {'X', "F+[[X]-X]-F[-FX]+X"},
            {'F', "FF"}
        };*/

        std::string startInstruction = "F";
        std::map<char, std::string> updateMap = {
            {'F', "FF"}
        };

        //draw
        std::string instruction;
        std::vector<Segment> lines;

        //settings
        sf::Vector2f startPos   = sf::Vector2f(400, -400); //old is sf::Vector2f(400, -700);
        sf::Color color         = sf::Color::White;
        float lineSize          = 5;
        float lineLength        = 50; //old is 3
        float angle             = 25;

        //move
        sf::Vector2f dir        = Math::getUpVec();
        sf::Vector2f pos;
        std::stack<std::pair<sf::Vector2f, sf::Vector2f>> mem;
        std::stack<int> stackIndices;

        void Initialize(sf::RenderWindow* window, PhysicManager* physicManager) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

    private:
        void CreateTree();
        void DrawTree();

        void CreatePhysicTree();
        
};

#endif