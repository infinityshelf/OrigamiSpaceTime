#include "Door.hpp"

const bool debug = false;

Door::Door(sf::Vector2f position) {
    physics = new DoorPhysicsComponent(*this, position);
    graphics = new DoorGraphicsComponent(*this);
    components.push_back(physics);
    components.push_back(graphics);
    for (Component *component: components) {
        component->siblingComponentsInitialized();
    }
}

Door::~Door() {
    
}

void Door::update(double elapsed) {
    for (Component *component: components) {
        component->update(elapsed);
    }
    if (debug) std::cout << "door updated!: -- " <<  elapsed << std::endl;
}