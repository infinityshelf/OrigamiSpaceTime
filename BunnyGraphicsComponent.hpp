//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_BUNNYGRAPHICSCOMPONENT_HPP
#define ORIGAMISPACETIME_BUNNYGRAPHICSCOMPONENT_HPP

#include "SFML-Engine/GraphicsComponent.hpp"

class BunnyGraphicsComponent: public GraphicsComponent {
private:
    const sf::Vector2i *position_;
    const sf::Vector2i *size_;
public:
    BunnyGraphicsComponent(Entity &entity);
    void update(double elapsed) override;
    void siblingComponentsInitialized() override;


};


#endif //ORIGAMISPACETIME_BUNNYGRAPHICSCOMPONENT_HPP
