//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNYGRAPHICSCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYGRAPHICSCOMPONENT_HPP

#include "SFML-Engine/GraphicsComponent.hpp"
//#include "SFML-Engine/ComponentMessaging.hpp"
#include "Bunny.hpp"
#include "BunnyPhysicsComponent.hpp"
#include <cmath>
#include "BunnyComponent.hpp"

class BunnyPhysicsComponent;

extern const std::string kBunnyWalk;
extern const std::string kBunnyWalkFilePath;

class BunnyGraphicsComponent: public GraphicsComponent,
                              public BunnyComponent {
private:
    const sf::Vector2f *position_;
    sf::Sprite sprite_;
    Bunny &entity_;
    BunnyPhysicsComponent *physicsComponent_;

    sf::CircleShape maxTeleportCircle;
    sf::CircleShape teleportCircle;
public:
    explicit BunnyGraphicsComponent(Bunny &bunny);
    void update(double elapsed) override;
    void siblingComponentsInitialized() override;
    void handleMessage(Message<INT> const &message);
    ~BunnyGraphicsComponent() override;
    //sf::RenderWindow &windowRef() { return *s_window; }
    static sf::Vector2i getMousePosition();
    static float getMouseDistance(sf::Vector2f position);
    void record() override;
    void play() override;
};


#endif //ORIGAMISPACETIME_BUNNYGRAPHICSCOMPONENT_HPP
