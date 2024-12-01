#include "Player.h"
#include <iostream>

// Constructor arguments: player texture file, laser texture file, player speed, laser speed as latter two may be changed if difficulty settings are implemented
Player::Player(const std::string& playerTextureFile, const std::string& laserTextureFile, float playerSpeed, float laserSpeed) 
    : laser(laserTextureFile, laserSpeed), speed(playerSpeed), laserActive(false) {
    if (!playerTexture.loadFromFile(playerTextureFile)) {
        std::cerr << "Error: Could not load player texture from " << playerTextureFile << std::endl;
        exit(-1);
    }
    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(0.5f, 0.5f);
	playerSprite.setPosition(800.0f, 820.0f); // Depending on window size, may need to adjust starting position
}

// Move the player
void Player::move(float deltaTime, const sf::Vector2u& windowSize) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        playerSprite.move(-speed * deltaTime, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        playerSprite.move(speed * deltaTime, 0);
    }

    // Prevent going off-screen
    if (playerSprite.getPosition().x < 0) {
        playerSprite.setPosition(0, playerSprite.getPosition().y);
    }
    if (playerSprite.getPosition().x + playerSprite.getGlobalBounds().width > windowSize.x) {
        playerSprite.setPosition(windowSize.x - playerSprite.getGlobalBounds().width, playerSprite.getPosition().y);
    }
}

// Shoot a laser
void Player::shoot() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !laserActive) {
        laserActive = true;
        // Set the initial position of the laser
        laser.setPosition(
            playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2 - laser.getBounds().width / 2,
            playerSprite.getPosition().y - laser.getBounds().height
        );
    }
}


// Update the player and laser
void Player::update(float deltaTime) {
    if (laserActive) {
        laser.move(deltaTime);

        // If the laser goes off-screen, deactivate it
        if (laser.getPosition().y + laser.getBounds().height < 0) {
            laserActive = false;
        }
    }
}

// Draw the player and laser
void Player::draw(sf::RenderWindow& window) {
    window.draw(playerSprite);

    if (laserActive) {
        laser.draw(window);
    }
}

// Check if the laser is active
bool Player::isLaserActive() const {
    return laserActive;
}

// Get reference to the laser
Laser& Player::getLaser() {
    return laser;
}

// Deactivate the laser
void Player::deactivateLaser() {
    laserActive = false;
}

