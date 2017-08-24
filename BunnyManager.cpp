//
// Created by Estevan Hernandez on 8/22/17.
//

#include "BunnyManager.hpp"

BunnyManager* BunnyManager::s_instance = nullptr;

void BunnyManager::addBunny(Bunny *bunny) {
    static bool debug;
    bool shouldAdd = true;
    for (Bunny *aBunny: bunnies_) {
        if (aBunny == bunny) {
            shouldAdd = false;
            break;
        }
    }
    if (shouldAdd == true) {
        this->bunnies_.push_back(bunny);
    } else {
        if (debug) std::cout << "That Bunny is already in the Bunny Manager." << std::endl;
    }

}

void BunnyManager::removeBunny(Bunny *bunny) {
    bunnies_.erase(std::remove(bunnies_.begin(), bunnies_.end(), bunny), bunnies_.end());
}

bool BunnyManager::isABunnyTeleporting() {
    for (Bunny *bun: bunnies_) {
        if (bun->state == BUNNY_STATE_TELEPORTING) {
            return true;
        }
    }
    return false;
}

void BunnyManager::handleMessage(Message<BOOL> const &message) {
    if (message.description == "teleport") {
        if (message.data_ == true) {

        } else if (message.data_ == false) {

        }
    }

}
