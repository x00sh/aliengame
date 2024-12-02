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
    const float moveDelay;
    int playerHitPoint;

public:
    AlienManager(int rows, int cols, const std::string& textureFile, const sf::Vector2u& windowSize, float initSpeed);
    ~AlienManager();

    void update(float deltaTime, const sf::Vector2u& windowSize);
    void draw(sf::RenderWindow& window);

    void checkCollisions(Player& player); // Check and handle collisions with player lasers

};

#endif
