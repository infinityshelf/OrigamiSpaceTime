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

class World: //public MessageHandler<INT>,
                 //public MessageHandler<BOOL>,
                 public EntityManager,
                 public CollidableManager {
private:
    //bool teleporting_ = false;
    static World *s_instance;
    uint16_t currentFrame_;
    World();
    sf::Text timeText;
    sf::Font timeFont;
public:
    uint16_t &currentFrame = World::currentFrame_;
    static World *instance();
    void update(double elapsed, sf::RenderWindow &window);
    ~World() {
        for (Entity *entity: entities_) {
            delete entity;
        }
    }
};


#endif //ORIGAMISPACETIME_ORIGAMIWORLD_HPP
