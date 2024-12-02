#ifndef ALIEN_H
#define ALIEN_H

#include <SFML/Graphics.hpp>
#include "Laser.h"


class Alien {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed; // Movement speed
    Laser* alienLaser; // Alien's laser
public:
    Alien(const std::string& textureFile, const sf::Vector2f& startPos, float initSpeed);
    ~Alien(); // Destructor to delete laser if it's created

    void move(float deltaX, float deltaY);
    void update(float deltaTime, const sf::Vector2u& windowSize, bool& directionDown);
    void draw(sf::RenderWindow& window);

    void shootLaser(); // Method to shoot laser
    void moveLaser(float deltaTime); // Method to move the laser
    void deactivateLaser();
   


    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
    sf::FloatRect getBounds() const;

    Laser* getLaser(); // Accessor for alien laser
};

#endif
