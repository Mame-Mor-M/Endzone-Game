#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.hpp"

class Renderer {
public:
    Renderer();
    void draw(sf::RenderWindow& window, const GameState& state);
    void drawPrompt(sf::RenderWindow& window, const GameState& state);

private:
    sf::CircleShape playerShape{ 40.f };
    sf::RectangleShape enemyShape;
    sf::Font font;

    int GenerateRandomNumber(int a, int b);
};