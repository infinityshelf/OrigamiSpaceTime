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
#include "Door.hpp"

// const unsigned int blockSize = 60;
// const unsigned int width = 1920;
// const unsigned int height = 1080;

int main(int argc, const char *argv[]) {
    std::string windowTitle("Origami Space Time");
    if (argc > 1) {
        windowTitle = std::string(argv[1]);
    }

	sf::RenderWindow window(sf::VideoMode(1920, 1080, 8), argv[1], sf::Style::Titlebar|sf::Style::Close);
    //window.setSize(sf::Vector2u(width * 3, height * 3));
    window.setPosition(sf::Vector2i(0,0));

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);
    window.setKeyRepeatEnabled(false);
    window.setTitle(windowTitle);

    GraphicsComponent::setWindow(&window);

    World *world = World::instance();
    Bunny *player = new Bunny();
    //Door *door = new Door();
    world->level->addEntity(player);
    //world->level->addEntity(door);
    //world->level = new Level(0);
    //world->level = Level::Read("Level0.origami");
    //std::cout << "world->level: " << world->level << std::endl;
    //assert(false);


    Input::clearInput();
    
    while (window.isOpen()) {
        Input::getInput(window);
        world->update(1, window);
    }

    return EXIT_SUCCESS;
}