#include <SFML/Graphics.hpp>
#include "gameState.hpp"
#include "systems.hpp"
#include "renderer.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Game");

    GameState state;
    PlayerMovement movementSystem;
    EnemyMovement enemyMovement;
    Renderer renderer;

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Update logic
        movementSystem.update(state, dt);
        enemyMovement.update(state, dt);
        

        // Render
        window.clear();
        renderer.draw(window, state);
        window.display();
    }
}