//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP

#include "SFML-Engine/PhysicsComponent.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"
#include "Bunny.hpp"
#include "BunnyInputComponent.hpp"

class BunnyInputComponent;

class BunnyPhysicsComponent: public PhysicsComponent, public MessageHandler<INT> {
private:
    Bunny &entity_;
    //bool active_;
    const sf::Vector2i *inputVector_;

    std::vector<sf::Vector2i> positions_;


    sf::IntRect boundingBox_;
    bool grounded_;
    bool hittingCeiling_;
    bool hitWallLeft_;
    bool hitWallRight_;

    int runSpeed_;
    int jumpSpeed_;
    int maxFallSpeed_;

    void setFlags();
    sf::Vector2i startPoint_;
    sf::Vector2i endPoint_;
    int distanceTraveled_ = 0;

    BunnyInputComponent *inputComponent_;
public:
    //void setActive(bool active) { active_ = active; }
    const bool &grounded = grounded_;
    const bool &hittingCeiling = hittingCeiling_;
    const bool &hitWallLeft = hitWallLeft_;
    const bool &hitWallRight = hitWallRight_;
    explicit BunnyPhysicsComponent(Bunny &bunny);
    void update(double elapsed) override;
    void siblingComponentsInitialized() override;

    const int &runSpeed = runSpeed_;
    const int &jumpSpeed = jumpSpeed_;
    const int &maxFallSpeed = maxFallSpeed_;

    void handleMessage(Message<INT> const &message) override;
    ~BunnyPhysicsComponent() override;

    const int &distanceTraveled = distanceTraveled_;
    const sf::Vector2i &startPoint = startPoint_;
    const sf::Vector2i &endPoint = endPoint_;
};


#endif //ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP
