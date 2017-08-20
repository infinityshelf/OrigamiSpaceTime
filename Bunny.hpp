//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNY_HPP
#define ORIGAMISPACETIME_BUNNY_HPP

#include "SFML-Engine/Entity.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"

enum BunnyState {
    BUNNY_STATE_UNDEFINED = -1,
    BUNNY_STATE_RECORDING,
    BUNNY_STATE_TELEPORTING,
    BUNNY_STATE_PLAYING
};

class Bunny: public Entity {
private:
    void initializeComponents();
    //
    // time travel
    //
    uint16_t birth_ = 0;
    uint16_t death_ = 0;
    //
    //
    //
    BunnyState state_;
    BunnyState newState_;
public:
    //
    // time travel
    //
    const BunnyState &state = state_;
    void setState(BunnyState state);

    uint16_t &birth = birth_;
    uint16_t &death = death_;

    //Bunny();
    Bunny(BunnyState state = BUNNY_STATE_RECORDING,
          uint16_t birth = 0x0000,
          uint16_t death = 0xFFFF);
    ~Bunny() override;
    void update(double elapsed) override;
};


#endif //ORIGAMISPACETIME_BUNNY_HPP
