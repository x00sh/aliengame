#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>

class Laser {
private:
    sf::Sprite laserSprite;
    sf::Texture laserTexture;
    float speed;

public:
    Laser(float initSpeed);
    void move(float deltaTime); // Moves the laser upward
    void setPosition(float x, float y); // Sets the initial position of the laser
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
};

#endif // LASER_H
