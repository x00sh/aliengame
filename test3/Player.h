#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>

class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;

public:
    // Constructor
    Player(const std::string& textureFile, float initSpeed, const sf::Vector2f& startPos);

    // Move the player
    void move(float deltaTime, const sf::Vector2u& windowSize);

    // Draw the player
    void draw(sf::RenderWindow& window);

    // Accessors (optional, for extending functionality)
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
};

#endif // PLAYER_H

