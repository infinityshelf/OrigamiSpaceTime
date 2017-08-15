//
// Created by Estevan Hernandez on 8/4/17.
//

#include "Bunny.hpp"

#include "BunnyInputComponent.hpp"
#include "BunnyPhysicsComponent.hpp"
#include "BunnyGraphicsComponent.hpp"
#include "OrigamiWorld.hpp"


Bunny::Bunny(BunnyState state) {
    setState(state);
    oldState_ = state;
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
    oldState_ = state_;
}

Bunny::~Bunny() {
    for (Component *component: components) {
        delete component;
    }
}

void Bunny::setState(BunnyState state = BUNNY_STATE_UNDEFINED) {
    state_ = state;
    switch(state_) {
        case BUNNY_STATE_UNDEFINED: {
            assert(false && "Bunny State Undefined");
            break;
        };
        case BUNNY_STATE_RECORDING: {
            OrigamiWorld::instance()->setTimeFrozen(false);
            birthday_ = OrigamiWorld::instance()->currentFrame;
            deathday_ = 0xFFFF;
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
            OrigamiWorld::instance()->setTimeFrozen(true);
            deathday_ = OrigamiWorld::instance()->currentFrame;
            break;
        }
        case BUNNY_STATE_PLAYING: {
            OrigamiWorld::instance()->setTimeFrozen(false);
            break;
        }
    }
}
