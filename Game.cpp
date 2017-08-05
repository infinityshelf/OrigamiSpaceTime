//
// Created by Estevan Hernandez on 8/4/17.
//

#include "Game.hpp"
#include <SFML/Window.hpp>
#include "SFML-Engine/GraphicsComponent.hpp"
#include "SFML-Engine/Input.hpp"
#include "Bunny.hpp"

const int blockSize = 64;
const int width = blockSize * 56 / 2;
const int height = blockSize * 32 / 2;


int Game::main(int argc, const char *argv[]) {
    std::string windowTitle("Origami Space Time");
    if (argc > 1) {
        windowTitle = std::string(argv[1]);
    }

    sf::RenderWindow window(sf::VideoMode(width, height, 8), argv[1], sf::Style::Titlebar|sf::Style::Close);

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setTitle(windowTitle);

    GraphicsComponent::setWindow(&window);

    World *world = World::instance();

    for (int i = 0; i < width / blockSize; i++) {
        for (int j = 0; j < height / blockSize; j++) {
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

#if VARIABLE_TIME_STEP
    sf::Clock elapsedClock;
    static double elapsed;
#endif
    Input::clearInput();
    while (window.isOpen()) {
        Input::getInput(window);
#if VARIABLE_TIME_STEP
        elapsed = elapsedClock.restart().asMilliseconds() / (1000.0 / (double) targetFrameRate);
        world->update(elapsed, window);
#else
        world->update(1, window);
#endif

    }

    return EXIT_SUCCESS;
}