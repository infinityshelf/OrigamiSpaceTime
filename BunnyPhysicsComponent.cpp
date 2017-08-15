//
// Created by Estevan Hernandez on 8/4/17.
//

#include "Bunny.hpp"
#include "OrigamiWorld.hpp"
#include "BunnyPhysicsComponent.hpp"


bool debug = false;

BunnyPhysicsComponent::BunnyPhysicsComponent(Bunny &bunny): PhysicsComponent(bunny), entity_(bunny) {
    world_ = OrigamiWorld::instance();
    x_ = 32;
    y_ = 32;

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
    endPoint_ = sf::Vector2i(0,0);
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

            sf::Vector2i velocity = (inputVector_) ? *inputVector_ : sf::Vector2i(0,0);

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
            positions_.push_back(position);
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
            sf::Vector2i pos = positions_.at(positions_.size() - 1);
            position_ = pos;
            if (pos.y == 0 && pos.x == 0) {
                assert(false && "Teleporting position should not be 0,0");
            }
            break;
        }
        case BUNNY_STATE_PLAYING: {
            uint16_t currentFrame = OrigamiWorld::instance()->currentFrame;
            if (currentFrame >= entity_.birthday && currentFrame <= entity_.deathday) {
                position_ = positions_[currentFrame-1];
            } else {
                std::cout << "I don't even know" << std::endl;
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
        endPoint_ = position_;
    }
}

BunnyPhysicsComponent::~BunnyPhysicsComponent() = default;
