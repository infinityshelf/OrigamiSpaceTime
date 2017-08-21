//
// Created by Estevan Hernandez on 8/4/17.
//
#include <SFML/System.hpp>
#include "GameWorld.hpp"
#include "SFML-Engine/TextureManager.hpp"
#include "BunnyGraphicsComponent.hpp"
//#include "Bunny.hpp"

const bool debug = false;

const std::string kBunnyWalk = "BunnyWalk";
const std::string kBunnyWalkFilePath = "Images/sprPlayerWalk_strip4.png";

BunnyGraphicsComponent::BunnyGraphicsComponent(Bunny &bunny): GraphicsComponent(bunny), entity_(bunny) {
    TextureManager::instance()->loadTexture(kBunnyWalk, kBunnyWalkFilePath);
    sprite_.setTexture(TextureManager::instance()->getRef(kBunnyWalk));
    sprite_.setTextureRect(sf::IntRect(16,0,16,16));

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
    sprite_.setPosition(position_->x, position_->y);
    
    const uint16_t &frame = GameWorld::instance()->currentFrame;
    switch (frame % 40) {
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

    switch(entity_.state) {
        case BUNNY_STATE_UNDEFINED: {
            break;
        }
        case BUNNY_STATE_RECORDING: {
            sprite_.setColor(sf::Color::White);
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
            break;
        }
        case BUNNY_STATE_PLAYING: {
            sprite_.setColor(sf::Color(0x80,0xFF,0x80,0xFF));
            break;
        }
    }

    if (debug) std::cout << "BunnyGraphicsComponent::update elapsed: " <<  elapsed << std::endl;
    //uint16_t index = frame - entity_.birth;
    if (frame >= entity_.birth
        && frame <= entity_.death) { // death is 0xFFFF.
        sprite_.setColor(sf::Color(0xFF,0xFF,0xFF,0xFF));
        GraphicsComponent::s_window->draw(sprite_);


    } else {
        if (debug) std::cout << "out of range, won't draw" << std::endl;
    }

    if (entity_.state == BUNNY_STATE_TELEPORTING) {

        float travelDistance = physicsComponent_->getTraveledDistance();
        float mouseDistance = getMouseDistance(physicsComponent_->getEndPosition());

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

        sprite_.setPosition(physicsComponent_->getEndPosition().x, physicsComponent_->getEndPosition().y);
        sprite_.setColor(sf::Color(0xFF,0xFF,0xFF,0xFF / 4));
        GraphicsComponent::s_window->draw(sprite_);

        sprite_.setPosition(getMousePosition().x / 4, getMousePosition().y / 4);
        sprite_.setColor(sf::Color(0xFF,0xFF,0xFF,0xFF / 4));
        GraphicsComponent::s_window->draw(sprite_);
    }

}

BunnyGraphicsComponent::~BunnyGraphicsComponent() = default;

void BunnyGraphicsComponent::handleMessage(Message<INT> const &message) {
    std::cout << "description: "<< message.description << " message: " << message.data_ << std::endl;

}

sf::Vector2i BunnyGraphicsComponent::getMousePosition() {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*s_window);
    //unsigned int x = s_window->getSize().x;
    //unsigned int y = s_window->getSize().y;

    //mouse_pos.x /= 4;
    //mouse_pos.y /= 4;
    return mouse_pos;
}

void BunnyGraphicsComponent::play() {

}

void BunnyGraphicsComponent::record() {

}

float BunnyGraphicsComponent::getMouseDistance(sf::Vector2f position) {
    sf::Vector2i mousePos = getMousePosition();
    return sqrtf(powf(position.x - mousePos.x / 4, 2) + powf(position.y - mousePos.y / 4, 2));
}
