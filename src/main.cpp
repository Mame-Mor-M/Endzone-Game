#include <SFML/Graphics.hpp>
#include "gameState.hpp"
#include "systems.hpp"
#include "renderer.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Game");

    GameState state;
    MenuSystem menuSystem;
    PlayerMovement movementSystem;
    EnemyMovement enemyMovement;
    EnemySpawner enemySpawner;
    Renderer renderer;

    enemySpawner.update(state, 4);

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            
            menuSystem.handleEvent(state, *event);
        }

        if (state.gameOver == false && state.currentMenu == MenuState::None) {
            movementSystem.update(state, dt);
            enemyMovement.update(state, dt);
            
        }

        

        // Render
        window.clear();
        renderer.draw(window, state);
        renderer.drawPrompt(window, state);
        window.display();
    }
}