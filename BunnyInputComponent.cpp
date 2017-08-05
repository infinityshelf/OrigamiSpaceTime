//
// Created by Estevan Hernandez on 8/4/17.
//

#include "BunnyInputComponent.hpp"
#include "BunnyPhysicsComponent.hpp"
const bool debug = false;

BunnyInputComponent::BunnyInputComponent(Entity &entity) : InputComponent(entity) {

}

void BunnyInputComponent::update(double elapsed) {

    if (debug) std::cout << "Entity: " << &entity_ << " PlayerInputComponent::update elapsed: " << elapsed << std::endl;
    if (debug) Input::inputStruct.log();
    x_ = 0;
    if (input.right) {
        x_ += runSpeed_;

    }
    if (input.left) {
        x_ -= runSpeed_;
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

    if (*hittingCeiling_ == true) {
        if (y_ < 0) {
            y_ = 0;
        }
    }

    if (input.right == false && input.left == false) {
        x_ *= 0.5;
    }
}

void BunnyInputComponent::siblingComponentsInitialized() {
    BunnyPhysicsComponent &physics = *entity_.getComponent<BunnyPhysicsComponent *>();

    runSpeed_ = physics.runSpeed;
    jumpSpeed_ = physics.jumpSpeed;
    grounded_ = &physics.grounded;
    hittingCeiling_ = &physics.hittingCeiling;

}
