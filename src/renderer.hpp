#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.hpp"


class SceneManager;

class Renderer {
public:
    Renderer();
    void draw(sf::RenderWindow& window, const GameState& state, SceneManager& sceneManager);
    void drawDownPrompt(sf::RenderWindow& window, const GameState& state);
    void drawPlayPrompt(sf::RenderWindow& window, const GameState& state);
    void drawResultPrompt(sf::RenderWindow& window, const GameState& state);

private:
    sf::CircleShape playerShape{ 40.f };
    sf::Font font;

    int GenerateRandomNumber(int a, int b);
};