#pragma once
#include "gameState.hpp"

class PlayerMovement {
public:
    void update(GameState& state, float dt);
};

class EnemySpawner {
public:
    void update(GameState& state, float dt);
};

class EnemyMovement {
public:
    void update(GameState& state, float dt);
};

