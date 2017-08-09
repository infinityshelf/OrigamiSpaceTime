//
// Created by Estevan Hernandez on 8/4/17.
//

#include "BunnyPhysicsComponent.hpp"
#include "BunnyInputComponent.hpp"
#include "OrigamiWorld.hpp"
#include "Bunny.hpp"

bool debug = false;

BunnyPhysicsComponent::BunnyPhysicsComponent(Entity &entity): PhysicsComponent(entity) {
    world_ = OrigamiWorld::instance();
    x_ = 320;
    y_ = 640;

    width_ = 64;
    height_ = 64;

    boundingBox_.left = x_;
    boundingBox_.top = y_;
    boundingBox_.width = width_;
    boundingBox_.height = height_;

    runSpeed_ = 10;
    jumpSpeed_ = 23;
    maxFallSpeed_ = 23;
}

void BunnyPhysicsComponent::update(double elapsed) {
    if (debug) std::cout << elapsed << std::endl;

    boundingBox_.left = x;
    boundingBox_.top = y;

    sf::Vector2i velocity = *inputVector_;

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
    inputVector_ = &entity_.getComponent<BunnyInputComponent *>()->inputVector;
}

void BunnyPhysicsComponent::setFlags() {
    grounded_ = (placeFree(x, y + 1, boundingBox_) != nullptr);
    hittingCeiling_ = (placeFree(x, y - 1, boundingBox_) != nullptr);
    hitWallLeft_ = (placeFree(x - 1, y, boundingBox_) != nullptr);
    hitWallRight_ = (placeFree(x + 1, y, boundingBox_) != nullptr);
}
