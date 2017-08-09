//
// Created by Estevan Hernandez on 8/7/17.
//

#ifndef ORIGAMISPACETIME_ORIGAMIWORLD_HPP
#define ORIGAMISPACETIME_ORIGAMIWORLD_HPP

#include "SFML-Engine/World.hpp"
#include <iomanip>
#include "SFML-Engine/ComponentMessaging.hpp"

class OrigamiWorld: public World, public MessageDispatcher<INT> {
private:
    bool teleporting_;
    static OrigamiWorld *s_instance;
    uint16_t currentFrame;
    uint16_t frames;
    OrigamiWorld();
public:
    const bool &teleporting = teleporting_;
    void setTeleporting(bool teleporting);
    static OrigamiWorld *instance();
    void update(double elapsed, sf::RenderWindow &window);
};


#endif //ORIGAMISPACETIME_ORIGAMIWORLD_HPP
