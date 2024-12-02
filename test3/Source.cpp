#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AlienManager.h"
#include <iostream>

// Function to create a button sprite
sf::Sprite createButton(const std::string& textureFile, const sf::Vector2f& position) {
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile(textureFile)) {
        std::cerr << "Error: Could not load texture from " << textureFile << std::endl;
        exit(-1);
    }

    sf::Sprite button;
    button.setTexture(*texture);
    button.setPosition(position);
    return button;
}

bool startGame() {

    return true;
}

int main() {
    // Window dimensions
    const int windowWidth = 1600;
    const int windowHeight = 900;

    // Create a window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Alien Game");

    // Load button images as sprites
    sf::Sprite easyButton = createButton("assets/easy.png", sf::Vector2f(windowWidth / 2 - 450, windowHeight / 2 - 100));
    sf::Sprite mediumButton = createButton("assets/med.png", sf::Vector2f(windowWidth / 2 - 150, windowHeight / 2 - 100));
    sf::Sprite hardButton = createButton("assets/hard.png", sf::Vector2f(windowWidth / 2 + 150, windowHeight / 2 - 100));

    // Variables to store selected difficulty settings
    int alienRows = 5, alienCols = 11;
    float playerSpeed = 250.0f, laserSpeed = 300.0f, delay = 0.15f;
    bool gameStarted = false;

    // Main menu loop
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
                    alienRows = 3;
                    alienCols = 8;
                    playerSpeed = 200.0f;
                    laserSpeed = 500.0f;
                    delay = 0.25f;
                    gameStarted = true;
                }
                else if (mediumButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    alienRows = 5;
                    alienCols = 11;
                    playerSpeed = 150.0f;
                    laserSpeed = 400.0f;
					delay = 0.15f;
                    gameStarted = true;
                }
                else if (hardButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    alienRows = 5;
                    alienCols = 11;
                    playerSpeed = 100.0f;
                    laserSpeed = 200.0f;
					delay = 0.1f;
                    gameStarted = true;
                }
            }
        }

        // Render the main menu
        window.clear(sf::Color::Black);
        window.draw(easyButton);
        window.draw(mediumButton);
        window.draw(hardButton);
        window.display();
    }

    // Initialize the player with selected difficulty settings
    Player player("assets/player.png", "assets/laser.png", playerSpeed, laserSpeed);

    // Create the AlienManager with selected difficulty settings
    AlienManager alienManager(alienRows, alienCols, "assets/alien.png", window.getSize(), delay);

    // Main game loop
    sf::Clock clock; // To track frame time for smooth movement
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Get delta time
        float deltaTime = clock.restart().asSeconds();

        // Update the player
        player.move(deltaTime, window.getSize());
        player.shoot();                   // Check for shooting
        player.update(deltaTime);         // Update laser positions

        // Update the alien manager (moves aliens and handles direction)
        alienManager.update(deltaTime, window.getSize());
        alienManager.checkCollisions(player);

        // Render the game
        window.clear(sf::Color::Black); // Clear the screen with a black color
        player.draw(window);           // Draw the player
        alienManager.draw(window);     // Draw all aliens using AlienManager
        window.display();              // Display the current frame
    }

    return 0;
}
