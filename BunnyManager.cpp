//
// Created by Estevan Hernandez on 8/22/17.
//

#include "BunnyManager.hpp"

BunnyManager* BunnyManager::s_instance = nullptr;

bool BunnyManager::teleporting_ = false;
const bool &BunnyManager::teleporting = teleporting_;

void BunnyManager::addBunny(Bunny *bunny) {
    static bool debug;
    for (Bunny *aBunny: bunnies_) {
        if (aBunny == bunny) {
            if (debug) std::cout << "That Bunny is already in the Bunny Manager." << std::endl;
            return;
        }
    }
    this->bunnies_.push_back(bunny);
}

void BunnyManager::removeBunny(Bunny *bunny) {
    bunnies_.erase(std::remove(bunnies_.begin(), bunnies_.end(), bunny), bunnies_.end());
}