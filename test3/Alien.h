#ifndef ALIEN_H
#define ALIEN_H

#include <SFML/Graphics.hpp>

class Alien {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed; // Movement speed

public:
    Alien(const std::string& textureFile, const sf::Vector2f& startPos, float initSpeed);

    void move(float deltaX, float deltaY);             // Direct movement
    void update(float deltaTime, const sf::Vector2u& windowSize, bool& directionDown); // Automatic movement
    void draw(sf::RenderWindow& window);              // Render the alien

    sf::Vector2f getPosition() const;                 // Get current position
    void setPosition(const sf::Vector2f& position);   // Set position
    sf::FloatRect getBounds() const;                  // Get collision bounds
};

#endif
