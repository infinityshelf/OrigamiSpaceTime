//
// Created by Estevan Hernandez on 8/15/17.
//

#ifndef ORIGAMISPACETIME_BUNNYCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYCOMPONENT_HPP

#include <cinttypes>

class BunnyComponent {
protected:
    /* serialize state */
    virtual void record() {};
    /* deserialize state */
    //virtual void play(uint16_t frame) = 0;
    virtual void play() {};
};


#endif //ORIGAMISPACETIME_BUNNYCOMPONENT_HPP
