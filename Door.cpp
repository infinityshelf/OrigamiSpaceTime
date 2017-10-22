#include "Door.hpp"
#include "DoorPhysicsComponent.hpp"
#include "DoorGraphicsComponent.hpp"

const bool debug = false;

Door::Door() {

    components.push_back(new DoorPhysicsComponent(*this));
    components.push_back(new DoorGraphicsComponent(*this));
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