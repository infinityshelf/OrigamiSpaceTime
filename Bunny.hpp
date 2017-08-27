//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNY_HPP
#define ORIGAMISPACETIME_BUNNY_HPP

#include "SFML-Engine/Entity.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"
#include "BunnyManager.hpp"

enum BunnyState {
    BUNNY_STATE_UNDEFINED = -1,
    BUNNY_STATE_RECORDING,
    BUNNY_STATE_TELEPORTING,
    BUNNY_STATE_SCRUBBING,
    BUNNY_STATE_PLAYING
};

class Bunny: public Entity,
             //public MessageHandler<INT>,
             public MessageHandler<BOOL>,
             public MessageHandler<VECTOR2i>,
             public MessageDispatcher<VECTOR2i> {
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
    //void setState(BunnyState state);
    //void handleMessage(const Message<INT> &message) override;
    void handleMessage(const Message<BOOL> &message) override;
    void handleMessage(const Message<VECTOR2i> &message) override;
public:
    //
    // time travel
    //
    const BunnyState &state = state_;
    //void setState(BunnyState state);

    const uint16_t &birth = birth_;
    const uint16_t &death = death_;
    static bool teleporting;

    //Bunny();
    Bunny(BunnyState state = BUNNY_STATE_RECORDING,
          uint16_t birth = 0x0000,
          uint16_t death = 0xFFFF);
    ~Bunny() override;
    void update(double elapsed) override;
};


#endif //ORIGAMISPACETIME_BUNNY_HPP
