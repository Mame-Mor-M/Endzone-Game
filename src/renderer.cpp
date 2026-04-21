#include "renderer.hpp"
#include <random>

int GenerateRandomNumber(int a, int b);
sf::RectangleShape CreateDefender();

Renderer::Renderer() {
    playerShape.setFillColor(sf::Color::Blue);
    enemyShape = CreateDefender();
}

void Renderer::draw(sf::RenderWindow& window, const GameState& state) {
    playerShape.setPosition(state.playerPosition);
    //state.enemyPositions.push_back(enemyShape.getPosition());
    enemyShape.setPosition(state.enemyPosition);
    window.draw(playerShape);
    window.draw(enemyShape);
}



sf::RectangleShape CreateDefender() {
    sf::RectangleShape enemy;
    enemy.setSize({ 30,30 });
    enemy.setOutlineColor(sf::Color::Red);
    enemy.setFillColor(sf::Color::Red);
    int x = GenerateRandomNumber(300, 700);
    int y = GenerateRandomNumber(300, 700);
    sf::Vector2f pos(x, y);
    enemy.setPosition(pos);
    return enemy;
}

// Don't use random pos for enemy yet
int GenerateRandomNumber(int a, int b) {
    static std::mt19937 gen(std::random_device{}()); // Create generator once so we don't make a new one every call
    std::uniform_int_distribution<> distrib(a, b); // Distrib transforms the random unsigned int (no defined datatype so it could be anything)

    return distrib(gen);
}
