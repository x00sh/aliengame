#ifndef ALIEN_MANAGER_H
#define ALIEN_MANAGER_H

#include <vector>
#include "Alien.h"
#include "Player.h" // Include the Player class header
#include "Laser.h"

class AlienManager {
private:
    std::vector<Alien*> aliens;
    bool moveRight;
    bool directionDown;
    float timeSinceLastMove;
    float moveDelay;

public:
    AlienManager(int rows, int cols, const sf::Vector2u& windowSize);
    ~AlienManager();

    void reset(int rows, int cols, const sf::Vector2u& windowSize);
    void update(float deltaTime, const sf::Vector2u& windowSize);
    void draw(sf::RenderWindow& window);

    void checkCollisions(Player& player); // Check and handle collisions with player lasers
};
#endif