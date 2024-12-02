#ifndef PLAYER_H
#define PLAYER_H

#include "Laser.h"

class Player {
private:
    sf::Sprite playerSprite;
    sf::Texture playerTexture;
    Laser laser;              // Non-static member
    bool laserActive;         // Tracks if the laser is active
    float speed;
    bool destroyed;

public:
    Player(const std::string& playerTextureFile, const std::string& laserTextureFile, float playerSpeed, float laserSpeed);
    void move(float deltaTime, const sf::Vector2u& windowSize);
    void shoot();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isLaserActive() const;          // Check if the laser is active
    Laser& getLaser();                   // Get reference to the laser
    void deactivateLaser();   
    

    bool isDestroyed() const { return destroyed; }
    void destroy() { destroyed = true; }  

    // New method to get player's bounding box (for collision detection)
    sf::FloatRect getBounds() const {
        return playerSprite.getGlobalBounds();
    }
};

#endif // PLAYER_H
