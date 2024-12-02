#include "Alien.h"
#include <iostream>

// Constructor
Alien::Alien(const std::string& textureFile, const sf::Vector2f& startPos)
    : speed(0.0f) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error: Could not load texture from " << textureFile << std::endl;
        exit(-1); // Exit if the texture fails to load
    }
    sprite.setTexture(texture);
    sprite.setScale(0.15f, 0.15); // Adjust the scale as needed
    sprite.setPosition(startPos);
}

// Move the alien in a specific direction
void Alien::move(float deltaX, float deltaY) {
    sprite.move(deltaX, deltaY);
}

// Update the alien's movement (e.g., oscillating horizontally)
void Alien::update(float deltaTime, const sf::Vector2u& windowSize, bool& directionDown) {
    sf::Vector2f position = sprite.getPosition();

    // Reverse direction if alien hits screen bounds
    if (position.x <= 0 || position.x + sprite.getGlobalBounds().width >= windowSize.x) {
        directionDown = true; // Signal to move downward
        speed = -speed;       // Reverse horizontal movement
    }

    if (directionDown) {
        sprite.move(0, 10); // Move downward
        directionDown = false; // Reset direction flag
    }
    else {
        sprite.move(speed * deltaTime, 0); // Horizontal movement
    }
}

// Draw the alien
void Alien::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}




// Accessor: Get alien's position
sf::Vector2f Alien::getPosition() const {
    return sprite.getPosition();
}

// Accessor: Set alien's position
void Alien::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

// Accessor: Get alien's global bounds (for collision detection)
sf::FloatRect Alien::getBounds() const {
    return sprite.getGlobalBounds();
}
