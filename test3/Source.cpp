#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AlienManager.h"


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
        player.update(deltaTime);   // Update laser positions

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
