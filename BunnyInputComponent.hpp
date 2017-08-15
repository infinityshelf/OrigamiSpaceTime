//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNYINPUTCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYINPUTCOMPONENT_HPP

#include "SFML-Engine/InputComponent.hpp"
#include "SFML-Engine/Input.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"
#include "Bunny.hpp"
#include "BunnyPhysicsComponent.hpp"
#include "OrigamiWorld.hpp"

class BunnyPhysicsComponent;

class BunnyInputComponent: public InputComponent, public MessageDispatcher<INT> {
private:
    Bunny &entity_;
    sf::Vector2f inputVector_;
    float &x_ = inputVector_.x;
    float &y_ = inputVector_.y;
    const InputStruct &input = Input::inputStruct;

    float runSpeed_;
    float jumpSpeed_;
    float maxFallSpeed_;
    const bool *grounded_;
    const bool *hittingCeiling_;
    const bool *hitWallLeft_;
    const bool *hitWallRight_;

    BunnyPhysicsComponent *physicsComponent_;
    void handleLeftClick();
public:
    const sf::Vector2f &inputVector = inputVector_;
    const float &x = x_;
    const float &y = y_;

    explicit BunnyInputComponent(Bunny &bunny);

    void update(double elapsed) override;
    void siblingComponentsInitialized() override;

    ~BunnyInputComponent() override;
};


#endif //ORIGAMISPACETIME_BUNNYINPUTCOMPONENT_HPP
