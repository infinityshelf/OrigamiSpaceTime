//
// Created by Estevan Hernandez on 8/7/17.
//

#ifndef ORIGAMISPACETIME_ORIGAMIWORLD_HPP
#define ORIGAMISPACETIME_ORIGAMIWORLD_HPP

#include "SFML-Engine/World.hpp"
#include <iomanip>
#include "SFML-Engine/ComponentMessaging.hpp"

class GameWorld: public World,
                    public MessageHandler<INT>,
                    public MessageHandler<BOOL> {
private:
    bool teleporting_ = false;
    static GameWorld *s_instance;
    uint16_t currentFrame_;
    GameWorld();
    ~GameWorld() override {
        for (Entity *entity: entities_) {
            delete entity;
        }
    }
public:
    //const uint16_t &currentFrame = GameWorld::currentFrame_;
    const bool & teleporting = teleporting_;
    uint16_t &currentFrame = GameWorld::currentFrame_;
    //void setCurrentFrame(uint16_t frame) { currentFrame_ = frame; }
    static GameWorld *instance();
    void update(double elapsed, sf::RenderWindow &window);
    void handleMessage(Message<INT> const &message) override;
    void handleMessage(Message<BOOL> const &message) override;
};


#endif //ORIGAMISPACETIME_ORIGAMIWORLD_HPP
