#include "gameState.hpp"
void GameState::getState() {
    sf::Vector2f playerPosition;
    
    int playerDowns;
    int playerHealth;
    int totalPoints;
    int totalYards; // Spendable, this is the in-game currency
    int pointMultiplier;
    int playerMoveDir;

    bool gameOver;

    sf::Vector2f enemyPosition;
    std::vector<sf::Vector2f> enemyPositions;
    std::vector<float> enemySpeeds;
    std::map<int, NPC> npcs;

    
};