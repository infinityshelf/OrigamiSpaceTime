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

    switch(entity_.state) {
        case BUNNY_STATE_UNDEFINED: {
            assert(false);
            break;
        }
        case BUNNY_STATE_RECORDING: {
            record();
            break;
        }
        case BUNNY_STATE_TELEPORTING: {
            play();
            return;
            //break;
        }
        case BUNNY_STATE_PLAYING: {
            play(); /* For now, just play back recorded positions */
            return;
            break;
        }
    }

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
    if (inputComponent_) {
        static_cast<MessageDispatcher<INT> *>(inputComponent_)->addHandler(dynamic_cast<MessageHandler<INT> *>(this));
        static_cast<MessageDispatcher<BOOL> *>(inputComponent_)->addHandler(dynamic_cast<MessageHandler<BOOL> *>(this));
    }
    graphicsComponent_ = entity_.getComponent<BunnyGraphicsComponent *>();
    inputVector_ = (inputComponent_) ? &inputComponent_->inputVector : nullptr;
}

void BunnyPhysicsComponent::setFlags() {
    grounded_ = (placeFree(x, y + 1, boundingBox_) != nullptr);
    hittingCeiling_ = (placeFree(x, y - 1, boundingBox_) != nullptr);
    hitWallLeft_ = (placeFree(x - 1, y, boundingBox_) != nullptr);
    hitWallRight_ = (placeFree(x + 1, y, boundingBox_) != nullptr);
}

void BunnyPhysicsComponent::handleMessage(Message<BOOL> const &message) {
    if (true) std::cout << message.data_ << std::endl;
    if (message.description == "teleport") {
        if (message.data_ == true) {
            // teleport started
        } else if (message.data_ == false) {
            // teleport cancelled
        }
    }
}

void BunnyPhysicsComponent::handleMessage(Message<INT> const &message) {
    if (debug) std::cout << message.data_ << std::endl;

    /****
    if (message.description == "teleported") {
        uint16_t index = 0;
        index = message.data_ - entity_.birth;
        //entity_.death = message.data_;
        //index -= 1;
        if (index < recordedPositions_.size()) {
            sf::Vector2<uint16_t > recordedPos = recordedPositions_[index];
            position_ = sf::Vector2f(recordedPos.x, recordedPos.y);

            //
            // This should delete all of the recorded positions before the players
            // landing position after a teleportation happens
            //
            // We don't want to delete the current position.
            // A teleportation message is received during the input phase.

            //std::cout << "old size:" << recordedPositions_.size() << std::endl;
            //recordedPositions_.erase(recordedPositions_.begin(), recordedPositions_.begin() + index);
            //std::cout << "new size:" << recordedPositions_.size() << std::endl;
            Bunny *newBunny = new Bunny(BUNNY_STATE_RECORDING, message.data_, 0xFFFF);
            OrigamiWorld::instance()->addEntity(newBunny);
        } else {
            std::cout << "void BunnyPhysicsComponent::handleMessage(Message<INT> const &message)\n"
                      << "out of range:" << std::endl
                      << "..valid: 0.." << recordedPositions_.size() - 1 << std::endl
                      << "..index:    " << index << std::endl;
        }
    }
     ****/
    //OrigamiWorld::instance()->currentFrame = message.data_;
    if (message.description == "teleported") {
        Bunny *newBunny = new Bunny(BUNNY_STATE_RECORDING, message.data_, 0xFFFF);
        sf::Vector2i mousePos = BunnyGraphicsComponent::getMousePosition();
        newBunny->getComponent<BunnyPhysicsComponent *>()->position_ = sf::Vector2f(mousePos.x / 4, mousePos.y / 4);
        OrigamiWorld::instance()->addEntity(newBunny);
    }
}

void BunnyPhysicsComponent::play() {
    // uses input for playback
    uint16_t frame = OrigamiWorld::instance()->currentFrame;
    uint16_t index = frame - entity_.birth;

    if (debug) std::cout << "frame: " << frame << std::endl;
    sf::Vector2<uint16_t > pos(0,0);
    unsigned long size = recordedPositions_.size();

    if (index < recordedPositions_.size()) {
        pos = recordedPositions_[index];
        position_ = sf::Vector2f(pos.x, pos.y);
    } else {
        if (debug) {
            std::cout << "void BunnyPhysicsComponent::play(uint16_t frame)\n"
                      << "out of range:" << std::endl
                      << "..valid: 0.." << recordedPositions_.size() - 1 << std::endl
                      << "..index:    " << index << std::endl;
        }
        pos = recordedPositions_.at(size - 1);
        position_ = sf::Vector2f(pos.x, pos.y);
    }

}

void BunnyPhysicsComponent::record() {
    assert(recordedPositions_.size() < 0xFFFF && "Why do you need so many bytes?!");
    recordedPositions_.push_back(sf::Vector2<uint16_t >(x,y));
}

unsigned long BunnyPhysicsComponent::getPositionsSize() {
    return recordedPositions_.size();
}

BunnyPhysicsComponent::~BunnyPhysicsComponent() = default;
