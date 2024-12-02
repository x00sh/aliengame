#include "Alien.h"
#include "Laser.h"
#include <iostream>


Alien::Alien(const std::string& textureFile, const sf::Vector2f& startPos, float initSpeed)
    : speed(initSpeed), alienLaser(nullptr) { // Initialize alienLaser to nullptr
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error: Could not load texture from " << textureFile << std::endl;
        exit(-1);
    }
    sprite.setTexture(texture);
    sprite.setScale(0.15f, 0.15f);
    sprite.setPosition(startPos);
}

Alien::~Alien() {
    delete alienLaser; // Delete the laser when the alien is destroyed
}

void Alien::shootLaser() {
    if (!alienLaser) { // Only shoot if no laser is currently active
        alienLaser = new Laser("assets/laser.png", -20000.0f); // Initialize laser with speed
        alienLaser->setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - alienLaser->getBounds().width / 2,
            sprite.getPosition().y + sprite.getGlobalBounds().height);
    }
}


void Alien::moveLaser(float deltaTime) {
    if (alienLaser) {
        alienLaser->move(deltaTime); // Move the laser downward
    }
}


void Alien::draw(sf::RenderWindow& window) {
    window.draw(sprite);
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
