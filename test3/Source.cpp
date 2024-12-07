#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AlienManager.h"
#include <iostream>

sf::Text createButton(sf::Font& font, sf::Color color, const std::string& text, const sf::Vector2f& position) {
    sf::Text button;
    button.setFont(font);
    button.setString(text);
    button.setCharacterSize(75);
    button.setFillColor(color);
    button.setPosition(position);
    return button;
}


int main() {
    // Window dimensions
    float windowWidth = 1600;
    float windowHeight = 900;

    // Create a window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Alien Game");

    sf::Font font;
    if (!font.loadFromFile("assets/Evil Empire.otf")) {
        std::cerr << "Error: Could not load font from assets/arial.ttf" << std::endl;
        return -1;
    }

    // Main menu text
    sf::Text title("Alien Game", font, 60);
    title.setFillColor(sf::Color::White);
    title.setPosition(windowWidth / 2 - title.getGlobalBounds().width / 2, 100);

    // Difficulty buttons
    sf::Text easyButton = createButton(font, sf::Color::Green, "Easy", sf::Vector2f((windowWidth / 2) - 250, windowHeight / 2));
    sf::Text mediumButton = createButton(font, sf::Color::Yellow, "Medium", sf::Vector2f((windowWidth / 2) - 50, windowHeight / 2));
    sf::Text hardButton = createButton(font, sf::Color::Red, "Hard", sf::Vector2f((windowWidth / 2) + 250, windowHeight / 2));

    // Create game-over text
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over\nPress R to Restart or Q to Quit");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(windowWidth / 2.0f - gameOverText.getGlobalBounds().width / 2.0f, windowHeight / 2.0f - gameOverText.getGlobalBounds().height / 2.0f);

	// Game variables
	int alienRows = 0, alienCols = 0;
	float playerSpeed = 0.0f, laserSpeed = 0.0f, delay = 0.0f, alienLaserSpeed = 0.0f;
    bool gameStarted = false, gameOver = false;

    sf::Clock clock; // Clock to track frame time

    while (window.isOpen() && !gameStarted) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Check for button clicks
                if (easyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    alienRows = 4;
                    alienCols = 9;
                    playerSpeed = 300.0f;
                    laserSpeed = 400.0f;
                    delay = 0.3f;
					alienLaserSpeed = 1250.0f;
                    gameStarted = true;
                }
                else if (mediumButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    alienRows = 5;
                    alienCols = 10;
                    playerSpeed = 250.0f;
                    laserSpeed = 300.0f;
					delay = 0.25f;
					alienLaserSpeed = 1500.0f;
                    gameStarted = true;
                }
                else if (hardButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    alienRows = 6;
                    alienCols = 10;
                    playerSpeed = 200.0f;
                    laserSpeed = 200.0f;
					delay = 0.20f;
					alienLaserSpeed = 1750.0f;
                    gameStarted = true;
                }
            }
        }

        // Render the main menu
        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(easyButton);
        window.draw(mediumButton);
        window.draw(hardButton);
        window.display();
    }

	// Create the player and alien manager

	Player player(playerSpeed, laserSpeed, (windowWidth / 2), (windowHeight - 80));
	AlienManager alienManager(alienRows, alienCols, window.getSize(), delay, alienLaserSpeed);

    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (gameOver && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    alienManager.reset(4, 9, window.getSize(), alienLaserSpeed);
                    player.reset(250.0f, 300.0f, (windowWidth / 2), (windowHeight - 80));
                    clock.restart();
                    gameOver = false;
                    std::cout << "Game restarted\n";
                }
                else if (event.key.code == sf::Keyboard::Q) {
                    window.close(); // Close the window if Q is pressed
                }
            }
        }

        // Update the game (only if not game over)
        if (!gameOver) {
            float deltaTime = clock.restart().asSeconds();

            // Update the player and alien manager
            player.move(deltaTime, window.getSize());
            player.shoot();
            player.update(deltaTime);
            alienManager.update(deltaTime, window.getSize());
            alienManager.checkCollisions(player);

            // Check if the player is destroyed
            if (player.getDestroyed()) {
                gameOver = true;
                std::cout << "Game Over triggered\n";
            }
        }

        // Render the game
        window.clear(sf::Color::Black);
        if (gameOver) {
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
