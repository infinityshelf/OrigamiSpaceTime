//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP

#include "SFML-Engine/PhysicsComponent.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"
#include "SFML-Engine/GraphicsComponent.hpp"
#include "BunnyComponent.hpp"
#include "Bunny.hpp"
#include "BunnyInputComponent.hpp"
#include "BunnyGraphicsComponent.hpp"

class BunnyGraphicsComponent;
class BunnyInputComponent;

class BunnyPhysicsComponent: public PhysicsComponent,
                             //public MessageHandler<INT>,
                             //public MessageHandler<BOOL>,
                             public MessageHandler<VECTOR2i>,
                             public BunnyComponent {
private:
    Bunny &entity_;
    const sf::Vector2f *inputVector_;


    sf::IntRect boundingBox_;
    bool grounded_;
    bool hittingCeiling_;
    bool hitWallLeft_;
    bool hitWallRight_;

    int runSpeed_;
    int jumpSpeed_;
    int maxFallSpeed_;

    void setFlags();

    BunnyInputComponent *inputComponent_;
    BunnyGraphicsComponent *graphicsComponent_;

    std::vector<sf::Vector2<uint16_t>> recordedPositions_;

    //using MessageHandler<INT>::handleMessage;
    //using MessageHandler<BOOL>::handleMessage;
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

    //void handleMessage(Message<BOOL> const &message) override;
    //void handleMessage(Message<INT> const &message) override;
    void handleMessage(Message<VECTOR2i> const &message) override;
    ~BunnyPhysicsComponent() override;

    void recording() override;
    void playing() override;
    void controlUsingInput();
    void controlUsingTime();
    void scrubbing() override;
    void teleporting() override;

    unsigned long getPositionsSize();
    float getTraveledDistance();

    sf::Vector2f getStartPosition();
    sf::Vector2f getEndPosition();
    const sf::Vector2f &position = position_;
};


#endif //ORIGAMISPACETIME_BUNNYPHYSICSCOMPONENT_HPP
