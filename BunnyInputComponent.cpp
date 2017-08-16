//
// Created by Estevan Hernandez on 8/4/17.
//

#include "BunnyInputComponent.hpp"
#include "BunnyGraphicsComponent.hpp"
#include <cassert>
const bool debug = false;

BunnyInputComponent::BunnyInputComponent(Bunny &bunny) : InputComponent(bunny), entity_(bunny) {
    addHandler(OrigamiWorld::instance());
}

void BunnyInputComponent::update(double elapsed) {

    if (debug) std::cout << "Entity: " << &entity_ << " PlayerInputComponent::update elapsed: " << elapsed << std::endl;
    if (debug) Input::inputStruct.log();
    //x_ = 0;
    if (input.right) {
        x_ += 1;
        if (x_ > runSpeed_) {
            x_ = runSpeed_;
        }

    }
    if (input.left) {
        x_ -= 1;
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
        if (y_ > maxFallSpeed_) {
            y_ = maxFallSpeed_;
        } else {
            y_ += 0.5f;
        }

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
    // if left mouse button is pressed
    // and if not teleporting
    if (input.leftMouseButtonPressed) {
        handleLeftClick();
    }
}

void BunnyInputComponent::handleLeftClick() {
    switch(entity_.state) {
        case BUNNY_STATE_UNDEFINED: {
            assert(false && "Bunny State was Undefined");
            break;
        }
        case BUNNY_STATE_RECORDING: {
            entity_.setState(BUNNY_STATE_TELEPORTING);
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
            if (graphicsComponent_
                && graphicsComponent_->shouldTeleport) {
                entity_.setState(BUNNY_STATE_PLAYING);
                uint16_t lifeSpan = entity_.deathday - entity_.birthday;
                uint16_t data = entity_.deathday - lifeSpan * graphicsComponent_->teleportationMultiplier;
                //uint16_t data = entity_.deathday - (lifeSpan * graphicsComponent_->teleportationMultiplier);
                Message<INT> message(data);
                message.description = "teleported";
                dispatchMessage(message);
            }
            break;
        }
        case BUNNY_STATE_PLAYING: {
            // do nothing
            break;
        }
    }

}

void BunnyInputComponent::siblingComponentsInitialized() {
    physicsComponent_ = entity_.getComponent<BunnyPhysicsComponent *>();
    graphicsComponent_ = entity_.getComponent<BunnyGraphicsComponent *>();
    addHandler(physicsComponent_);
    if (physicsComponent_) {
        runSpeed_ = physicsComponent_->runSpeed;
        jumpSpeed_ = physicsComponent_->jumpSpeed;
        maxFallSpeed_ = physicsComponent_->maxFallSpeed;
        grounded_ = &physicsComponent_->grounded;
        hittingCeiling_ = &physicsComponent_->hittingCeiling;
        hitWallLeft_ = &physicsComponent_->hitWallLeft;
        hitWallRight_ = &physicsComponent_->hitWallRight;
    }

}

BunnyInputComponent::~BunnyInputComponent() = default;
