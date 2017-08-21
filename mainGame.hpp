//
// Created by Estevan Hernandez on 8/4/17.
//

#ifndef ORIGAMISPACETIME_GAME_HPP
#define ORIGAMISPACETIME_GAME_HPP

#include "SFML-Engine/World.hpp"

extern const int screenWidth;
extern const int screenHeight;

class mainGame {
public:

    static mainGame *instance() {
        if (s_instance == nullptr) {
            s_instance = new mainGame;
        }
        return s_instance;
    }
    static int main(int argc, const char *argv[]);
private:
    static mainGame *s_instance;
    mainGame() {

    }
};


#endif //ORIGAMISPACETIME_GAME_HPP
