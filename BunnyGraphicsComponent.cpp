//
// Created by Estevan Hernandez on 8/4/17.
//

#include "BunnyGraphicsComponent.hpp"
#include <SFML/System.hpp>
#include "SFML-Engine/TextureManager.hpp"
#include "OrigamiWorld.hpp"
#include "Bunny.hpp"

const bool debug = false;

const std::string kBunnyWalk = "BunnyWalk";
const std::string kBunnyWalkFilePath = "Images/sprPlayerWalk_strip4.png";

float BunnyGraphicsComponent::teleportationMultiplier_ = 1.0f;

BunnyGraphicsComponent::BunnyGraphicsComponent(Bunny &bunny): GraphicsComponent(bunny), entity_(bunny) {
    TextureManager::instance()->loadTexture(kBunnyWalk, kBunnyWalkFilePath);
    sprite_.setTexture(TextureManager::instance()->getRef(kBunnyWalk));
    sprite_.setTextureRect(sf::IntRect(16,0,16,16));

}

void BunnyGraphicsComponent::siblingComponentsInitialized() {
    physicsComponent_ = entity_.getComponent<BunnyPhysicsComponent *>();
    position_ = (physicsComponent_) ? &physicsComponent_->position : new sf::Vector2f(0,0);
}

void BunnyGraphicsComponent::update(double elapsed) {
    sprite_.setPosition(position_->x, position_->y);
    
    const uint16_t &currentFrame = OrigamiWorld::instance()->currentFrame;
    switch (currentFrame % 40) {
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

    if (debug) std::cout << "BunnyGraphicsComponent::update elapsed: " <<  elapsed << std::endl;
    GraphicsComponent::s_window->draw(sprite_);
}

BunnyGraphicsComponent::~BunnyGraphicsComponent() = default;

void BunnyGraphicsComponent::handleMessage(Message<INT> const &message) {
    std::cout << "description: "<< message.description << " message: " << message.data_ << std::endl;

}
