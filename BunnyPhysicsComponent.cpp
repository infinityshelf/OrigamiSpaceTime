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
}

void BunnyPhysicsComponent::update(double elapsed) {
    if (debug) std::cout << elapsed << std::endl;

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
    if (debug) std::cout << message.data_ << std::endl;
}

BunnyPhysicsComponent::~BunnyPhysicsComponent() = default;
