#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <cinttypes>
#include "SFML-Engine/Entity.hpp"

// class DoorComponent {
// protected:
//     /* serialize state */
//     virtual void recording() = 0;

//     /* teleporting state */
//     virtual void teleporting() = 0;

//     /* scrub state */
//     virtual void scrubbing() = 0;

//     /* deserialize state */
//     virtual void playing() = 0;
// };

//////////////////////////////////////////////////////////////////////////////////////////
class Button : public Entity {
private:
    Door *door_;
public:
    void update(double elapsed) override;

    uint16_t x;
    uint16_t y;
};
#endif