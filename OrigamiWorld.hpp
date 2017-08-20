//
// Created by Estevan Hernandez on 8/7/17.
//

#ifndef ORIGAMISPACETIME_ORIGAMIWORLD_HPP
#define ORIGAMISPACETIME_ORIGAMIWORLD_HPP

#include "SFML-Engine/World.hpp"
#include <iomanip>
#include "SFML-Engine/ComponentMessaging.hpp"

class OrigamiWorld: public World,
                    public MessageHandler<INT>,
                    public MessageHandler<BOOL> {
private:
    bool teleporting_ = false;
    static OrigamiWorld *s_instance;
    uint16_t currentFrame_;
    OrigamiWorld();
    ~OrigamiWorld() override {
        for (Entity *entity: entities_) {
            delete entity;
        }
    }
public:
    //const uint16_t &currentFrame = OrigamiWorld::currentFrame_;
    const bool & teleporting = teleporting_;
    uint16_t &currentFrame = OrigamiWorld::currentFrame_;
    //void setCurrentFrame(uint16_t frame) { currentFrame_ = frame; }
    static OrigamiWorld *instance();
    void update(double elapsed, sf::RenderWindow &window);
    void handleMessage(Message<INT> const &message) override;
    void handleMessage(Message<BOOL> const &message) override;
};


#endif //ORIGAMISPACETIME_ORIGAMIWORLD_HPP
