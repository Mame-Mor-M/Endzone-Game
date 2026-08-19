#include <SFML/Graphics.hpp>
#include "gameState.hpp"
#include "systems.hpp"
#include "renderer.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Game");

    GameState state;
    MenuSystem menuSystem;
    SceneManager sceneManager;
    PlayerMovement movementSystem;
    EnemyMovement enemyMovement;
    EnemySpawner enemySpawner;
    Renderer renderer;
    SceneChange sceneChanger;
    NPCOverlap npcInteraction;

    //enemySpawner.update(state, 2, sceneManager);

    sf::Clock clock;
    sceneManager.GetCurrentScene()->Load();

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            
            menuSystem.handleEvent(state, *event, sceneManager);
        }

        if (state.gameOver == false && state.currentMenu == MenuState::None) {
            movementSystem.update(state, dt);
            enemyMovement.update(state, dt, sceneManager);
            npcInteraction.update(state, sceneManager);
            
        }

        sceneChanger.update(state, sceneManager);
        

        // Render
        window.clear();
        renderer.draw(window, state, sceneManager);

        if (state.currentMenu == MenuState::DownPrompt) {
            renderer.drawDownPrompt(window, state);
        }

        if (state.currentMenu == MenuState::PlayPrompt) {
            renderer.drawPlayPrompt(window, state);
        }

        if (state.currentMenu == MenuState::ResultPrompt) {
            renderer.drawResultPrompt(window, state);
        }
        if (state.currentMenu == MenuState::LevelPrompt) {
            renderer.drawChangeLevelPrompt(window, state, sceneManager);
        }
        if (state.currentMenu == MenuState::NPCPrompt) {
            renderer.drawNPCPrompt(window, state);
        }
        
        window.display();
    }
}