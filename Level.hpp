#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <cinttypes>
#include <cassert>
#include <iostream>
#include <cstdio>
#include "Door.hpp"

#include "SFML-Engine/CollidableManager.hpp"
#include "SFML-Engine/EntityManager.hpp"

enum FileType {
    FileTypeUndefined = 0,
    FileTypeLevel = 1
};

struct Header {
    uint8_t signature[4] = {'T','I','M','E'};
    uint8_t version = 0x1;
    uint8_t type = FileTypeLevel;
    uint16_t size = 0x3;
};

// struct Door {
//     uint16_t x;
//     uint16_t y;
// };

// struct Button {
//     uint16_t x;
//     uint16_t y;
//     uint16_t triggerDoor;
// };

// struct Collidable {
//     uint16_t x;
//     uint16_t y;
//     uint16_t width;
//     uint16_t height;
// };

struct LevelInfo {
    char type[4] = {'L', 'E', 'V', 'L'};
    uint8_t nameOffset = 0xFF;
    uint8_t entryDoorOffset = 0xFF;
    uint8_t exitDoorOffset = 0xFF;
    // uint8_t buttonsOffset = 0xFF;
    uint8_t collidablesOffset = 0xFF;
    char name[8] = "";
    Door entry;
    Door exit;
    // Button *buttons;
    //sf::IntRect *collidables;
};

class Level: public CollidableManager,
             public EntityManager {
private:
    Header header;
    LevelInfo levelInfo;
    std::vector<Door *> doors;
public:
    void write(const char * fileName);
    static void Read(Level *level, const char * fileName);
    Level();
    Level(unsigned int levelId);
};

#endif