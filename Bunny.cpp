//
// Created by Estevan Hernandez on 8/4/17.
//

#include "Bunny.hpp"

#include "BunnyInputComponent.hpp"
#include "BunnyPhysicsComponent.hpp"
#include "BunnyGraphicsComponent.hpp"
#include "OrigamiWorld.hpp"


Bunny::Bunny() {
    initializeComponents();
}

void Bunny::initializeComponents() {
    components.push_back(new BunnyInputComponent(*this));
    components.push_back(new BunnyPhysicsComponent(*this));
    components.push_back(new BunnyGraphicsComponent(*this));
    for (Component *component: components) {
        component->siblingComponentsInitialized();
    }
}

void Bunny::update(double elapsed) {
    for (Component *component: components) {
        component->update(elapsed);
    }
}

Bunny::~Bunny() {
    for (Component *component: components) {
        delete component;
    }
}
