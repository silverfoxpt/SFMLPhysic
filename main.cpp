#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "Reuseable/gameManager.h"
#include "Reuseable/randomsfml.h"
#include "Reuseable/math.h"

#include "Physic/physicmanager.h"

#include "LSys/lsysmanager.h"

#include "Perlin/flowfield.h"

#include "Reuseable/gameobjectmanager.h"

#include "Boids/fish.h"
#include "Boids/fishmanager.h"

//really early stuff initialization
Rand Randomize::rand;

//public vars
sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Physic");
sf::Clock deltaTime;

//GameobjectManager gameobjectManager;
//PhysicManager physicManager;
//LSystem lsystem;
Flowfield flowfield;

//static vars
float GameManager::windowWidth                  = window.getSize().x;
float GameManager::windowHeight                 = window.getSize().y;
float GameManager::deltaTime                    = 1/300.0;

sf::Vector2u GameManager::mainWindowSize        = sf::Vector2u(800, 800);
sf::Vector2u GameManager::originalResolution    = sf::Vector2u(1920, 1080);

//test vars
GameObject test = GameObject(10, 10);
Fish fish;

void Test() {
    //DO NOT PUT ANYTHING THAT NEEDS TO BE INITIALIZED BEFOREHAND IN THIS FUNCTION. TEST UNRELATED SIMPLE FUNCTIONS ONLY
}

void LateTest() {
    //fish.Initialize(&window);
}

void UpdateTest(sf::Event event) {
    //fish.physicPoint->AddForce(sf::Vector2f(0.01, 0));
    //fish.gameObject->GetComponent<PhysicPoint>()->AddForce(sf::Vector2f(0.01, 0));
}

void VisualizeTest(sf::Event event) {
    
}

void Initialize() {
    Test();

    GameManager::InitializeWindowWithResolution(&window);

    GameobjectManager::GetInstance()->Initialize(&window);
    PhysicManager::GetInstance()->Initialize(&window);
    flowfield.Initialize(&window);
    //lsystem.Initialize(&window, PhysicManager::GetInstance(), &flowfield);
    FishManager::GetInstance()->Initialize(&window);
    LSystemManager::GetInstance()->Initialize(&window, PhysicManager::GetInstance(), &flowfield);

    LateTest();
}

void Update(sf::Event event) {
    UpdateTest(event);

    GameobjectManager::GetInstance()->Update(event);
    PhysicManager::GetInstance()->Update(event);
    //lsystem.Update(event);
    flowfield.Update(event);
    FishManager::GetInstance()->Update(event);
    LSystemManager::GetInstance()->Update(event);
}

void Visualize(sf::Event event) {
    VisualizeTest(event);

    GameobjectManager::GetInstance()->Visualize(event);
    PhysicManager::GetInstance()->Visualize(event);
    //lsystem.Visualize(event);
    flowfield.Visualize(event);
    FishManager::GetInstance()->Visualize(event);
    LSystemManager::GetInstance()->Visualize(event);
}

void LateUpdate() {
    GameobjectManager::GetInstance()->LateUpdate();
    PhysicManager::GetInstance()->LateUpdate();
    //lsystem.LateUpdate();
    flowfield.LateUpdate();
    FishManager::GetInstance()->LateUpdate();
    LSystemManager::GetInstance()->LateUpdate();
}

void Reset() {
    GameobjectManager::GetInstance()->Reset();
    PhysicManager::GetInstance()->Reset();
    //lsystem.Reset();
    flowfield.Reset();
    FishManager::GetInstance()->Reset();
    LSystemManager::GetInstance()->Reset();
}

void MainGameLoop() {
    //ImGui::SFML::SetCurrentWindow(window);

    //polling event
    sf::Event event;
    while (window.pollEvent(event))
    {
        //ImGui::SFML::ProcessEvent(window, event);
        if (event.type == sf::Event::Closed)
            window.close();
    }
    //ImGui::SFML::Update(window, deltaTime.restart());
    window.clear(sf::Color(48,56,129));

    //doin stuff zone
    Update(event);
    Visualize(event);
    LateUpdate();

    //imguiMain.ImGuiMainLoop();

    //display
    //ImGui::SFML::Render(window);
    window.display();
}

int main()
{
    //ImGui::SFML::Init(window);
    //ImGui::GetIO().IniFilename = "imgui.ini";

    Initialize();
    window.setFramerateLimit(300);
    while (window.isOpen())
    {
        MainGameLoop();  

        std::cout << 1.0 / deltaTime.getElapsedTime().asSeconds() << '\n';
        deltaTime.restart();
    }

    //ImGui::SFML::Shutdown(window);
    return 0;
}
