#include "DoorPhysicsComponent.hpp"
#include <iostream>
#include "World.hpp"
#include "Bunny.hpp"
#include "BunnyPhysicsComponent.hpp"
#include "BunnyManager.hpp"

DoorPhysicsComponent::DoorPhysicsComponent(Door &door): PhysicsComponent(door), entity_(door) {
    /*
    sf::RectangleShape rect(sf::Vector2f(60,60));
    rect.setPosition(sf::Vector2f(60*30,60*16));
    rect.setFillColor(sf::Color(0x80,0xFF,0x80,0x20));
    */
    x_ = 60*30;
    y_ = 60*16;
    width_ = height_ = 60;

    for (Bunny *bunny: BunnyManager::instance()->bunnies) {
        addHandler(static_cast<MessageHandler<BOOL> *> (bunny));
    }

}

void DoorPhysicsComponent::siblingComponentsInitialized() {
    graphics_ = entity_.getComponent<DoorGraphicsComponent *>();
    if (graphics_) {
        addHandler(graphics_);
    }

}

void DoorPhysicsComponent::update(double elapsed) {
    static bool debug = false;
    if (debug) std::cout << "elapsed: " << elapsed << std::endl;

    /*
    check if colliding with a bunny, then send a message if so?
    */
    sf::IntRect me = sf::IntRect(x, y, width, height);
    sf::IntRect bunnyRect(0,0,0,0);
    for (Entity *entity: World::instance()->level->entities) {
        // check if the entity is a bunny
        Bunny *bunny = dynamic_cast<Bunny *>(entity);
        // if bunny is not nullptr
        if (bunny) {
            // get the physics component
            BunnyPhysicsComponent *bunnyPhysics = entity->getComponent<BunnyPhysicsComponent *>();
            
            // only if physics component is not nullptr
            if (bunnyPhysics) {
                //set bunny rect properties
                bunnyRect.left = bunnyPhysics->x;
                bunnyRect.top = bunnyPhysics->y;
                bunnyRect.width = bunnyPhysics->width;
                bunnyRect.height = bunnyPhysics->height;
                // set bool to intersection
                setCollidingWithBunny(me.intersects(bunnyRect));

                if (debug) {
                    std::cout   << " me.left: " << me.left << std::endl
                                << "  me.top: " << me.top << std::endl
                                << "me.width: " << me.width << std::endl
                                << "me.height " << me.height << std::endl;

                    std::cout   << " bunnyRect.left: " << bunnyRect.left << std::endl
                                << "  bunnyRect.top: " << bunnyRect.top << std::endl
                                << "bunnyRect.width: " << bunnyRect.width << std::endl
                                << "bunnyRect.height " << bunnyRect.height << std::endl;

                    std::cout << "interesects?" << ((collidingWithBunny) ? "YES" : "NO");
                }


            }
        }
        
    }
}

void DoorPhysicsComponent::setCollidingWithBunny(bool colliding) {
    if (colliding != collidingWithBunny_) {
        collidingWithBunny_ = colliding;
        // dispatch collided with door
        Message<BOOL> collidedMessage(colliding);
        collidedMessage.description = "door_collision";
        std::cout << "collided with bunny!, sending message" << std::endl;
        dispatchMessage(collidedMessage);
    }
}