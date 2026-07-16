#pragma once
#include "gameState.hpp"
#include <SFML/Window/Event.hpp>

class PlayerMovement {
public:
    void update(GameState& state, float dt);
};

class ReduceHealth {
public:
    void update(GameState& state, int posIndex);
};

class ReduceDowns {
public:
    void update(GameState& state, int posIndex);
};

class EnemySpawner {
public:
    void update(GameState& state, int enemyNum);
};

class EnemyMovement {
public:
    void update(GameState& state, float dt);
};

class EnemyOverlap {
public:
    void update(GameState& state, int posIndex);
};


class NPCSpawner {
public:
    void update(GameState& state, float dt);
};

class MenuSystem {
public:
    void handleEvent(GameState& state, const sf::Event& event);
};

