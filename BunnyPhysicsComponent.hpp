//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP

#include "SFML-Engine/PhysicsComponent.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"
#include "SFML-Engine/GraphicsComponent.hpp"
#include "Bunny.hpp"
#include "BunnyInputComponent.hpp"
#include "BunnyGraphicsComponent.hpp"

class BunnyGraphicsComponent;
class BunnyInputComponent;

class BunnyPhysicsComponent: public PhysicsComponent, public MessageHandler<INT> {
private:
    Bunny &entity_;
    const sf::Vector2f *inputVector_;

    std::vector<sf::Vector2<uint16_t> > positions_;


    sf::IntRect boundingBox_;
    bool grounded_;
    bool hittingCeiling_;
    bool hitWallLeft_;
    bool hitWallRight_;

    int runSpeed_;
    int jumpSpeed_;
    int maxFallSpeed_;

    void setFlags();
    sf::Vector2f startPoint_;
    sf::Vector2f endPoint_;
    float distanceTraveled_ = 0;

    BunnyInputComponent *inputComponent_;
    BunnyGraphicsComponent *graphicsComponent_;
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

    const float &distanceTraveled = distanceTraveled_;
    const sf::Vector2f &startPoint = startPoint_;
    const sf::Vector2f &endPoint = endPoint_;
};


#endif //ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP
