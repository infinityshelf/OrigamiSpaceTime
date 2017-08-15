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
    const uint16_t &currentFrame = OrigamiWorld::instance()->currentFrame;
    Bunny &entity_;
    sf::Vector2i inputVector_;
    int &x_ = inputVector_.x;
    int &y_ = inputVector_.y;
    const InputStruct &input = Input::inputStruct;

    int runSpeed_;
    int jumpSpeed_;
    int maxFallSpeed_;
    const bool *grounded_;
    const bool *hittingCeiling_;
    const bool *hitWallLeft_;
    const bool *hitWallRight_;

    BunnyPhysicsComponent *physicsComponent_;
    void handleLeftClick();
public:
    const sf::Vector2i &inputVector = inputVector_;
    const int &x = inputVector_.x;
    const int &y = inputVector_.y;

    explicit BunnyInputComponent(Bunny &bunny);

    void update(double elapsed) override;
    void siblingComponentsInitialized() override;

    ~BunnyInputComponent() override;
};


#endif //ORIGAMISPACETIME_BUNNYINPUTCOMPONENT_HPP
