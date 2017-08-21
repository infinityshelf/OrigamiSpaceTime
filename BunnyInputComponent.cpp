//
// Created by Estevan Hernandez on 8/4/17.
//

#include "BunnyInputComponent.hpp"
#include "BunnyGraphicsComponent.hpp"
#include <cassert>
#include <cmath>
const bool debug = false;

BunnyInputComponent::BunnyInputComponent(Bunny &bunny) : InputComponent(bunny), entity_(bunny) {
    static_cast<MessageDispatcher<BOOL> *>(this)->addHandler(static_cast<MessageHandler<BOOL> *>(GameWorld::instance()));
    static_cast<MessageDispatcher<INT> *>(this)->addHandler(static_cast<MessageHandler<INT> *>(GameWorld::instance()));
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
            if (GameWorld::instance()->teleporting == false) {
                //InputStruct blank;
                //input_ = blank;
                play();
            } else {
                return;
            }
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
            InputStruct blank;
            // when teleporting, we want to ignore pretty much all inputs except for LMB released
            input_ = blank;
            input_.leftMouseButtonReleased = Input::inputStruct.leftMouseButtonReleased;
            // for now, use the mouse_x position as a frame

            //int mouse_x = mousePos.x;

            //mouse_x = (mouse_x < 0) ? 0 : mouse_x;
            //uint16_t mouse_x16 = static_cast<uint16_t>(mouse_x);
            if (physicsComponent_) {

                sf::Vector2f posF = physicsComponent_->getEndPosition();

                float mouseDistance = BunnyGraphicsComponent::getMouseDistance(posF);
                float traveledDistance = physicsComponent_->getTraveledDistance();

                float multiplier = mouseDistance / traveledDistance;
                multiplier = (multiplier > 1.f) ? 1.f : multiplier;

                if (debug) std::cout << "multiplier: " << multiplier << std::endl;
                uint16_t lifeSpan = entity_.death - entity_.birth;

                uint16_t frame = entity_.death - lifeSpan * multiplier;

                GameWorld::instance()->currentFrame = entity_.birth + static_cast<uint16_t >(frame);

            }

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

    // only want to allow a teleport if the player is recording (player controlled)
    if (input.leftMouseButtonPressed
        && entity_.state == BUNNY_STATE_RECORDING) {

        //set state to teleporting
        entity_.setState(BUNNY_STATE_TELEPORTING);
        // data = false would be the teleport was cancelled.
        bool data = true;
        // set the death to teh current frame, if the teleportation gets cancelled, it would be 0xFFFF again.
        entity_.death = GameWorld::instance()->currentFrame;
        Message<BOOL> teleportMessage(data);
        teleportMessage.description = "teleport";
        // dispatch message.
        static_cast<MessageDispatcher<BOOL> *>(this)->dispatchMessage(teleportMessage);

    }
    if (input.leftMouseButtonReleased
        && entity_.state == BUNNY_STATE_TELEPORTING) {

        // only teleport on LMB released if the player is teleporting.
        uint16_t frame = GameWorld::instance()->currentFrame;
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

    uint16_t frame = GameWorld::instance()->currentFrame;
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
