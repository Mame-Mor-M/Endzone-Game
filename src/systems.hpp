#pragma once
#include "gameState.hpp"
#include "sceneManager.hpp"
#include <SFML/Window/Event.hpp>

struct NPC;

class PlayerMovement {
public:
    void update(GameState& state, float dt);
};
class SceneChange {
public:
    void update(GameState& state, SceneManager& scene);
};

class ReduceHealth {
public:
    void update(GameState& state, int posIndex, int amount, SceneManager& scene);
};

class ReduceDowns {
public:
    void update(GameState& state, int posIndex, SceneManager& scene);
};

class EnemySpawner {
public:
    void update(GameState& state, int enemyNum, SceneManager& scene);
    void despawn(int index, SceneManager& scene);
};

class EnemyMovement {
public:
    void update(GameState& state, float dt, SceneManager& sceneManager);
};

class EnemyOverlap {
public:
    void update(GameState& state, int posIndex, SceneManager& scene);
};

class NPCOverlap {
public:
    void update(GameState& state, SceneManager& scene);
};


class MenuSystem {
public:
    void handleEvent(GameState& state, const sf::Event& event, SceneManager& scene);
    void calculateResult(GameState& state, SceneManager& scene);
};

