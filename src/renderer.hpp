#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.hpp"

class Renderer {
public:
    Renderer();
    void draw(sf::RenderWindow& window, const GameState& state);

private:
    sf::CircleShape playerShape{ 40.f };
    sf::RectangleShape enemyShape;

    int GenerateRandomNumber(int a, int b);
};