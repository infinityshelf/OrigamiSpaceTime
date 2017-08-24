//
// Created by Estevan Hernandez on 8/4/17.
//

#include "BunnyInputComponent.hpp"
#include "BunnyGraphicsComponent.hpp"
#include <cassert>
#include <cmath>
const bool debug = false;

BunnyInputComponent::BunnyInputComponent(Bunny &bunny) : InputComponent(bunny), entity_(bunny) {
    static_cast<MessageDispatcher<BOOL> *>(this)->addHandler(static_cast<MessageHandler<BOOL> *>(&entity_));
    static_cast<MessageDispatcher<INT> *>(this)->addHandler(static_cast<MessageHandler<INT> *>(&entity_));
}

void BunnyInputComponent::update(double elapsed) {
    switch (entity_.state) {
        case BUNNY_STATE_UNDEFINED: {
            assert(false);
        }
        case BUNNY_STATE_RECORDING: {
            recording();
            break;
        }
        case BUNNY_STATE_PLAYING: {
            playing();
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
            teleporting();
            break;
        }
        case BUNNY_STATE_SCRUBBING: {
            scrubbing();
            break;
        }
    }

    if (debug) std::cout << "Entity: " << &entity_ << " PlayerInputComponent::update elapsed: " << elapsed << std::endl;
    if (debug) Input::inputStruct.log();
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

void BunnyInputComponent::recording() {
    input_ = Input::inputStruct;

    if (input.leftMouseButtonPressed) {

        bool data = true;
        Message<BOOL> teleportMessage(data);
        teleportMessage.description = "teleporting";
        static_cast<MessageDispatcher<BOOL> *>(this)->dispatchMessage(teleportMessage);

        return;
    }

    input_.leftMouseButtonPressed = false; // never record a teleport! lol
    input_.leftMouseButtonReleased = false;// this too
    recordedInputs_.push_back(input);

    control(input_);
}

void BunnyInputComponent::teleporting() {
    input_ = Input::inputStruct;
    if (input.leftMouseButtonPressed) {

        uint16_t frame = World::instance()->currentFrame;
        Message<INT> teleportedMessage(frame);
        teleportedMessage.description = "teleported";
        static_cast<MessageDispatcher<INT> *>(this)->dispatchMessage(teleportedMessage);

    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {

        bool data = false;
        Message<BOOL> teleportCancelledMessage(data);
        teleportCancelledMessage.description = "teleporting";

        static_cast<MessageDispatcher<BOOL> *>(this)->dispatchMessage(teleportCancelledMessage);
    }

    if (physicsComponent_) {

        sf::Vector2f posF = physicsComponent_->getEndPosition();

        float mouseDistance = BunnyGraphicsComponent::getMouseDistance(posF);
        float traveledDistance = physicsComponent_->getTraveledDistance();

        float multiplier = mouseDistance / traveledDistance;
        multiplier = (multiplier > 1.f) ? 1.f : multiplier;

        if (debug) std::cout << "multiplier: " << multiplier << std::endl;
        uint16_t lifeSpan = entity_.death - entity_.birth;

        uint16_t frame = entity_.death - lifeSpan * multiplier;

        World::instance()->currentFrame = entity_.birth + static_cast<uint16_t >(frame);

    }
}

void BunnyInputComponent::scrubbing() {
    // do nothing when scrubbing!
    return;
}

void BunnyInputComponent::playing() {
    InputStruct blank;
    input_ = blank;

    uint16_t frame = World::instance()->currentFrame;
    uint16_t index = 0;
    index = frame - entity_.birth;
    if (index < recordedInputs_.size()) {
        input_ = recordedInputs_[frame - entity_.birth];
        //input_.leftMouseButtonPressed = false; // never playback a teleport! lol
        //input_.leftMouseButtonReleased = false;// this too
        assert(input_.leftMouseButtonPressed == false
               && input_.leftMouseButtonReleased == false);
        control(input_);
    } else {
        if (debug) {
            std::cout << "out of range:" << std::endl
                      << "..valid: 0.." << recordedInputs_.size() - 1 << std::endl
                      << "..index:    " << index << std::endl;
        }
    }
}

void BunnyInputComponent::control(InputStruct input) {
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

}


BunnyInputComponent::~BunnyInputComponent() = default;
