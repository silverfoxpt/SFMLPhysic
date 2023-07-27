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

#include "LSys/lsystem.h"

//really early stuff initialization
Rand Randomize::rand;

//public vars
sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Physic");
sf::Clock deltaTime;

PhysicManager manager;
LSystem lsystem;

//static vars
float GameManager::windowWidth                  = window.getSize().x;
float GameManager::windowHeight                 = window.getSize().y;
float GameManager::deltaTime                    = 1/300.0;

sf::Vector2u GameManager::mainWindowSize        = sf::Vector2u(800, 800);
sf::Vector2u GameManager::originalResolution    = sf::Vector2u(1920, 1080);

void Test() {
    
}

void UpdateTest(sf::Event event) {
    
}

void VisualizeTest(sf::Event event) {
    
}

void Initialize() {
    Test();

    GameManager::InitializeWindowWithResolution(&window);
    manager.Initialize(&window);
    lsystem.Initialize(&window);
}

void Update(sf::Event event) {
    UpdateTest(event);

    manager.Update(event);
    lsystem.Update(event);
}

void Visualize(sf::Event event) {
    VisualizeTest(event);

    manager.Visualize(event);
    lsystem.Visualize(event);
}

void LateUpdate() {
    manager.LateUpdate();
    lsystem.LateUpdate();
}

void Reset() {
    manager.Reset();
    lsystem.Reset();
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
    window.clear();

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
    while (window.isOpen())
    {
        MainGameLoop();    
    }

    //ImGui::SFML::Shutdown(window);
    return 0;
}