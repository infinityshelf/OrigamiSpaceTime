//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_GAME_HPP
#define ORIGAMISPACETIME_GAME_HPP

#include "SFML-Engine/World.hpp"

extern const int screenWidth;
extern const int screenHeight;

class Game {
public:

    static Game *instance() {
        if (s_instance == nullptr) {
            s_instance = new Game;
        }
        return s_instance;
    }
    static int main(int argc, const char *argv[]);
private:
    static Game *s_instance;
    Game() {

    }
};


#endif //ORIGAMISPACETIME_GAME_HPP
