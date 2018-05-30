#ifndef DOORGRAPHICSCOMPONENT_HPP
#define DOORGRAPHICSCOMPONENT_HPP

#include "SFML-Engine/GraphicsComponent.hpp"
#include "Door.hpp"
//#include "DoorPhysicsComponent.hpp"

class Door;


class DoorPhysicsComponent;

class DoorGraphicsComponent: public GraphicsComponent,
                             public Handler {
private:
    sf::Sprite sprite_;
    void siblingComponentsInitialized() override;
    Door &entity_;
    DoorPhysicsComponent *physics_;
public:
    explicit DoorGraphicsComponent(Door &door);
    ~DoorGraphicsComponent() = default;
    void update(double elapsed) override;
    void handleMessage(MessageBase const &message) override;
};
#endif