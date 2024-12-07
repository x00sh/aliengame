#include "Alien.h"
#include "Laser.h"
#include <iostream>

Alien::Alien(const sf::Vector2f& startPos, float laser)
    : speed(0.0f), laserSpeed(laser), alienLaser(nullptr) { // Initialize alienLaser to nullptr
	const std::string& textureFile = "assets/alien.png";
    if (!alienTexture.loadFromFile(textureFile)) {
        std::cerr << "Error: Could not load alienTexture from " << textureFile << std::endl;
        exit(-1);
    }
    alienSprite.setTexture(alienTexture);
    alienSprite.setScale(0.15f, 0.15f);
    alienSprite.setPosition(startPos);
}

Alien::~Alien() {
    //delete alienLaser; // Delete the laser when the alien is destroyed
}



void Alien::shootLaser() {

    if (!alienLaser) { // Only shoot if no laser is currently active
        alienLaser = new Laser(-laserSpeed); // Initialize laser with speed
        alienLaser->setPosition(alienSprite.getPosition().x + alienSprite.getGlobalBounds().width / 2 - alienLaser->getBounds().width / 2,
            alienSprite.getPosition().y + alienSprite.getGlobalBounds().height);
    }
}

void Alien::moveLaser(float deltaTime) {
    if (alienLaser) {
        alienLaser->move(deltaTime); // Move the laser downward

		if (alienLaser->getBounds().height > 900) { // If laser goes off-screen, deactivate it
			deactivateLaser();
		}
    }
}

void Alien::draw(sf::RenderWindow& window) {
    window.draw(alienSprite);
    if (alienLaser) {
        alienLaser->draw(window); // Draw the laser if it exists
    }
}

Laser* Alien::getLaser() {
    return alienLaser;
}

void Alien::deactivateLaser() {
    if (alienLaser) {
        delete alienLaser;
        alienLaser = nullptr;
    }
}

// Move the alien in a specific direction
void Alien::move(float deltaX, float deltaY) {
    alienSprite.move(deltaX, deltaY);
}

// Update the alien's movement (e.g., oscillating horizontally)
void Alien::update(float deltaTime, const sf::Vector2u& windowSize, bool& directionDown) {
    sf::Vector2f position = alienSprite.getPosition();

    // Reverse direction if alien hits screen bounds
    if (position.x <= 0 || position.x + alienSprite.getGlobalBounds().width >= windowSize.x) {
        directionDown = true; // Signal to move downward
        speed = -speed;       // Reverse horizontal movement
    }

    if (directionDown) {
        alienSprite.move(0, 10); // Move downward
        directionDown = false; // Reset direction flag
    }
    else {
        alienSprite.move(speed * deltaTime, 0); // Horizontal movement
    }
}

// Accessor: Get alien's position
sf::Vector2f Alien::getPosition() const {
    return alienSprite.getPosition();
}

// Accessor: Set alien's position
void Alien::setPosition(const sf::Vector2f& position) {
    alienSprite.setPosition(position);
}

// Accessor: Get alien's global bounds (for collision detection)
sf::FloatRect Alien::getBounds() const {
    return alienSprite.getGlobalBounds();
}
