#include "DoorGraphicsComponent.hpp"
#include "SFML-Engine/TextureManager.hpp"
const std::string kDoor = "Door";
const std::string kDoorPath = "Images/door_strip.png";

void DoorGraphicsComponent::siblingComponentsInitialized() {
    physics_ = entity_.getComponent<DoorPhysicsComponent *>();
    if (physics_ != nullptr) {
        sprite_.setPosition(physics_->x,physics_->y);
    }

}
DoorGraphicsComponent::DoorGraphicsComponent(Door &door): GraphicsComponent(door), entity_(door) {
    TextureManager::instance()->loadTexture(kDoor, kDoorPath);
    sprite_.setTexture(TextureManager::instance()->getRef(kDoor));
    sprite_.setTextureRect(sf::IntRect(0,0,16,16));
    sprite_.setScale(4,4);
}
void DoorGraphicsComponent::update(double elapsed) {
    static bool debug = false;
    if (debug) std::cout << "elapsed: " << elapsed << std::endl;
    GraphicsComponent::s_window->draw(sprite_);
};

void DoorGraphicsComponent::handleMessage(MessageBase const &message) {
    const Message<bool> *boolMessage = dynamic_cast<const Message<bool> *>(&message);
    if (boolMessage != nullptr) {
        if (boolMessage->data == true) {
            sprite_.setTextureRect(sf::IntRect(16,0,16,16));
        } else {
            sprite_.setTextureRect(sf::IntRect(0,0,16,16));
        }
    }
}