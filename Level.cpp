#include "Level.hpp"

const unsigned int blockSize = 60;
const unsigned int width = 1920;
const unsigned int height = 1080;

Level::Level() {
    //levelInfo.entry.x = 0x44;
    //levelInfo.entry.y = 0x55;
    //levelInfo.exit.x = 0x66;
    //levelInfo.exit.y = 0x77;

    //memcpy(levelInfo.name, "Level 1", 7);
    //levelInfo.name = "Level 1"
}

Level::Level(unsigned int levelId) {
    //assert(false);
    switch(levelId) {
        case 0: {
            memcpy(levelInfo.name, "Level 0 ", 7);
            for (unsigned int i = 0; i < width / blockSize; i++) {
                for (unsigned int j = 0; j < height / blockSize; j++) {
                    if (i == 0 || j == 0 || i == (width / blockSize) - 1 || j == (height / blockSize) - 1) {
                        addCollidable(new sf::Rect<uint16_t>(i * blockSize, j * blockSize, blockSize, blockSize));
                    }

                    if ((i >= 3 && i <= 9)
                        &&(j == height / blockSize - 5)) {
                        addCollidable(new sf::Rect<uint16_t>(i * blockSize, j * blockSize, blockSize, blockSize));
                    }
                }
            }

            entry_ = new Door(sf::Vector2f(60*2, 60*16));
            exit_ = new Door(sf::Vector2f(60*30, 60*16));
            //levelInfo.entry = *entry;
            //levelInfo.exit = *exit;
            addEntity(static_cast<Entity *>(entry_));
            addEntity(static_cast<Entity *>(exit_));
            break;
        }
        case 1: {
            break;
        }
        default: {
            break;
        }
    }

}

void Level::write(const char * fileName) {
    FILE *fp = fopen(fileName, "w");
    if (fp != NULL) {
        std::cout << "opened file" << std::endl;

        // Header is 8 bytes
        fwrite(header.signature, 1, 4, fp);
        fwrite(&header.version, 1, 1, fp);
        fwrite(&header.type, 1, 1, fp);
        fwrite(&header.size, sizeof(uint16_t), 1, fp);

        //fseek(fp, 12, SEEK_CUR); // lin 93
        fwrite("\xFF\xFF\xFF\xFF\xFF\xFF", 12, 1, fp);

        fpos_t nameOff;
        fgetpos(fp, &nameOff);
        
        fwrite(&levelInfo.name, 1, 8, fp); // 8

        fpos_t entryDoorOff;
        fgetpos(fp, &entryDoorOff);

        //fwrite(&levelInfo.entry.x, 2, 1, fp); // 2
        //fwrite(&levelInfo.entry.y, 2, 1, fp); // 2
        uint16_t val;
        val = (uint16_t)entry_->getComponent<DoorPhysicsComponent *>()->x;
        fwrite(&val, sizeof(uint16_t), 1, fp);
        val = (uint16_t)entry_->getComponent<DoorPhysicsComponent *>()->y;
        fwrite(&val, sizeof(uint16_t), 1, fp);
        val = (uint16_t)exit_->getComponent<DoorPhysicsComponent *>()->x;
        fwrite(&val, sizeof(uint16_t), 1, fp);
        val = (uint16_t)exit_->getComponent<DoorPhysicsComponent *>()->y;
        fwrite(&val, sizeof(uint16_t), 1, fp);

        fpos_t exitDoorOff;
        fgetpos(fp, &exitDoorOff);

        fpos_t collidablesOff;
        fgetpos(fp, &collidablesOff);

        for (sf::Rect<uint16_t> *collidable: collidables) {
            //sf::IntRect *intRect = collidable;
//            fwrite(&collidable.left, sizeof(int), 1, fp);
//            fwrite(&collidable.top, sizeof(int), 1, fp);
//            fwrite(&collidable.width, sizeof(int), 1, fp);
//            fwrite(&collidable.height, sizeof(int), 1, fp);
            fwrite(collidable, sizeof(sf::Rect<uint16_t>), 1, fp);
        }


        for (sf::Rect<uint16_t> *collidable: collidables) {
            std::cout << "WRITE" << std::endl;
            std::cout << "collidable.left: " << collidable->left << std::endl;
            std::cout << "collidable.top: " << collidable->top << std::endl;
            std::cout << "collidable.width: " << collidable->width << std::endl;
            std::cout << "collidable.height: " << collidable->height << std::endl;
            std::cout << std::endl;
        }
        
        fseek(fp, 8, SEEK_SET); // line 56

        // Level Info offsets are 12 bytes
        fwrite(&levelInfo.type, 1, 4, fp);
        fwrite(&nameOff, sizeof(uint16_t), 1, fp);
        fwrite(&entryDoorOff, sizeof(uint16_t), 1, fp);
        fwrite(&exitDoorOff, sizeof(uint16_t), 1, fp);
        fwrite(&collidablesOff, sizeof(uint16_t), 1, fp);

        

        fseek(fp, 0, SEEK_END);
        fpos_t size;
        fgetpos(fp, &size);

        fseek(fp, 6, SEEK_SET);
        fwrite(&size, sizeof(uint16_t), 1, fp);

        fclose(fp);
    } else {
        assert(false && "File was null");
    }
}

void Level::Read(Level *pLevel, const char * fileName) {
    FILE *fp = fopen(fileName, "r");

    if (fp != NULL && pLevel != nullptr) {
        Level &level = *pLevel;

        fread(level.header.signature, 1, 4, fp);
        fread(&level.header.version, 1, 1, fp);
        fread(&level.header.type, 1, 1, fp);
        fread(&level.header.size, 2, 1, fp);
        fread(level.levelInfo.type, sizeof(char), 4, fp);
        fread(&level.levelInfo.nameOffset, sizeof(uint16_t), 1, fp);
        fread(&level.levelInfo.entryDoorOffset, sizeof(uint16_t), 1, fp);
        fread(&level.levelInfo.exitDoorOffset, sizeof(uint16_t), 1, fp);
        fread(&level.levelInfo.collidablesOffset, sizeof(uint16_t), 1, fp);
        fread(&level.levelInfo.name, 8, 1, fp);



        uint16_t entry_x = 0;
        uint16_t entry_y = 0;
        uint16_t exit_x = 0;
        uint16_t exit_y = 0;

        fread(&entry_x, sizeof(uint16_t), 1, fp);
        fread(&entry_y, sizeof(uint16_t), 1, fp);
        fread(&exit_x, sizeof(uint16_t), 1, fp);
        fread(&exit_y, sizeof(uint16_t), 1, fp);

        Door *entry = new Door(sf::Vector2f(entry_x, entry_y));
        Door *exit = new Door(sf::Vector2f(exit_x, exit_y));

        //level.levelInfo.entry = *entry;
        //level.levelInfo.exit = *exit;

        uint16_t sizeOfCollidables = level.header.size - level.levelInfo.collidablesOffset;
        uint16_t collidablesCount = sizeOfCollidables / sizeof(sf::Rect<uint16_t>);

        for (uint16_t i = 0; i < collidablesCount; i++) {
            sf::Rect<uint16_t> *collidable = new sf::Rect<uint16_t >();
            fread(collidable, sizeof(sf::Rect<uint16_t>), 1, fp);
            level.addCollidable(collidable);
        }

        level.addEntity(static_cast<Entity *>(entry));
        level.addEntity(static_cast<Entity *>(exit));
    } else {
        assert(false && "File was null");
    }
}