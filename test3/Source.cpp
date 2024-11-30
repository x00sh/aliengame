#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AlienManager.h" // Include the AlienManager class header

int main() {
    // Window dimensions
    const int windowWidth = 800;
    const int windowHeight = 600;

    // Create a window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Alien Game");

    // Initialize the player
    Player player("assets/player.png", 300.0f, sf::Vector2f(windowWidth / 2 - 25, windowHeight - 100));

    // Create the AlienManager with 2 rows and 8 columns of aliens
    AlienManager alienManager(3, 8, "assets/alien.png", window.getSize(), 0.0f);

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

        // Update the alien manager (moves aliens and handles direction)
        alienManager.update(deltaTime, window.getSize());

        // Render the game
        window.clear(sf::Color::Black); // Clear the screen with a black color
        player.draw(window);           // Draw the player
        alienManager.draw(window);     // Draw all aliens using AlienManager
        window.display();              // Display the current frame
    }

    return 0;
}
