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
                BunnyManager::teleporting_ = true;
            }
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
            if (newState_ == BUNNY_STATE_RECORDING) {
                // teleport canceled
                death_ = 0xFFFF;
                BunnyManager::teleporting_ = false;
            }
            if (newState_ == BUNNY_STATE_PLAYING) {
                // teleport was successful?
                BunnyManager::teleporting_ = false;
            }
            break;
        }
        case BUNNY_STATE_SCRUBBING: {
            if (BunnyManager::teleporting == false) {
                newState_ = BUNNY_STATE_PLAYING;
            }
            break;
        }
        case BUNNY_STATE_PLAYING: {
            if (BunnyManager::teleporting == true) {
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

void Bunny::handleMessage(const MessageBase &message) {
    const Message<sf::Vector2i>  *vectorMessage = dynamic_cast<const Message<sf::Vector2i> *>(&message);
    // Message<sf::Vector2i>
    if (vectorMessage != nullptr) {
        if (vectorMessage->description == "teleported") {
            uint16_t currentFrame = World::instance()->currentFrame;
            assert(currentFrame >= birth_
                && currentFrame <= death_
                && "Trying to teleport out of range");
            newState_ = BUNNY_STATE_PLAYING;

            Bunny *newBunny;
            newBunny = new Bunny(BUNNY_STATE_RECORDING, currentFrame, 0xFFFF);
            BunnyPhysicsComponent *physics;
            physics = newBunny->getComponent<BunnyPhysicsComponent *>();

            if (physics) {
                addHandler(physics);
                dispatchMessage(*vectorMessage);
                removeHandler(physics);
            }
            World::instance()->level->addEntity(newBunny);
        }

    }

    const Message<bool> *boolMessage = dynamic_cast<const Message<bool> *>(&message);
    // Message<bool>
    if (boolMessage != nullptr) {
        if (boolMessage->description == "teleporting") {
            if (boolMessage->data == true) {
                newState_ = BUNNY_STATE_TELEPORTING;
            } else {
                newState_ = BUNNY_STATE_RECORDING;
            }
        } else if (boolMessage->description == "door_collision") {
            std::cout << "door message recieved!" << std::endl;
        }
    }
}
