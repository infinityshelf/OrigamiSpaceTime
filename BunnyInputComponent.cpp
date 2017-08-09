//
// Created by Estevan Hernandez on 8/4/17.
//

#include "BunnyInputComponent.hpp"
#include "BunnyPhysicsComponent.hpp"
#include "OrigamiWorld.hpp"
const bool debug = false;

BunnyInputComponent::BunnyInputComponent(Entity &entity) : InputComponent(entity) {

}

void BunnyInputComponent::update(double elapsed) {

    if (debug) std::cout << "Entity: " << &entity_ << " PlayerInputComponent::update elapsed: " << elapsed << std::endl;
    if (debug) Input::inputStruct.log();
    //x_ = 0;
    if (input.right) {
        x_ += 3;
        if (x_ > runSpeed_) {
            x_ = runSpeed_;
        }

    }
    if (input.left) {
        x_ -= 3;
        if (x_ < -runSpeed_) {
            x_ = -runSpeed_;
        }
    }

    if (input.upPressed && *grounded_) {
        y_ -= jumpSpeed_;
    }

    if (*grounded_ == true) {
        y_ = 0;
        if (input.upPressed) {
            y_ -= jumpSpeed_;
        }
    } else {
        y_ += 1;
    }

    if (*hittingCeiling_ == true && y_ < 0) {
        y_ = 0;
    }

    if (*hitWallLeft_ && x_ < 0) {
        x_ = 0;
    }

    if (*hitWallRight_ && x_ > 0) {
        x_ = 0;
    }

    if (input.right == false && input.left == false) {
        x_ *= 0.5;
    }
    if (input.leftMouseButtonPressed) {
        if (OrigamiWorld::instance()->teleporting == false) {
            OrigamiWorld::instance()->setTeleporting(true);
        } else {
            OrigamiWorld::instance()->setTeleporting(false);
        }
    }
}

void BunnyInputComponent::siblingComponentsInitialized() {
    BunnyPhysicsComponent &physics = *entity_.getComponent<BunnyPhysicsComponent *>();

    runSpeed_ = physics.runSpeed;
    jumpSpeed_ = physics.jumpSpeed;
    grounded_ = &physics.grounded;
    hittingCeiling_ = &physics.hittingCeiling;
    hitWallLeft_ = &physics.hitWallLeft;
    hitWallRight_ = &physics.hitWallRight;

}
