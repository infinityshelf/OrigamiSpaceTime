//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP

#include "SFML-Engine/PhysicsComponent.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"

class BunnyPhysicsComponent: public PhysicsComponent, public MessageHandler<INT> {
private:
    const sf::Vector2i *inputVector_;

    sf::Vector2i position_;
    std::vector<sf::Vector2i> positions_;
    int &x_ = position_.x;
    int &y_ = position_.y;

    sf::Vector2i size_;
    int &width_ = size_.x;
    int &height_ = size_.y;

    sf::IntRect boundingBox_;
    bool grounded_;
    bool hittingCeiling_;
    bool hitWallLeft_;
    bool hitWallRight_;

    int runSpeed_;
    int jumpSpeed_;
    int maxFallSpeed_;

    void setFlags();
public:
    const bool &grounded = grounded_;
    const bool &hittingCeiling = hittingCeiling_;
    const bool &hitWallLeft = hitWallLeft_;
    const bool &hitWallRight = hitWallRight_;
    const sf::Vector2i &position = position_;
    const sf::Vector2i &size = size_;
    const int width = width_;
    const int height = height_;
    const int &x = position_.x;
    const int &y = position_.y;
    BunnyPhysicsComponent(Entity &entity);
    void update(double elapsed) override;
    void siblingComponentsInitialized() override;

    const int &runSpeed = runSpeed_;
    const int &jumpSpeed = jumpSpeed_;

    void handleMessage(Message<INT> const &message) override {
        std::cout << "description: "<< message.description << " message: " << message.data_ << std::endl;
    }
};


#endif //ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP
