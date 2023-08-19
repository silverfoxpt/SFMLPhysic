#include "lsysmanager.h"

LSystemManager* LSystemManager::instance = nullptr;

void LSystemManager::Initialize(sf::RenderWindow* window, PhysicManager* physicManager, Flowfield* flowfield) {
    this->window = window;
    this->physicManager = physicManager;
    this->flowfield = flowfield;

    //add trees
    this->TestAddLSystems();
    //this->TestAddLSystemVideo();
}

void LSystemManager::Update(sf::Event event) {
    for (auto &sys : this->lsystems) {
        sys.Update(event);
    }
}

void LSystemManager::Visualize(sf::Event event) {

}

void LSystemManager::LateUpdate() {

}

void LSystemManager::Reset() {

}

void LSystemManager::TestAddLSystemVideo() {
    LSystem test1(6, "X", {{'X', "F+[[X]-X]-F[-FX]+X"}, {'F', "FF"}}, 25, sf::Vector2f(400, -800), sf::Color(0, 255, 0), 3, 3, 20);
    test1.Initialize(this->window, this->physicManager, this->flowfield);
    this->lsystems.push_back(test1);
}

void LSystemManager::TestAddLSystems() {
    //kelps
    LSystem test1(5, "X", {{'X', "F+[[X]-X]-F[-FX]+X"}, {'F', "FF"}}, 25, sf::Vector2f(300, -800), sf::Color(113,136,25), 2.8, 3, 20);
    test1.Initialize(this->window, this->physicManager, this->flowfield);
    this->lsystems.push_back(test1);

    LSystem test2(6, "X", {{'X', "F+[[X]-X]-F[-FX]+X"}, {'F', "FF"}}, 25, sf::Vector2f(500, -800), sf::Color(42,140,49), 3, 3, 20);
    test2.Initialize(this->window, this->physicManager, this->flowfield);
    this->lsystems.push_back(test2);

    LSystem test12(5, "X", {{'X', "F+[[X]-X]-F[-FX]+X"}, {'F', "FF"}}, 25, sf::Vector2f(700, -800), sf::Color(43,150,92), 2.6, 3, 20);
    test12.Initialize(this->window, this->physicManager, this->flowfield);
    this->lsystems.push_back(test12);

    //coral
    LSystem test3(5, "F", {{'F', "F[+X][-X]FX"},{'X', "FF[+X][-X]"}}, 25, sf::Vector2f(200, -800), sf::Color(224,157,158), 2.75, 5, 8);
    test3.Initialize(this->window, this->physicManager, this->flowfield);
    this->lsystems.push_back(test3);

    LSystem test4(6, "F", {{'F', "F[+X][-X]FX"},{'X', "FF[+X][-X]"}}, 25, sf::Vector2f(350, -800), sf::Color(123,202,183), 2.75, 5, 8);
    test4.Initialize(this->window, this->physicManager, this->flowfield);
    this->lsystems.push_back(test4);

    LSystem test32(4, "F", {{'F', "F[+X][-X]FX"},{'X', "FF[+X][-X]"}}, 25, sf::Vector2f(550, -800), sf::Color(247,123,77), 3, 5, 8);
    test32.Initialize(this->window, this->physicManager, this->flowfield);
    this->lsystems.push_back(test32);

    //seagrass
    LSystem test5(7, "X", {{'F', "FF"},{'X', "F[-X]+X"}}, 22.5, sf::Vector2f(150, -800), sf::Color(171,207,112), 3, 5, 5);
    test5.Initialize(this->window, this->physicManager, this->flowfield);
    this->lsystems.push_back(test5);

    LSystem test6(8, "X", {{'F', "FF"},{'X', "F[-X]+X"}}, 22.5, sf::Vector2f(400, -800), sf::Color(42,140,49), 3, 5, 5);
    test6.Initialize(this->window, this->physicManager, this->flowfield);
    this->lsystems.push_back(test6);

    LSystem test52(7, "X", {{'F', "FF"},{'X', "F[-X]+X"}}, 22.5, sf::Vector2f(600, -800), sf::Color(171,207,112), 2.5, 5, 5);
    test52.Initialize(this->window, this->physicManager, this->flowfield);
    this->lsystems.push_back(test52);
}