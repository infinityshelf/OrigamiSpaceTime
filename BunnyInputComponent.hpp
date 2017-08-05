//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNYINPUTCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYINPUTCOMPONENT_HPP

#include "SFML-Engine/InputComponent.hpp"
#include "SFML-Engine/Input.hpp"

class BunnyInputComponent: public InputComponent {
private:
    sf::Vector2i inputVector_;
    int &x_ = inputVector_.x;
    int &y_ = inputVector_.y;
    const InputStruct &input = Input::inputStruct;

    int runSpeed_;
    int jumpSpeed_;
    const bool *grounded_;
    const bool *hittingCeiling_;
public:
    const sf::Vector2i &inputVector = inputVector_;
    const int &x = inputVector_.x;
    const int &y = inputVector_.y;

    BunnyInputComponent(Entity &entity);

    void update(double elapsed) override;
    void siblingComponentsInitialized() override;


};


#endif //ORIGAMISPACETIME_BUNNYINPUTCOMPONENT_HPP
