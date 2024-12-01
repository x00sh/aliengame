#include "Laser.h"
#include <iostream>

Laser::Laser(const std::string& textureFile, float initSpeed) : speed(initSpeed) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error: Could not load texture from " << textureFile << std::endl;
        exit(-1);
    }
    sprite.setTexture(texture);
}

void Laser::move(float deltaTime) {
    sprite.move(0, -speed * deltaTime); // Move the laser upward
}

void Laser::setPosition(float x, float y) {
    sprite.setPosition(x, y); // Set the laser's initial position
}

void Laser::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Laser::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect Laser::getBounds() const {
    return sprite.getGlobalBounds();
}
