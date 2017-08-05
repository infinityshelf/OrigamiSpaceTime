//
// Created by Estevan Hernandez on 8/4/17.
//

#include "BunnyGraphicsComponent.hpp"
#include <SFML/System.hpp>
#include "BunnyPhysicsComponent.hpp"

const bool debug = false;

void BunnyGraphicsComponent::update(double elapsed) {
    if (debug) std::cout << "BunnyGraphicsComponent::update elapsed: " <<  elapsed << std::endl;

    sf::RectangleShape rect;
    rect.setPosition(position_->x, position_->y);
    rect.setFillColor(sf::Color::Red);
    rect.setSize(sf::Vector2f(size_->x, size_->y));
    GraphicsComponent::s_window->draw(rect);

}

BunnyGraphicsComponent::BunnyGraphicsComponent(Entity &entity): GraphicsComponent(entity) {

}

void BunnyGraphicsComponent::siblingComponentsInitialized() {
    BunnyPhysicsComponent &physics = *parent_.getComponent<BunnyPhysicsComponent *>();
    position_ = &physics.position;
    size_ = &physics.size;
}