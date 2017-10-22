//
// Created by Estevan Hernandez on 8/7/17.
//

#ifndef ORIGAMISPACETIME_ORIGAMIWORLD_HPP
#define ORIGAMISPACETIME_ORIGAMIWORLD_HPP

//#include "SFML-Engine/World.hpp"
#include "SFML-Engine/EntityManager.hpp"
#include "SFML-Engine/CollidableManager.hpp"
#include <iomanip>
#include "SFML-Engine/ComponentMessaging.hpp"
#include "Level.hpp"

class World {
private:
    //bool teleporting_ = false;
    static World *s_instance;
    uint16_t currentFrame_;
    World();
    
    sf::Text timeText;
    sf::Font timeFont;
public:
    Level *level;
    uint16_t &currentFrame = World::currentFrame_;
    static World *instance();
    void update(double elapsed, sf::RenderWindow &window);
    ~World() {
        // for (Entity *entity: entities_) {
        //     delete entity;
        // }
    }
};


#endif //ORIGAMISPACETIME_ORIGAMIWORLD_HPP
