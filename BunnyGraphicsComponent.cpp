//
// Created by Estevan Hernandez on 8/4/17.
//
#include <SFML/System.hpp>
#include "World.hpp"
#include "SFML-Engine/TextureManager.hpp"
#include "BunnyGraphicsComponent.hpp"
//#include "Bunny.hpp"

//const bool debug = true;

const std::string kBunnyWalk = "BunnyWalk";
const std::string kBunnyWalkFilePath = "Images/sprPlayerWalk_strip4.png";

const std::string kBunnyStand = "BunnyStand";
const std::string kBunnyStandFilePath = "Images/sprPlayermug.png";

BunnyGraphicsComponent::BunnyGraphicsComponent(Bunny &bunny): GraphicsComponent(bunny), entity_(bunny) {
    TextureManager::instance()->loadTexture(kBunnyWalk, kBunnyWalkFilePath);
    TextureManager::instance()->loadTexture(kBunnyStand, kBunnyStandFilePath);

    //sprite_.setTexture(TextureManager::instance()->getRef(kBunnyWalk));
    sprite_.setTexture(TextureManager::instance()->getRef(kBunnyStand));
    sprite_.setTextureRect(sf::IntRect(0,0,16,16));

    teleportCircle.setPointCount(100);
    maxTeleportCircle.setPointCount(100);

    teleportCircle.setFillColor(sf::Color(0xFF,0xFF,0xFF,0xFF/10));
    maxTeleportCircle.setFillColor(sf::Color(0xFF,0xFF,0xFF,0xFF/10));

}

void BunnyGraphicsComponent::siblingComponentsInitialized() {
    physicsComponent_ = entity_.getComponent<BunnyPhysicsComponent *>();
    position_ = (physicsComponent_) ? &physicsComponent_->position : new sf::Vector2f(0,0);
}

void BunnyGraphicsComponent::update(double elapsed) {
    const uint16_t &frame = World::instance()->currentFrame;

    switch(entity_.state) {
        case BUNNY_STATE_UNDEFINED: {
            break;
        }
        case BUNNY_STATE_RECORDING: {
            sprite_.setColor(sf::Color::White);
            recording();
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
            teleporting();
            break;
        }
        case BUNNY_STATE_SCRUBBING: {
            scrubbing();
            break;
        }
        case BUNNY_STATE_PLAYING: {
            sprite_.setColor(sf::Color(0x80,0xFF,0x80,0xFF));
            playing();
            break;
        }
    }

    if (false) std::cout << "BunnyGraphicsComponent::update elapsed: " <<  elapsed << std::endl;

    if (frame >= entity_.birth
        && frame <= entity_.death) { // death is 0xFFFF.
        sprite_.setPosition(position_->x, position_->y);
        sprite_.setColor(sf::Color(0xFF,0xFF,0xFF,0xFF));
        GraphicsComponent::s_window->draw(sprite_);
    } else {
        if (false) std::cout << "out of range, won't draw" << std::endl;
    }
}

BunnyGraphicsComponent::~BunnyGraphicsComponent() = default;

void BunnyGraphicsComponent::handleMessage(Message<INT> const &message) {
    std::cout << "description: "<< message.description << " message: " << message.data_ << std::endl;

}

sf::Vector2i BunnyGraphicsComponent::getMousePosition() {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*s_window);
    return mouse_pos;
}

void BunnyGraphicsComponent::playing() {

}

void BunnyGraphicsComponent::recording() {

}

void BunnyGraphicsComponent::scrubbing() {

}

void BunnyGraphicsComponent::teleporting() {
    float travelDistance = physicsComponent_->getTraveledDistance();
    float mouseDistance = getMouseDistance(physicsComponent_->getEndPosition());

    static sf::Sprite teleportingSprite = sprite_;
    static sf::Sprite endPositionSprite = sprite_;

    mouseDistance = (mouseDistance > travelDistance) ? travelDistance : mouseDistance;

    maxTeleportCircle.setPosition(physicsComponent_->getEndPosition());
    maxTeleportCircle.setRadius(travelDistance);
    maxTeleportCircle.setOrigin(travelDistance,
                                travelDistance);

    teleportCircle.setPosition(physicsComponent_->getEndPosition());
    teleportCircle.setRadius(mouseDistance);
    teleportCircle.setOrigin(mouseDistance,
                             mouseDistance);

    GraphicsComponent::s_window->draw(maxTeleportCircle);
    GraphicsComponent::s_window->draw(teleportCircle);

    endPositionSprite.setPosition(physicsComponent_->getEndPosition().x, physicsComponent_->getEndPosition().y);
    endPositionSprite.setColor(sf::Color(0xFF,0xFF,0xFF,0xFF / 4));
    GraphicsComponent::s_window->draw(endPositionSprite);
    if (getMouseDistance(physicsComponent_->getEndPosition()) <= travelDistance) {
        teleportingSprite.setPosition(getMousePosition().x / 4, getMousePosition().y / 4);
    }

    teleportingSprite.setColor(sf::Color(0xFF,0xFF,0xFF,0xFF / 4));
    GraphicsComponent::s_window->draw(teleportingSprite);
}

float BunnyGraphicsComponent::getMouseDistance(sf::Vector2f position) {
    sf::Vector2i mousePos = getMousePosition();
    return sqrtf(powf(position.x - mousePos.x / 4, 2) + powf(position.y - mousePos.y / 4, 2));
}
