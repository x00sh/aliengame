#include "Player.h"
#include <iostream>

// Constructor
Player::Player(const std::string& textureFile, float initSpeed, const sf::Vector2f& startPos)
    : speed(initSpeed) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error: Could not load texture from " << textureFile << std::endl;
        exit(-1); // Exit if the texture fails to load
    }
    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f); // Adjust the scale as needed
    sprite.setPosition(startPos);
}

// Move the player
void Player::move(float deltaTime, const sf::Vector2u& windowSize) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-speed * deltaTime, 0); // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(speed * deltaTime, 0); // Move right
    }

    // Prevent going off-screen
    if (sprite.getPosition().x < 0) {
        sprite.setPosition(0, sprite.getPosition().y);
    }
    if (sprite.getPosition().x + sprite.getGlobalBounds().width > windowSize.x) {
        sprite.setPosition(windowSize.x - sprite.getGlobalBounds().width, sprite.getPosition().y);
    }
}

// Draw the player
void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Accessor: Get player position
sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

// Accessor: Set player position
void Player::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}
