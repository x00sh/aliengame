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
    bool destroyed = false;
    int health = 5;

public:
    Player(float playerSpeed, float laserSpeed, float xStartPos, float yStartPos);
    void move(float deltaTime, const sf::Vector2u& windowSize);
    void shoot();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isLaserActive() const;          // Check if the laser is active
    Laser& getLaser();                   // Get reference to the laser
    void deactivateLaser();   
    

    bool getDestroyed() const { return destroyed; }
    void destroy() { destroyed = true; }
	void reset(float x, float y, float xStartPos, float yStartPos);

    int getHealth() const { return health; }
	void takeDamage() { health--; }
	

    sf::FloatRect getBounds() const;
};

#endif // PLAYER_H
