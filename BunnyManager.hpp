//
// Created by Estevan Hernandez on 8/22/17.
//

#ifndef ORIGAMISPACETIME_BUNNYMANAGER_HPP
#define ORIGAMISPACETIME_BUNNYMANAGER_HPP

#include "Bunny.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"

class Bunny;

class BunnyManager: public Dispatcher {
private:
    static BunnyManager *s_instance;
    static bool teleporting_;
    BunnyManager() = default;
    std::vector<Bunny *> bunnies_;
public:
    const std::vector<Bunny *> &bunnies = bunnies_;
    friend class Bunny;
    static const bool &teleporting;
    static BunnyManager *instance() {
        if (!s_instance) {
            s_instance = new BunnyManager();
        }
        return s_instance;
    }
    void addBunny(Bunny *bunny);
    void removeBunny(Bunny *bunny);
    ~BunnyManager() = default;
};


#endif //ORIGAMISPACETIME_BUNNYMANAGER_HPP
