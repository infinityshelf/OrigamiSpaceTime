//
// Created by Estevan Hernandez on 8/4/17.
//

#include "Bunny.hpp"
#include "World.hpp"
#include "BunnyPhysicsComponent.hpp"
#include "BunnyGraphicsComponent.hpp"

bool debug = false;

BunnyPhysicsComponent::BunnyPhysicsComponent(Bunny &bunny): PhysicsComponent(bunny), entity_(bunny) {
    world_ = World::instance();
    x_ = 32*3;
    y_ = 32 * 5;

    width_ = 64;
    height_ = 64;

    boundingBox_.left = x_ - size.x / 2;
    boundingBox_.top = y_ - size.y / 2;
    boundingBox_.width = width_;
    boundingBox_.height = height_;
    runSpeed_ = 3 + 10;
    jumpSpeed_ = 8 + 23;
    maxFallSpeed_ = 5 + 10;

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
            recording();
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
        case BUNNY_STATE_PLAYING: {
            playing();
            break;
        }
    }
}

void BunnyPhysicsComponent::controlUsingInput() {
    boundingBox_.left = x - size.x / 2;
    boundingBox_.top = y - size.y / 2;

    sf::Vector2f velocity = (inputVector_) ? *inputVector_ : sf::Vector2f(0,0);

    const sf::Rect<uint16_t> *result;

    result = World::instance()->level->placeFree(x + velocity.x, y, &boundingBox_);

    if (result == nullptr) {
        x_ += velocity.x;
    } else {
        if (velocity.x > 0) {
            x_ = result->left - boundingBox_.width;
        } else if (velocity.x < 0) {
            x_ = result->left + result->width;
        }
    }

    result = World::instance()->level->placeFree(x , y + velocity.y, &boundingBox_);

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

void BunnyPhysicsComponent::controlUsingTime() {
    uint16_t frame = World::instance()->currentFrame;
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

void BunnyPhysicsComponent::siblingComponentsInitialized() {
    inputComponent_ = entity_.getComponent<BunnyInputComponent *>();
    graphicsComponent_ = entity_.getComponent<BunnyGraphicsComponent *>();
    inputVector_ = (inputComponent_) ? &inputComponent_->inputVector : nullptr;
}

void BunnyPhysicsComponent::setFlags() {
    grounded_ =       (World::instance()->level->placeFree(x, y + 1, &boundingBox_) != nullptr);
    hittingCeiling_ = (World::instance()->level->placeFree(x, y - 1, &boundingBox_) != nullptr);
    hitWallLeft_ =    (World::instance()->level->placeFree(x - 1, y, &boundingBox_) != nullptr);
    hitWallRight_ =   (World::instance()->level->placeFree(x + 1, y, &boundingBox_) != nullptr);
}

void BunnyPhysicsComponent::recording() {
    assert(BunnyManager::teleporting == false);
    assert(recordedPositions_.size() < 0xFFFF && "Why do you need so many bytes?!");
    recordedPositions_.push_back(sf::Vector2<uint16_t >(x,y));
    controlUsingInput();
}

void BunnyPhysicsComponent::teleporting() {
    controlUsingTime();
}

void BunnyPhysicsComponent::scrubbing() {
    controlUsingTime();
}

void BunnyPhysicsComponent::playing() {
    controlUsingInput();
}

unsigned long BunnyPhysicsComponent::getPositionsSize() {
    return recordedPositions_.size();
}

float BunnyPhysicsComponent::getTraveledDistance() {

    sf::Vector2f start = getStartPosition();
    sf::Vector2f end = getEndPosition();

    float distance = sqrtf(powf(start.x - end.x, 2) + powf(start.y - end.y, 2));

    return distance;
}

sf::Vector2f BunnyPhysicsComponent::getEndPosition() {
    sf::Vector2<uint16_t > end16 = recordedPositions_[recordedPositions_.size() - 1];
    sf::Vector2f end = sf::Vector2f(end16.x, end16.y);
    return end;
}

sf::Vector2f BunnyPhysicsComponent::getStartPosition() {
    sf::Vector2<uint16_t > start16 = recordedPositions_[0];
    sf::Vector2f start = sf::Vector2f(start16.x, start16.y);
    return start;
}

void BunnyPhysicsComponent::handleMessage(Message<VECTOR2i> const &message) {
    if (message.description == "teleported") {
        position_ = sf::Vector2f(message.data_.x, message.data_.y);
    }
}

BunnyPhysicsComponent::~BunnyPhysicsComponent() = default;
