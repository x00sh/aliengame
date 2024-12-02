#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AlienManager.h"
#include <iostream>

int main() {
    // Window dimensions
    const int windowWidth = 1600;
    const int windowHeight = 900;

    // Create a window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Alien Game");

    // Initialize the player
    Player player("assets/player.png", "assets/laser.png", 250.0f, 300.0f);

    // Create the AlienManager
    AlienManager alienManager(5, 11, "assets/alien.png", window.getSize(), 0.0f);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("assets/Evil Empire.otf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    // Create game-over text
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over\nPress R to Restart or Q to Quit");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(windowWidth / 2.0f - gameOverText.getGlobalBounds().width / 2.0f,
        windowHeight / 2.0f - gameOverText.getGlobalBounds().height / 2.0f);

    bool isGameOver = false;
    sf::Clock clock; // Clock to restart time on game over

    // Main game loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && isGameOver) {
                if (event.key.code == sf::Keyboard::R) {
                    // Restart the game
                    player = Player("assets/player.png", "assets/laser.png", 250.0f, 300.0f); // Re-initialize the player
                    AlienManager alienManager(5, 11, "assets/alien.png", window.getSize(), 0.0f); // Re-initialize aliens
                    isGameOver = false; // Set game over state to false
                    clock.restart(); // Reset the game clock
                }
                else if (event.key.code == sf::Keyboard::Q) {
                    window.close(); // Close the window if Q is pressed
                }
            }
        }

        // Game updates (only if not game over)
        if (!isGameOver) {
            // Get delta time
            float deltaTime = clock.restart().asSeconds();

            // Update the player
            player.move(deltaTime, window.getSize());
            player.shoot();                   // Check for shooting
            player.update(deltaTime);         // Update laser positions

            // Update the alien manager (moves aliens and handles direction)
            alienManager.update(deltaTime, window.getSize()); // Update aliens' movement and shooting
            alienManager.checkCollisions(player); // Check for collisions between lasers and aliens

            // Check if player is destroyed
            if (player.isDestroyed()) {
                isGameOver = true; // Set game over state to true
            }
        }

        // Render the game
        window.clear(sf::Color::Black); // Clear the screen with a black color
        if (isGameOver) {
            window.draw(gameOverText); // Draw the game over text
        }
        else {
            player.draw(window);           // Draw the player
            alienManager.draw(window);     // Draw all aliens using AlienManager
        }

        window.display(); // Display everything we've drawn
    }

    return 0;
}
