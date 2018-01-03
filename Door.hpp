#ifndef DOOR_HPP
#define DOOR_HPP
#include <cinttypes>
#include "SFML-Engine/Entity.hpp"
#include "DoorPhysicsComponent.hpp"
#include "DoorGraphicsComponent.hpp"

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
class Door : public Entity {
private:
public:
    //Door();
    Door(sf::Vector2f position = sf::Vector2f(0,0));
    ~Door();
    void update(double elapsed) override;

    uint16_t x;
    uint16_t y;

    DoorPhysicsComponent* physics;
    DoorGraphicsComponent* graphics;
};
#endif