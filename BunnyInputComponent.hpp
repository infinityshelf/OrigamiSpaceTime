//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNYINPUTCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYINPUTCOMPONENT_HPP

#include "SFML-Engine/InputComponent.hpp"
#include "SFML-Engine/Input.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"
#include "Bunny.hpp"
#include "World.hpp"
#include "BunnyComponent.hpp"

class BunnyPhysicsComponent;

class BunnyInputComponent: public InputComponent,
                           //public MessageHandler<INT>,
                           //public MessageDispatcher<INT>,
                           public MessageDispatcher<VECTOR2i>,
                           public MessageDispatcher<BOOL>,
                           public BunnyComponent {
private:
    Bunny &entity_;
    sf::Vector2f inputVector_;
    float &x_ = inputVector_.x;
    float &y_ = inputVector_.y;
    InputStruct input_;

    //
    // for time travel recording
    //
    std::vector<InputStruct> recordedInputs_;

    float runSpeed_;
    float jumpSpeed_;
    float maxFallSpeed_;
    const bool *grounded_;
    const bool *hittingCeiling_;
    const bool *hitWallLeft_;
    const bool *hitWallRight_;

    BunnyPhysicsComponent *physicsComponent_;
public:
    const sf::Vector2f &inputVector = inputVector_;
    const float &x = x_;
    const float &y = y_;
    const InputStruct &input = input_;

    explicit BunnyInputComponent(Bunny &bunny);

    void update(double elapsed) override;
    void siblingComponentsInitialized() override;

    ~BunnyInputComponent() override;
    void recording() override;
    void playing() override;
    void scrubbing() override;
    void teleporting() override;
    void control(InputStruct input);
    //void handleMessage(Message<INT> const &message)d;
};


#endif //ORIGAMISPACETIME_BUNNYINPUTCOMPONENT_HPP
