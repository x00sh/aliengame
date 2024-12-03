#include "Laser.h"
#include <iostream>

Laser::Laser(float initSpeed) : speed(initSpeed) {
	const std::string& textureFile = "assets/laser.png";
    if (!laserTexture.loadFromFile(textureFile)) {
        std::cerr << "Error: Could not load laserTexture from " << textureFile << std::endl;
        exit(-1);
    }
    laserSprite.setTexture(laserTexture);
}

void Laser::move(float deltaTime) {
    laserSprite.move(0, -speed * deltaTime); // Move the laser upward
}

void Laser::setPosition(float x, float y) {
    laserSprite.setPosition(x, y); // Set the laser's initial position
}

void Laser::draw(sf::RenderWindow& window) {
    window.draw(laserSprite);
}

sf::Vector2f Laser::getPosition() const {
    return laserSprite.getPosition();
}

sf::FloatRect Laser::getBounds() const {
    return laserSprite.getGlobalBounds();
}
