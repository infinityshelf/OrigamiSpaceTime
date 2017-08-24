//
// Created by Estevan Hernandez on 8/15/17.
//

#ifndef ORIGAMISPACETIME_BUNNYCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYCOMPONENT_HPP

#include <cinttypes>

class BunnyComponent {
protected:
    /* serialize state */
    virtual void recording() = 0;

    /* teleporting state */
    virtual void teleporting() = 0;

    /* scrub state */
    virtual void scrubbing() = 0;

    /* deserialize state */
    virtual void playing() = 0;


};


#endif //ORIGAMISPACETIME_BUNNYCOMPONENT_HPP
