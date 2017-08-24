//
// Created by Estevan Hernandez on 8/22/17.
//

#ifndef ORIGAMISPACETIME_BUNNYMANAGER_HPP
#define ORIGAMISPACETIME_BUNNYMANAGER_HPP

#include "Bunny.hpp"
#include "SFML-Engine/ComponentMessaging.hpp"

class Bunny;

class BunnyManager: public MessageHandler<BOOL>,
                    public MessageDispatcher<BOOL> {
private:
    static BunnyManager *s_instance;
    BunnyManager() = default;
    std::vector<Bunny *> bunnies_;
public:
    static BunnyManager *instance() {
        if (!s_instance) {
            s_instance = new BunnyManager();
        }
        return s_instance;
    }
    void addBunny(Bunny *bunny);
    void removeBunny(Bunny *bunny);
    bool isABunnyTeleporting();
    ~BunnyManager() = default;

    void handleMessage(Message<BOOL> const &message) override;

};


#endif //ORIGAMISPACETIME_BUNNYMANAGER_HPP
