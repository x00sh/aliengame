#include "AlienManager.h"
#include <iostream>
#include <algorithm>

AlienManager::AlienManager(int rows, int cols, const sf::Vector2u& windowSize, float delay, float laserSpeed)
    : moveRight(true), directionDown(false), timeSinceLastMove(0.0f), moveDelay(delay) {
    // Create aliens and place them in a grid
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float xPos = 50.0f + col * 150.0f;
            float yPos = 50.0f + row * 100.0f;
            aliens.push_back(new Alien(sf::Vector2f(xPos, yPos), laserSpeed));
        }
    }
}

AlienManager::~AlienManager() {
    // Clean up dynamically allocated aliens
    for (Alien* alien : aliens) {
        delete alien;
    }
}

void AlienManager::reset(int rows, int cols, const sf::Vector2u& windowSize, float laserSpeed) {
	// Clean up existing aliens
	for (Alien* alien : aliens) {
		delete alien;
	}
	aliens.clear(); // Clear the vector
	// Create new aliens
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			float xPos = 50.0f + col * 150.0f;
			float yPos = 50.0f + row * 100.0f;
			aliens.push_back(new Alien(sf::Vector2f(xPos, yPos), laserSpeed));
		}
	}
}

void AlienManager::update(float deltaTime, const sf::Vector2u& windowSize) {
    timeSinceLastMove += deltaTime;

    if (timeSinceLastMove >= moveDelay) {
        timeSinceLastMove = 0.0f;

        // Move aliens right or left based on edge detection
        if (moveRight) {
            // Check if any alien has reached the right boundary
            bool hitRightEdge = false;
            for (Alien* alien : aliens) {
                if (alien->getBounds().left + alien->getBounds().width >= windowSize.x) {
                    hitRightEdge = true;
                    break;
                }
            }

            if (hitRightEdge) {
                directionDown = true;
                moveRight = false;  // Change direction
            }
            else {
                for (Alien* alien : aliens) {
                    alien->setPosition(alien->getPosition() + sf::Vector2f(7.5f, 0)); // Move right by smaller step
                }
            }
        }
        else {
            // Check if any alien has reached the left boundary
            bool hitLeftEdge = false;
            for (Alien* alien : aliens) {
                if (alien->getBounds().left <= 0) {
                    hitLeftEdge = true;
                    break;
                }
            }

            if (hitLeftEdge) {
                directionDown = true;
                moveRight = true; // Change direction
            }
            else {
                for (Alien* alien : aliens) {
                    alien->setPosition(alien->getPosition() - sf::Vector2f(7.5f, 0)); // Move left by smaller step
                }
            }
        }

        // Move all aliens down if an edge is hit
        if (directionDown) {
            for (int i = 0; i < aliens.size(); ++i) {
                Alien* alien = aliens[i];

                // Move alien down by 20 pixels while keeping the horizontal position intact
                sf::Vector2f currentPos = alien->getPosition();
                alien->setPosition(sf::Vector2f(currentPos.x, currentPos.y + 15.0f)); // Only update Y for downward movement
            }
            directionDown = false; // Reset flag after moving all aliens down
        }

        // Update lasers and shooting for all aliens
        
        for (Alien* alien : aliens) {
            if (!alien->getLaser()) {
                // Alien has no active laser, give it a 1% chance to shoot
                if (rand() % 100 < 1) { // 1% chance
                    alien->shootLaser();
                }
            }

            // Move the alien's laser if it is active
            alien->moveLaser(deltaTime);
        }
        
    }
}


void AlienManager::draw(sf::RenderWindow& window) {
    for (Alien* alien : aliens) {
        alien->draw(window);    // Draw each alien
    }
}

void AlienManager::checkCollisions(Player& player) {

    for (Alien* alien : aliens) {
        if (alien->getLaser() && alien->getLaser()->getBounds().intersects(player.getBounds())) {
            // Handle player hit by alien laser
            std::cout << "Player hit by alien laser!" << std::endl;
          
            alien->deactivateLaser();
			player.takeDamage();

            if (player.getHealth() <= 0) {
                std::cout << "Game Over!" << std::endl;
                player.destroy();
            }

            break; // Stop checking other aliens once the player is hit
        }
    }
    if (!player.isLaserActive()) {
        return; // No active laser, so no collisions to check
    }

    Laser& laser = player.getLaser(); // Get a reference to the player's laser

    for (size_t i = 0; i < aliens.size(); ) {
        if (laser.getBounds().intersects(aliens[i]->getBounds())) {
            // Collision detected: Remove alien and deactivate the laser
            delete aliens[i];                 // Free memory for the alien
            aliens.erase(aliens.begin() + i); // Remove alien from the list
            player.deactivateLaser();         // Deactivate the laser
            break;                            // Only one collision per laser
        }
        else if (aliens[i]->getLaser() && laser.getBounds().intersects(aliens[i]->getLaser()->getBounds())) {
			// Collision detected: Remove alien laser and deactivate the player's laser
			aliens[i]->deactivateLaser();     // Deactivate the alien's laser
			player.deactivateLaser();         // Deactivate the player's laser
			break;
        }
        else {
            ++i; // Check the next alien
        }
    }
}