//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNY_HPP
#define ORIGAMISPACETIME_BUNNY_HPP

#include "SFML-Engine/Entity.hpp"

class Bunny: public Entity {
private:
    void initializeComponents();
public:
    Bunny();
    void update(double elapsed) override;
};


#endif //ORIGAMISPACETIME_BUNNY_HPP
