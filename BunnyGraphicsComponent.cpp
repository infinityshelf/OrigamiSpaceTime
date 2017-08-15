//
// Created by Estevan Hernandez on 8/4/17.
//

#include "BunnyGraphicsComponent.hpp"
#include <SFML/System.hpp>
#include "SFML-Engine/TextureManager.hpp"
#include "OrigamiWorld.hpp"
#include "Bunny.hpp"
#include <cmath>

const bool debug = false;

const std::string kBunnyWalk = "BunnyWalk";
const std::string kBunnyWalkFilePath = "Images/sprPlayerWalk_strip4.png";

BunnyGraphicsComponent::BunnyGraphicsComponent(Bunny &bunny): GraphicsComponent(bunny), entity_(bunny) {
    TextureManager::instance()->loadTexture(kBunnyWalk, kBunnyWalkFilePath);
    sprite_.setTexture(TextureManager::instance()->getRef(kBunnyWalk));
    sprite_.setTextureRect(sf::IntRect(16,0,16,16));
    teleportingRadius_.setFillColor(sf::Color(0xFF,0xFF,0xFF,0xFF * 0.25f));
    teleportingRadius_.setOutlineColor(sf::Color::Cyan);
    teleportingRadius_.setPointCount(128);
    teleportingRadius_.setOutlineThickness(1.f);
}

void BunnyGraphicsComponent::siblingComponentsInitialized() {
    physicsComponent_ = entity_.getComponent<BunnyPhysicsComponent *>();
    position_ = (physicsComponent_) ? &physicsComponent_->position : new sf::Vector2f(0,0);
}

void BunnyGraphicsComponent::update(double elapsed) {
    sprite_.setPosition(position_->x, position_->y);

    sf::RenderWindow &windowRef = *GraphicsComponent::s_window;

    sf::Vector2i mouse_pos_ref = sf::Mouse::getPosition(dynamic_cast<sf::Window &>(windowRef));
    sf::Vector2f mouse_pos = windowRef.mapPixelToCoords(mouse_pos_ref);

    teleportingRadius_.setPosition(position_->x, position_->y);
    teleportingRadius_.setRadius(sqrtf(powf(mouse_pos.x - position_->x, 2) + powf(mouse_pos.y - position_->y, 2)));
    teleportingRadius_.setOrigin((teleportingRadius_.getRadius()), (teleportingRadius_.getRadius()));

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
            sprite_.setColor(sf::Color::Yellow);
            GraphicsComponent::s_window->draw(teleportingRadius_);
            break;
        }
    }
    if (debug) std::cout << "BunnyGraphicsComponent::update elapsed: " <<  elapsed << std::endl;


    if (currentFrame >= entity_.birthday
        && currentFrame <= entity_.deathday) {
        GraphicsComponent::s_window->draw(sprite_);
    } else {
        if (debug) std::cout << "BunnyInputComponent: " << this << " did not draw." << std::endl;
    }
}

BunnyGraphicsComponent::~BunnyGraphicsComponent() = default;

void BunnyGraphicsComponent::handleMessage(Message<INT> const &message) {
    std::cout << "description: "<< message.description << " message: " << message.data_ << std::endl;
}

