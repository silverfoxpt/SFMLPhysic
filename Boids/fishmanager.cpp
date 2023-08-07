#include "fishmanager.h"

void FishManager::Initialize(sf::RenderWindow* window) {
    this->window = window;
    this->fishes.reserve(100000);
    this->SpawnFish();
}

void FishManager::Update(sf::Event event) {
    this->Seperation();
    this->Alignment();
    this->Cohesion();
}

void FishManager::Visualize(sf::Event event) {

}

void FishManager::LateUpdate() {

}

void FishManager::Reset() {
    this->fishes.clear();
    this->fishPhysics.clear();
    this->fishObjects.clear();
}

void FishManager::SpawnFish() {
    for (int i = 0; i < this->numFish; i++) {
        Fish newFish = Fish();
        newFish.Initialize(this->window);

        this->fishes.push_back(newFish);
        this->fishObjects.push_back(this->fishes[i].gameObject);
        this->fishPhysics.push_back(this->fishes[i].gameObject->GetComponent<PhysicPoint>());

        //start veloctity -> test
        this->fishPhysics[i]->velocity = sf::Vector2f(0, 1) * this->minVelocity;
    }
}

void FishManager::Seperation() {
    for (int i = 0; i < this->fishes.size(); i++) {
        auto fish = this->fishObjects[i];
        sf::Vector2f close = sf::Vector2f(0, 0);

        for (int j = 0; j < this->fishes.size(); j++) {
            if (i == j) {continue;}
            auto other = this->fishObjects[j];

            if (Math::Distance(fish->GetPosition(), other->GetPosition()) <= this->protectedRange) {
                close += fish->GetPosition() - other->GetPosition();
            }
        }

        //update velocity
        this->fishPhysics[i]->velocity += close * this->avoidFactor;
    }
}

void FishManager::Alignment() {
    for (int i = 0; i < this->fishes.size(); i++) {
        auto fish = this->fishObjects[i];
        sf::Vector2f averageVelocity = sf::Vector2f(0, 0);
        int numNeighbor = 0;

        for (int j = 0; j < this->fishes.size(); j++) {
            if (i == j) {continue;}
            auto other = this->fishObjects[j];

            if (Math::Distance(fish->GetPosition(), other->GetPosition()) <= this->visualRange) {
                averageVelocity += this->fishPhysics[j]->velocity;
                numNeighbor += 1;
            }
        }
        if (numNeighbor == 0) {continue;}

        //update velocity
        averageVelocity /= (float) numNeighbor;
        this->fishPhysics[i]->velocity += (averageVelocity - this->fishPhysics[i]->velocity) * matchingFactor;
    }
}

void FishManager::Cohesion() {
    for (int i = 0; i < this->fishes.size(); i++) {
        auto fish = this->fishObjects[i];
        sf::Vector2f averagePos = sf::Vector2f(0, 0);
        int numNeighbor = 0;

        for (int j = 0; j < this->fishes.size(); j++) {
            if (i == j) {continue;}
            auto other = this->fishObjects[j];

            if (Math::Distance(fish->GetPosition(), other->GetPosition()) <= this->visualRange) {
                averagePos += other->GetPosition();
                numNeighbor += 1;
            }
        }
        if (numNeighbor == 0) {continue;}

        //update velocity
        averagePos /= (float) numNeighbor;
        this->fishPhysics[i]->velocity += (averagePos - fish->GetPosition()) * centeringFactor;
    }
}