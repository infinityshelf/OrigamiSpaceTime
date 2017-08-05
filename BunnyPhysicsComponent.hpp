//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP

#include "SFML-Engine/PhysicsComponent.hpp"

class BunnyPhysicsComponent: public PhysicsComponent {
private:
    const sf::Vector2i *inputVector_;

    sf::Vector2i position_;
    int &x_ = position_.x;
    int &y_ = position_.y;

    sf::Vector2i size_;
    int &width_ = size_.x;
    int &height_ = size_.y;

    sf::IntRect boundingBox_;
    bool grounded_;
    bool hittingCeiling_;

    int runSpeed_;
    int jumpSpeed_;
    int maxFallSpeed_;
public:
    const bool &grounded = grounded_;
    const bool &hittingCeiling = hittingCeiling_;
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


};


#endif //ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP
