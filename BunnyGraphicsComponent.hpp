//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNYGRAPHICSCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYGRAPHICSCOMPONENT_HPP

#include "SFML-Engine/GraphicsComponent.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"
#include "Bunny.hpp"
#include "BunnyPhysicsComponent.hpp"
#include <cmath>

class BunnyPhysicsComponent;

extern const std::string kBunnyWalk;
extern const std::string kBunnyWalkFilePath;

class BunnyGraphicsComponent: public GraphicsComponent, public MessageHandler<INT> {
private:
    const sf::Vector2f *position_;
    sf::Sprite sprite_;
    Bunny &entity_;
    sf::CircleShape teleportingRadius_;
    sf::CircleShape maxTeleportRadius_;
    BunnyPhysicsComponent *physicsComponent_;

    bool shouldTeleport_ = false;
    static float teleportationMultiplier_;
public:
    sf::CircleShape &teleportingRadius = teleportingRadius_;
    explicit BunnyGraphicsComponent(Bunny &bunny);
    void update(double elapsed) override;
    void siblingComponentsInitialized() override;
    void handleMessage(Message<INT> const &message) override;
    ~BunnyGraphicsComponent() override;
    static sf::Vector2f getMousePosition() {
        sf::RenderWindow &windowRef = *GraphicsComponent::s_window;

        sf::Vector2i mouse_pos_ref = sf::Mouse::getPosition(dynamic_cast<sf::Window &>(windowRef));
        sf::Vector2f mouse_pos = windowRef.mapPixelToCoords(mouse_pos_ref);
        return mouse_pos;
    }
    float getMouseDistance(){
        sf::Vector2f mouse_pos = BunnyGraphicsComponent::getMousePosition();
        return sqrtf(powf(mouse_pos.x - position_->x, 2) + powf(mouse_pos.y - position_->y, 2));
    }
    const bool &shouldTeleport = shouldTeleport_;
    const float &teleportationMultiplier = teleportationMultiplier_;
};


#endif //ORIGAMISPACETIME_BUNNYGRAPHICSCOMPONENT_HPP
