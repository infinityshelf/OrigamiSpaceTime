//
// Created by Estevan Hernandez on 8/7/17.
//

#include "World.hpp"
#include "Bunny.hpp"
#include <sstream>

const bool debug = false;
const bool logTime = true;

World *World::s_instance = nullptr;
//uint16_t World::currentFrame_ = 0;

void World::update(double elapsed, sf::RenderWindow &window) {
    std::ostringstream time;
    if (logTime) {
        time    << std::setfill('0') << std::setw(2) << currentFrame / 60 / 60 << ":"
                << std::setfill('0') << std::setw(2) << currentFrame / 60 << ":"
                << std::setfill('0') << std::setw(2) << (short) ((100 / 60) * currentFrame * 1.666667) % 100;
        timeText.setString(time.str());
        std::cout << currentFrame << std::endl;
    }

    window.clear(sf::Color(0x30,0x30,0x30,0xFF));
    static double avg;
    avg = (avg + elapsed) / 2.0;
    if (debug) {
        std::cout << "elapsed: " << elapsed << std::endl;
        std::cout << "average: " << avg << std::endl;
    }
    for (Entity *entity: entities) {
        entity->update(elapsed);
    }
    
    for (sf::IntRect *rect: collidables) {
        rectShape.setPosition(sf::Vector2f(rect->left, rect->top));
        rectShape.setSize(sf::Vector2f(rect->width, rect->height));
        rectShape.setFillColor(sf::Color(0x60,0x60,0x60,0xFF));
        window.draw(rectShape);
    }

    if (logTime) window.draw(timeText);
    window.display();

    if (BunnyManager::teleporting == false) currentFrame_++;
}

World::World()  {
    currentFrame_ = 0;
    timeFont.loadFromFile("DroidSansMono.ttf");
    timeText.setFont(timeFont);
    timeText.setPosition(64,64);
    timeText.setFillColor(sf::Color::White);
    timeText.setCharacterSize(64);
}

World *World::instance() {
    if (!s_instance) {
        s_instance = new World();
    }
    return s_instance;
}