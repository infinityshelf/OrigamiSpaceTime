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

    teleportingRadius_.setFillColor(sf::Color(0xFF,0x00,0x00,0xFF * 0.125f));
    maxTeleportRadius_.setOutlineColor(sf::Color::Red);
    maxTeleportRadius_.setFillColor(sf::Color(0xFF,0x00,0x00,0xFF * 0.125f));
    maxTeleportRadius_.setOutlineThickness(1.f);

    maxTeleportRadius_.setPointCount(128);
    teleportingRadius_.setPointCount(128);

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
    switch (entity_.oldState) {
        case BUNNY_STATE_UNDEFINED: {
            assert(false && "Bunny State Was Undefined");
            break;
        }
        case BUNNY_STATE_RECORDING: {
            sprite_.setColor(sf::Color::Red);
            sprite_.setColor(sf::Color(0xFF,0xA0,0xA0,0xFF));
            break;
        }
        case BUNNY_STATE_PLAYING: {
            sprite_.setColor(sf::Color::Green);
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
            sprite_.setColor(sf::Color(0xFF,0xFF,0xA0,0xFF));

            teleportingRadius_.setPosition(physicsComponent_->endPoint.x, physicsComponent_->endPoint.y);
            //teleportingRadius_.setPosition(position_->x, position_->y);
            teleportingRadius_.setRadius(getMouseDistance());
            teleportingRadius_.setOrigin(
                    (teleportingRadius_.getRadius()) - physicsComponent_->size.x / 2,
                    (teleportingRadius_.getRadius()) - physicsComponent_->size.y / 2
            );

            //maxTeleportRadius_.setPosition(position_->x, position_->y);
            maxTeleportRadius_.setPosition(physicsComponent_->endPoint.x, physicsComponent_->endPoint.y);
            maxTeleportRadius_.setRadius(physicsComponent_->distanceTraveled);
            maxTeleportRadius_.setOrigin(
                    physicsComponent_->distanceTraveled - physicsComponent_->size.x / 2,
                    physicsComponent_->distanceTraveled - physicsComponent_->size.y / 2
            );
            shouldTeleport_ = teleportingRadius_.getRadius() <= maxTeleportRadius_.getRadius();
            teleportationMultiplier_ = teleportingRadius_.getRadius() / maxTeleportRadius_.getRadius();
            if (teleportationMultiplier_ > 1.0f) {
                teleportationMultiplier_ = 1.0f;
            }
            sf::RenderStates state = sf::RenderStates();
            state.blendMode = sf::BlendAdd;
            if (getMouseDistance() <= physicsComponent_->distanceTraveled) {
                GraphicsComponent::s_window->draw(teleportingRadius_, state);
            }

            GraphicsComponent::s_window->draw(maxTeleportRadius_, state);
            break;
        }
    }
    if (debug) std::cout << "BunnyGraphicsComponent::update elapsed: " <<  elapsed << std::endl;


    if (currentFrame >= entity_.birthday
        && currentFrame <= entity_.deathday) {
        GraphicsComponent::s_window->draw(sprite_);
    } else {
        //if (true) std::cout << "BunnyInputComponent: " << this << " did not draw." << std::endl;
        //GraphicsComponent::s_window->draw(sprite_);
    }
}

BunnyGraphicsComponent::~BunnyGraphicsComponent() = default;

void BunnyGraphicsComponent::handleMessage(Message<INT> const &message) {
    std::cout << "description: "<< message.description << " message: " << message.data_ << std::endl;

}

float BunnyGraphicsComponent::getMouseDistance() {
    sf::Vector2f mouse_pos = BunnyGraphicsComponent::getMousePosition();
    return sqrtf(powf(mouse_pos.x - physicsComponent_->endPoint.x, 2) + powf(mouse_pos.y - physicsComponent_->endPoint.y, 2));
}

