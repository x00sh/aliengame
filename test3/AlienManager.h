#ifndef ALIEN_MANAGER_H
#define ALIEN_MANAGER_H

#include <vector>
#include "Alien.h"

class AlienManager {
private:
    std::vector<Alien*> aliens;
    bool moveRight;
    bool directionDown;
    float timeSinceLastMove;
    const float moveDelay;

public:
    AlienManager(int rows, int cols, const std::string& textureFile, const sf::Vector2u& windowSize, float initSpeed);
    ~AlienManager();

    void update(float deltaTime, const sf::Vector2u& windowSize);
    void draw(sf::RenderWindow& window);
};

#endif
