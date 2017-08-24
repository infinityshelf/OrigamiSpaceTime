//
// Created by Estevan Hernandez on 8/4/17.
//

#include <iostream>
#include <SFML/Window.hpp>
#include <sstream>
#include "SFML-Engine/GraphicsComponent.hpp"
#include "SFML-Engine/Input.hpp"
#include "Bunny.hpp"
#include "World.hpp"
#include "BunnyPhysicsComponent.hpp"

const unsigned int blockSize = 16;
const unsigned int width = blockSize * 56 / 2;
const unsigned int height = blockSize * 32 / 2;

int main(int argc, const char *argv[]) {
    std::string windowTitle("Origami Space Time");
    if (argc > 1) {
        windowTitle = std::string(argv[1]);
    }

    sf::RenderWindow window(sf::VideoMode(width, height, 8), argv[1], sf::Style::Titlebar|sf::Style::Close);
    window.setSize(sf::Vector2u(width * 4,height * 4));
    window.setPosition(sf::Vector2i(100,0));

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setTitle(windowTitle);

    GraphicsComponent::setWindow(&window);

    World *world = World::instance();

    for (unsigned int i = 0; i < width / blockSize; i++) {
        for (unsigned int j = 0; j < height / blockSize; j++) {
            if (i == 0 || j == 0 || i == (width / blockSize) - 1 || j == (height / blockSize) - 1) {
                world->addCollidable(new sf::IntRect(i * blockSize, j * blockSize, blockSize, blockSize));
            }

            if ((i >= 2 && i <= 8)
                &&(j == height / blockSize - 5)) {
                world->addCollidable(new sf::IntRect(i * blockSize, j * blockSize, blockSize, blockSize));
            }
        }
    }
    Bunny *player = new Bunny();
    world->addEntity(player);
    Input::clearInput();
    
    while (window.isOpen()) {
        Input::getInput(window);
        world->update(1, window);
    }

    return EXIT_SUCCESS;
}