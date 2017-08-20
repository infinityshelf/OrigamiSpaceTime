//
// Created by Estevan Hernandez on 8/4/17.
//

#include "BunnyInputComponent.hpp"
#include "BunnyGraphicsComponent.hpp"
#include <cassert>
const bool debug = false;

BunnyInputComponent::BunnyInputComponent(Bunny &bunny) : InputComponent(bunny), entity_(bunny) {
    //addHandler(OrigamiWorld::instance());
}

void BunnyInputComponent::update(double elapsed) {
    switch (entity_.state) {
        case BUNNY_STATE_UNDEFINED: {
            assert(false);
        }
        case BUNNY_STATE_RECORDING: {
            input_ = Input::inputStruct;
            record();
            break;
        }
        case BUNNY_STATE_PLAYING: {
            //InputStruct blank;
            //input_ = blank;
            //play();
            return;
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
            InputStruct blank;
            input_ = blank;
            input_.leftMouseButtonReleased = Input::inputStruct.leftMouseButtonReleased;
            int mouse_x = BunnyGraphicsComponent::getMousePosition().x / 4;
            mouse_x = (mouse_x < 0) ? 0 : mouse_x;
            uint16_t mouse_x16 = static_cast<uint16_t>(mouse_x);
            OrigamiWorld::instance()->currentFrame = static_cast<uint16_t >(mouse_x16);
            break;
            //return;
        }
    }

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

    if (input.leftMouseButtonPressed
        && entity_.state == BUNNY_STATE_RECORDING) {

        entity_.setState(BUNNY_STATE_TELEPORTING);
        bool data = true;
        entity_.death = OrigamiWorld::instance()->currentFrame;
        Message<BOOL> teleportMessage(data);
        teleportMessage.description = "teleport";
        static_cast<MessageDispatcher<BOOL> *>(this)->dispatchMessage(teleportMessage);

    }
    if (input.leftMouseButtonReleased
        && entity_.state == BUNNY_STATE_TELEPORTING) {

        uint16_t frame = OrigamiWorld::instance()->currentFrame;
        entity_.setState(BUNNY_STATE_PLAYING);
        Message<INT> teleportedMessage(frame);
        teleportedMessage.description = "teleported";
        static_cast<MessageDispatcher<INT> *>(this)->dispatchMessage(teleportedMessage);

    }
}

void BunnyInputComponent::siblingComponentsInitialized() {
    physicsComponent_ = entity_.getComponent<BunnyPhysicsComponent *>();
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

void BunnyInputComponent::play() {

    uint16_t frame = OrigamiWorld::instance()->currentFrame;
    uint16_t index = 0;
    index = frame - entity_.birth;
    if (index < recordedInputs_.size()) {
        input_ = recordedInputs_[frame - entity_.birth];
        input_.leftMouseButtonPressed = false; // never playback a teleport! lol
        input_.leftMouseButtonReleased = false;// this too
        assert(input_.leftMouseButtonPressed == false
               && input_.leftMouseButtonReleased == false);
    } else {
        if (debug) {
            std::cout << "out of range:" << std::endl
                      << "..valid: 0.." << recordedInputs_.size() - 1 << std::endl
                      << "..index:    " << index << std::endl;
        }
    }
}

void BunnyInputComponent::record() {
    recordedInputs_.push_back(input);
}



BunnyInputComponent::~BunnyInputComponent() = default;
