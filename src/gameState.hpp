#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

struct GameState {
    sf::Vector2f playerPosition{ 400.f, 300.f };
    sf::Vector2f enemyPosition{ 300.f, 400.f };
    std::vector<sf::Vector2f> enemyPositions;

    int playerMoveDir = 0;
     void getState();
};