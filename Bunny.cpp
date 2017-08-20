//
// Created by Estevan Hernandez on 8/4/17.
//

#include "Bunny.hpp"

#include "BunnyInputComponent.hpp"
#include "BunnyPhysicsComponent.hpp"
#include "BunnyGraphicsComponent.hpp"
#include "OrigamiWorld.hpp"


//Bunny::Bunny() {
//    state_ = BUNNY_STATE_RECORDING;
//    newState_ = BUNNY_STATE_RECORDING;
//    birth_ = 0;
//    death_ = 0xFFFF;
//    initializeComponents();
//}

Bunny::Bunny(BunnyState state, uint16_t birth, uint16_t death) {
    state_ = state;
    newState_ = state;
    birth_ = birth;
    death_ = death;
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
    state_ = newState_;
}

Bunny::~Bunny() {
    for (Component *component: components) {
        delete component;
    }
}

void Bunny::setState(BunnyState state) {
    newState_ = state;

}
