#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AlienManager.h"
#include <iostream>

int main() {
    // Window dimensions
    float windowWidth = 1600;
    float windowHeight = 900;

    // Create a window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Alien Game");

    // Initialize the player
    Player player(250.0f, 300.0f, (windowWidth / 2), (windowHeight - 80));

    // Create the AlienManager
    AlienManager alienManager(4, 9, window.getSize());

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

    sf::Clock clock; // Clock to track frame time
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (isGameOver && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    alienManager.reset(4, 9, window.getSize());
                    player.reset(250.0f, 300.0f, (windowWidth / 2), (windowHeight - 80));
                    clock.restart();
                    isGameOver = false;
                    std::cout << "Game restarted\n";
                }
                else if (event.key.code == sf::Keyboard::Q) {
                    window.close(); // Close the window if Q is pressed
                }
            }
        }

        // Update the game (only if not game over)
        if (!isGameOver) {
            float deltaTime = clock.restart().asSeconds();

            // Update the player and alien manager
            player.move(deltaTime, window.getSize());
            player.shoot();
            player.update(deltaTime);
            alienManager.update(deltaTime, window.getSize());
            alienManager.checkCollisions(player);

            // Check if the player is destroyed
            if (player.getDestroyed()) {
                isGameOver = true;
                std::cout << "Game Over triggered\n";
            }
        }

        // Render the game
        window.clear(sf::Color::Black);
        if (isGameOver) {
            window.draw(gameOverText);          // Draw the game over screen
        }
        else {
			player.draw(window);				// Draw the player
			alienManager.draw(window);		  // Draw the aliens
        }
        window.display();
    }

    return 0;
}
