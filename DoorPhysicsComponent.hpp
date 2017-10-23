#ifndef DOORPHYSICSCOMPONENT_HPP
#define DOORPHYSICSCOMPONENT_HPP

#include "SFML-Engine/PhysicsComponent.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"
#include "Door.hpp"
#include "DoorGraphicsComponent.hpp"

class DoorGraphicsComponent;

class DoorPhysicsComponent: public PhysicsComponent,
                            public MessageDispatcher<BOOL> {
private:
    void siblingComponentsInitialized() override;
    Door &entity_;
    bool collidingWithBunny_;
    void setCollidingWithBunny(bool colliding);
    DoorGraphicsComponent *graphics_;
public:
    const bool &collidingWithBunny = collidingWithBunny_;
    explicit DoorPhysicsComponent(Door &door);
    ~DoorPhysicsComponent() = default;
    void update(double elapsed) override;
};
#endif