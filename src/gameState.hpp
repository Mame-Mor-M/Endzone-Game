#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include<map>
#include<string>

struct NPC {
    std::string name;
    float x;
    float y;
};

enum class MenuState {
    None,
    Paused,
    Prompt,
};

struct GameState {
    sf::Vector2f playerPosition{ 400.f, 300.f };
    sf::Vector2f enemyPosition{ 300.f, 400.f };
    std::vector<sf::Vector2f> enemyPositions;
    std::vector<float> enemySpeeds;
    std::map<int, NPC> npcs{};

    int playerDowns = 4;
    int playerHealth = 100;
    int totalPoints = 0;
    int totalYards = 0; // Spendable, this is the in-game currency
    int pointMultiplier = 1;

    bool gameOver = false;

    int playerMoveDir = 0;

    MenuState currentMenu = MenuState::None;
    int menuSelection = 0; // 0 = first option, 1 = second option
    int enemyIndex = -1;
    void getState();
};

