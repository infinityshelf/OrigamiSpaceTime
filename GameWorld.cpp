//
// Created by Estevan Hernandez on 8/7/17.
//

#include "GameWorld.hpp"
#include "Bunny.hpp"

const bool debug = false;
const bool logTime = false;

GameWorld *GameWorld::s_instance = nullptr;
//uint16_t GameWorld::currentFrame_ = 0;

void GameWorld::update(double elapsed, sf::RenderWindow &window) {
    if (currentFrame % 60 == 0 && logTime) {
        std::cout << std::setfill('0') << std::setw(2) << currentFrame / 60 / 60 << ":"<< std::setfill('0') << std::setw(2) << currentFrame / 60 << std::endl;
    }
    World::update(elapsed, window);
    if (teleporting_ == false) currentFrame_++;
}

GameWorld::GameWorld()  {
    currentFrame_ = 0;
}

GameWorld *GameWorld::instance() {
    if (!s_instance) {
        s_instance = new GameWorld();
    }
    return s_instance;
}

void GameWorld::handleMessage(Message<INT> const &message) {
    if (debug) std::cout << message.description << " " << message.data_ << std::endl;
    if (message.description == "teleported") {
        currentFrame_ = message.data_;
        teleporting_ = false;
        //Bunny *bunny = new Bunny(BUNNY_STATE_RECORDING);
        //addEntity(bunny);
    }

    //std::cout << "entities count: " << entities_.size() << std::endl;
}

void GameWorld::handleMessage(Message<BOOL> const &message) {
    if (debug) std::cout << message.description << " " << message.data_ << std::endl;
    if (message.description == "teleport") {
        teleporting_ = message.data_;
    }

    //std::cout << "entities count: " << entities_.size() << std::endl;
}
