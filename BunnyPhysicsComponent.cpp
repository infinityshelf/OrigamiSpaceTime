//
// Created by Estevan Hernandez on 8/4/17.
//

#include "Bunny.hpp"
#include "OrigamiWorld.hpp"
#include "BunnyPhysicsComponent.hpp"
#include "BunnyGraphicsComponent.hpp"

bool debug = false;

BunnyPhysicsComponent::BunnyPhysicsComponent(Bunny &bunny): PhysicsComponent(bunny), entity_(bunny) {
    world_ = OrigamiWorld::instance();
    x_ = 32;
    y_ = 32 * 5;

    width_ = 16;
    height_ = 16;

    boundingBox_.left = x_ - size.x / 2;
    boundingBox_.top = y_ - size.y / 2;
    boundingBox_.width = width_;
    boundingBox_.height = height_;
    runSpeed_ = 3;
    jumpSpeed_ = 8;
    maxFallSpeed_ = 5;

    hitWallRight_ = hitWallLeft_ = hittingCeiling_ = grounded_ = false;

    startPoint_ = position;
    endPoint_ = sf::Vector2f(0,0);
    distanceTraveled_ = 0;
}

void BunnyPhysicsComponent::update(double elapsed) {
    if (debug) std::cout << elapsed << std::endl;
    switch(entity_.oldState) {
        case BUNNY_STATE_UNDEFINED: {
            assert(false && "Bunny State was Undefined");
            break;
        }
        case BUNNY_STATE_RECORDING: {
            boundingBox_.left = x - size.x / 2;
            boundingBox_.top = y - size.y / 2;

            sf::Vector2f velocity = (inputVector_) ? *inputVector_ : sf::Vector2f(0,0);

            const sf::IntRect *result;

            result = placeFree(x + velocity.x, y, boundingBox_);

            if (result == nullptr) {
                x_ += velocity.x;
            } else {
                if (velocity.x > 0) {
                    x_ = result->left - boundingBox_.width;
                } else if (velocity.x < 0) {
                    x_ = result->left + result->width;
                }
            }

            result = placeFree(x , y + velocity.y, boundingBox_);

            if (result == nullptr) {
                y_ += velocity.y;
            } else {
                if (velocity.y > 0) {
                    y_ = result->top - boundingBox_.height;
                } else if (velocity.y < 0) {
                    y_ = result->top + result->height;
                }
            }
            size_t memory_in_bytes = sizeof(std::vector<sf::Vector2<uint16_t > >) + positions_.size() * sizeof(sf::Vector2<uint16_t >);
            if (debug) std::cout << "size of positions_ in bytes: " << memory_in_bytes << std::endl;
            assert(memory_in_bytes <= 1048576 && "Recording more than 1 mb : ");
            positions_.push_back( sf::Vector2<uint16_t>(position.x, position.y));
            if (positions_.size() == 1) {
                startPoint_ = position_;
            }
            endPoint_ = position;
            distanceTraveled_ = sqrtf(pow(startPoint.x - endPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
            if (debug) std::cout << "distance: " << distanceTraveled << std::endl;
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
//            sf::Vector2<uint16_t > fpos = positions_.at(positions_.size() - 1);
//            sf::Vector2f pos = sf::Vector2f(fpos.x, fpos.y);
//            position_ = pos;
//            if (pos.y == 0 && pos.x == 0) {
//                assert(false && "Teleporting position should not be 0,0");
//            }
//            break;
        }
        case BUNNY_STATE_PLAYING: {
            uint16_t currentFrame = OrigamiWorld::instance()->currentFrame;
            if (OrigamiWorld::instance()->timeFrozen) {
                size_t positionsSize = positions_.size();
                unsigned int index = positionsSize - (positionsSize * graphicsComponent_->teleportationMultiplier);
                sf::Vector2<uint16_t > pos = positions_[index];
                position_ = sf::Vector2f(pos.x, pos.y);
                if (debug) std::cout << "pos(" << pos.x << "," << pos.y << ")" <<std::endl;
            } else if (currentFrame >= entity_.birthday && currentFrame <= entity_.deathday) {
                sf::Vector2<uint16_t > uint16pos = positions_[currentFrame-1];
                position_ = sf::Vector2f(uint16pos.x, uint16pos.y);
            }
            break;
        }
        default: {
            break;
        }

    }
    setFlags();
}

void BunnyPhysicsComponent::siblingComponentsInitialized() {
    inputComponent_ = entity_.getComponent<BunnyInputComponent *>();
    graphicsComponent_ = entity_.getComponent<BunnyGraphicsComponent *>();
    inputVector_ = (inputComponent_) ? &inputComponent_->inputVector : nullptr;
}

void BunnyPhysicsComponent::setFlags() {
    grounded_ = (placeFree(x, y + 1, boundingBox_) != nullptr);
    hittingCeiling_ = (placeFree(x, y - 1, boundingBox_) != nullptr);
    hitWallLeft_ = (placeFree(x - 1, y, boundingBox_) != nullptr);
    hitWallRight_ = (placeFree(x + 1, y, boundingBox_) != nullptr);
}

void BunnyPhysicsComponent::handleMessage(Message<INT> const &message) {
    if (message.description == "teleported") {
        Bunny *player = new Bunny(BUNNY_STATE_RECORDING);
        BunnyPhysicsComponent *physics = player->getComponent<BunnyPhysicsComponent *>();
        if (physics) {
            physics->position_ = BunnyGraphicsComponent::getMousePosition();
        }
        OrigamiWorld::instance()->addEntity(player);
    }
}

BunnyPhysicsComponent::~BunnyPhysicsComponent() = default;
