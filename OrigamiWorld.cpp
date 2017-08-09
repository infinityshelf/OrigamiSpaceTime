//
// Created by Estevan Hernandez on 8/7/17.
//

#include "OrigamiWorld.hpp"

OrigamiWorld *OrigamiWorld::s_instance = nullptr;

void OrigamiWorld::update(double elapsed, sf::RenderWindow &window) {
    if (teleporting == false) currentFrame++;
    if (currentFrame % 60 == 0) {
        std::cout << std::setfill('0') << std::setw(2) << currentFrame / 60 / 60 << ":"<< std::setfill('0') << std::setw(2) << currentFrame / 60 << std::endl;
    }
    World::update(elapsed, window);
}

OrigamiWorld::OrigamiWorld() {
    frames = 0;
    currentFrame = 0;
}

void OrigamiWorld::setTeleporting(bool teleporting) {
    teleporting_ = teleporting;
}

OrigamiWorld *OrigamiWorld::instance() {
    if (!s_instance) {
        s_instance = new OrigamiWorld();
    }
    return s_instance;
}
