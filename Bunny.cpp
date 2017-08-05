//
// Created by Estevan Hernandez on 8/4/17.
//

#include "Bunny.hpp"

#include "BunnyInputComponent.hpp"
#include "BunnyPhysicsComponent.hpp"
#include "BunnyGraphicsComponent.hpp"


Bunny::Bunny() {
    components.push_back(new BunnyInputComponent(*this));
    components.push_back(new BunnyPhysicsComponent(*this));
    components.push_back(new BunnyGraphicsComponent(*this));
    if (components.size() > 1) {
        for (Component *component: components) {
            component->siblingComponentsInitialized();
        }
    }

}

void Bunny::update(double elapsed) {
    for (Component *component: components) {
        component->update(elapsed);
    }

}