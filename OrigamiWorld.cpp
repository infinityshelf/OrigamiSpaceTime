//
// Created by Estevan Hernandez on 8/7/17.
//

#include "OrigamiWorld.hpp"
#include "Bunny.hpp"

const bool debug = false;
const bool logTime = false;

OrigamiWorld *OrigamiWorld::s_instance = nullptr;
//uint16_t OrigamiWorld::currentFrame_ = 0;

void OrigamiWorld::update(double elapsed, sf::RenderWindow &window) {
    if (currentFrame % 60 == 0 && logTime) {
        std::cout << std::setfill('0') << std::setw(2) << currentFrame / 60 / 60 << ":"<< std::setfill('0') << std::setw(2) << currentFrame / 60 << std::endl;
    }
    World::update(elapsed, window);
    if (teleporting_ == false) currentFrame_++;
}

OrigamiWorld::OrigamiWorld()  {
    currentFrame_ = 0;
}

OrigamiWorld *OrigamiWorld::instance() {
    if (!s_instance) {
        s_instance = new OrigamiWorld();
    }
    return s_instance;
}

void OrigamiWorld::handleMessage(Message<INT> const &message) {
    if (debug) std::cout << message.description << " " << message.data_ << std::endl;
    if (message.description == "teleported") {
        currentFrame_ = message.data_;
        teleporting_ = false;
        //Bunny *bunny = new Bunny(BUNNY_STATE_RECORDING);
        //addEntity(bunny);
    }

    //std::cout << "entities count: " << entities_.size() << std::endl;
}

void OrigamiWorld::handleMessage(Message<BOOL> const &message) {
    if (debug) std::cout << message.description << " " << message.data_ << std::endl;
    if (message.description == "teleport") {
        teleporting_ = message.data_;
    }

    //std::cout << "entities count: " << entities_.size() << std::endl;
}
