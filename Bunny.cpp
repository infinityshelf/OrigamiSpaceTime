//
// Created by Estevan Hernandez on 8/4/17.
//

#include "Bunny.hpp"

#include "BunnyInputComponent.hpp"
#include "BunnyPhysicsComponent.hpp"
#include "BunnyGraphicsComponent.hpp"
#include "World.hpp"

Bunny::Bunny(BunnyState state, uint16_t birth, uint16_t death) {
    state_ = state;
    newState_ = state;
    birth_ = birth;
    death_ = death;
    initializeComponents();
    BunnyManager::instance()->addBunny(this);

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
    switch (state_) {
        case BUNNY_STATE_RECORDING: {
            if (newState_ == BUNNY_STATE_TELEPORTING) {
                // player wants to teleport
                death_ = World::instance()->currentFrame;
            }
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
            if (newState_ == BUNNY_STATE_RECORDING) {
                // teleport canceled
                death_ = 0xFFFF;
            }
            if (newState_ == BUNNY_STATE_PLAYING) {
                // teleport was successful?
            }
            break;
        }
        case BUNNY_STATE_SCRUBBING: {
            if (BunnyManager::instance()->isABunnyTeleporting() == false) {
                newState_ = BUNNY_STATE_PLAYING;
            }
            break;
        }
        case BUNNY_STATE_PLAYING: {
            if (BunnyManager::instance()->isABunnyTeleporting() == true) {
                newState_ = BUNNY_STATE_SCRUBBING;
            }
            break;
        }
        case BUNNY_STATE_UNDEFINED: {
            assert(false);
        }
    }
    state_ = newState_;
}

Bunny::~Bunny() {
    for (Component *component: components) {
        delete component;
    }
}

void Bunny::handleMessage(const Message<INT> &message) {
    if (message.description == "teleported") {
        assert(message.data_ >= birth_ && message.data_ <= death_);
        newState_ = BUNNY_STATE_PLAYING;

        Bunny *newBunny = new Bunny(BUNNY_STATE_RECORDING, message.data_, 0xFFFF);
        World::instance()->addEntity(newBunny);
    }
}

void Bunny::handleMessage(const Message<BOOL> &message) {
    if (message.description == "teleporting") {
        if (message.data_ == true) {
            newState_ = BUNNY_STATE_TELEPORTING;
        } else {
            newState_ = BUNNY_STATE_RECORDING;
        }
    }
}
