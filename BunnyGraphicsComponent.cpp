//
// Created by Estevan Hernandez on 8/4/17.
//

#include "BunnyGraphicsComponent.hpp"
#include <SFML/System.hpp>
#include "BunnyPhysicsComponent.hpp"
#include "SFML-Engine/TextureManager.hpp"
#include "OrigamiWorld.hpp"

const bool debug = false;

const std::string kBunnyWalk = "BunnyWalk";
const std::string kBunnyWalkFilePath = "Images/sprPlayerWalk_strip4.png";

BunnyGraphicsComponent::BunnyGraphicsComponent(Entity &entity): GraphicsComponent(entity) {
    TextureManager::instance()->loadTexture(kBunnyWalk, kBunnyWalkFilePath);
    sprite_.setTexture(TextureManager::instance()->getRef(kBunnyWalk));
    sprite_.setTextureRect(sf::IntRect(16,0,16,16));
    sprite_.setScale(4,4);

}

void BunnyGraphicsComponent::siblingComponentsInitialized() {
    BunnyPhysicsComponent &physics = *entity_.getComponent<BunnyPhysicsComponent *>();
    position_ = &physics.position;
}

void BunnyGraphicsComponent::update(double elapsed) {
    static uint8_t off;
    off++;
    off %= 40;
    switch (off) {
        case 0: {
            sprite_.setTextureRect(sf::IntRect(0,0,16,16));
            break;
        }
        case 10: {
            sprite_.setTextureRect(sf::IntRect(16,0,16,16));
            break;
        }
        case 20: {
            sprite_.setTextureRect(sf::IntRect(32,0,16,16));
            break;
        }
        case 30: {
            sprite_.setTextureRect(sf::IntRect(48,0,16,16));
            break;
        }
        default:
            break;

    }
    if (OrigamiWorld::instance()->teleporting) {
        sprite_.setColor(sf::Color::Blue);
    } else {
        sprite_.setColor(sf::Color::White);
    }
    if (debug) std::cout << "BunnyGraphicsComponent::update elapsed: " <<  elapsed << std::endl;
    sprite_.setPosition(position_->x, position_->y);
    GraphicsComponent::s_window->draw(sprite_);
}

