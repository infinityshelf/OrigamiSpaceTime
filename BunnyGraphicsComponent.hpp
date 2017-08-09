//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNYGRAPHICSCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYGRAPHICSCOMPONENT_HPP

#include "SFML-Engine/GraphicsComponent.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"

extern const std::string kBunnyWalk;
extern const std::string kBunnyWalkFilePath;

class BunnyGraphicsComponent: public GraphicsComponent, public MessageHandler<INT> {
private:
    const sf::Vector2i *position_;
    sf::Sprite sprite_;
public:
    BunnyGraphicsComponent(Entity &entity);
    void update(double elapsed) override;
    void siblingComponentsInitialized() override;

    void handleMessage(Message<INT> const &message) override {
        std::cout << "description: "<< message.description << " message: " << message.data_ << std::endl;
    }


};


#endif //ORIGAMISPACETIME_BUNNYGRAPHICSCOMPONENT_HPP
