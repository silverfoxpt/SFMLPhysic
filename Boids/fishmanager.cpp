#include "fishmanager.h"

FishManager* FishManager::instance = nullptr;

void FishManager::Initialize(sf::RenderWindow* window) {
    this->window = window;
    this->fishes.reserve(100000);
    //this->SpawnFish();
}

void FishManager::Update(sf::Event event) {
    this->Seperation();
    this->Alignment();
    this->Cohesion();
    
    this->TurnOnEdge();
    this->LimitVelocity();
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
        this->fishPhysics[i]->velocity = Math::getRandomDirectionVecWithAngleRange(1, 359) * this->minVelocity;
    }
}

void FishManager::Seperation() {
    for (int i = 0; i < (int) this->fishes.size(); i++) {
        auto fish = this->fishObjects[i];
        sf::Vector2f close = sf::Vector2f(0, 0);

        for (int j = 0;  j < (int) this->fishes.size(); j++) {
            if (i == j) {continue;}
            auto other = this->fishObjects[j];

            if (Math::Distance(fish->GetWorldPosition(), other->GetWorldPosition()) <= this->protectedRange) {
                close += fish->GetWorldPosition() - other->GetWorldPosition();
            }
        }

        //update velocity
        this->fishPhysics[i]->velocity += close * this->avoidFactor;
    }
}

void FishManager::Alignment() {
    for (int i = 0; i < (int) this->fishes.size(); i++) {
        auto fish = this->fishObjects[i];
        sf::Vector2f averageVelocity = sf::Vector2f(0, 0);
        int numNeighbor = 0;

        for (int j = 0; j < (int) this->fishes.size(); j++) {
            if (i == j) {continue;}
            auto other = this->fishObjects[j];

            if (Math::Distance(fish->GetWorldPosition(), other->GetWorldPosition()) <= this->visualRange) {
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
    for (int i = 0; i < (int) this->fishes.size(); i++) {
        auto fish = this->fishObjects[i];
        sf::Vector2f averagePos = sf::Vector2f(0, 0);
        int numNeighbor = 0;

        for (int j = 0; j < (int) this->fishes.size(); j++) {
            if (i == j) {continue;}
            auto other = this->fishObjects[j];

            if (Math::Distance(fish->GetWorldPosition(), other->GetWorldPosition()) <= this->visualRange) {
                averagePos += other->GetWorldPosition();
                numNeighbor += 1;
            }
        }
        if (numNeighbor == 0) {continue;}

        //update velocity
        averagePos /= (float) numNeighbor;
        this->fishPhysics[i]->velocity += (averagePos - fish->GetWorldPosition()) * centeringFactor;
    }
}

void FishManager::TurnOnEdge() {
    for (int i = 0; i < (int) this->fishes.size(); i++) {
        auto fish = this->fishObjects[i];
        auto phys = this->fishPhysics[i];

        auto velo = phys->velocity;
        auto pos = fish->GetWorldPosition();

        if (pos.x < this->leftMargin) {
            velo.x += turnFactor;
        } else if (pos.x > this->rightMargin) {
            velo.x -= turnFactor;
        }

        if (pos.y > this->topMargin) {
            velo.y -= turnFactor;
        } else if (pos.y < this->bottomMargin) {
            velo.y += turnFactor;
        }

        phys->velocity = velo;
    }
}

void FishManager::LimitVelocity() {
     for (int i = 0; i < (int) this->fishes.size(); i++) {
        auto phys = this->fishPhysics[i];

        auto velo = phys->velocity;
        float len = Math::Length(velo); len = Math::clamp(this->minVelocity, this->maxVelocity, len);

        phys->velocity = Math::normalizeVec(velo) * len;
    }
}