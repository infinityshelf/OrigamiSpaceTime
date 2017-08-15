//
// Created by Estevan Hernandez on 8/7/17.
//

#ifndef ORIGAMISPACETIME_ORIGAMIWORLD_HPP
#define ORIGAMISPACETIME_ORIGAMIWORLD_HPP

#include "SFML-Engine/World.hpp"
#include <iomanip>
#include "SFML-Engine/ComponentMessaging.hpp"

class OrigamiWorld: public World, public MessageHandler<INT> {
private:
    bool timeFrozen_;
    static OrigamiWorld *s_instance;
    uint16_t currentFrame_;
    uint16_t frames;
    OrigamiWorld();
    ~OrigamiWorld() override {
        for (Entity *entity: entities_) {
            delete entity;
        }
    }
public:
    const bool &timeFrozen = timeFrozen_;
    void setTimeFrozen(bool frozen) {
        timeFrozen_ = frozen;
    }
    const uint16_t &currentFrame = OrigamiWorld::currentFrame_;
    static OrigamiWorld *instance();
    void update(double elapsed, sf::RenderWindow &window);
    void handleMessage(Message<INT> const &message) override;
};


#endif //ORIGAMISPACETIME_ORIGAMIWORLD_HPP
