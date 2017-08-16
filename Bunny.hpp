//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNY_HPP
#define ORIGAMISPACETIME_BUNNY_HPP

#include "SFML-Engine/Entity.hpp"

//enum BunnyState {
//    BUNNY_STATE_UNDEFINED = -1,
//    BUNNY_STATE_RECORDING,
//    BUNNY_STATE_TELEPORTING,
//    BUNNY_STATE_PLAYING
//};

class Bunny: public Entity {
private:
    void initializeComponents();
public:
    Bunny();
    ~Bunny() override;
    void update(double elapsed) override;
};


#endif //ORIGAMISPACETIME_BUNNY_HPP
