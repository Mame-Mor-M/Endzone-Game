#include "gameState.hpp"
void GameState::getState() {
    sf::Vector2f playerPosition;
    
    int playerDowns;
    int playerHealth; // Same as player durability in old version of Endzone
    int healthLost;
    int totalPoints;
    int totalYards; // Spendable, this is the in-game currency
    int pointMultiplier;
    int playerMoveDir;

    bool gameOver;
    bool successfulEncounter;

    std::vector<sf::Vector2f> enemyPositions;
    std::vector<float> enemySpeeds;
    std::map<int, NPC> npcs;

    
};