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

class IncreaseHealth {
public:
    void update(GameState& state, int amount);
};

class ReduceDowns {
public:
    void update(GameState& state, int posIndex, SceneManager& scene);
};

class IncreaseDowns {
public:
    void update(GameState& state, int amount);
};

class IncreasePoints {
public:
    void update(GameState& state, int amount);
};

class ResetStats {
public:
    void update(GameState& state);
};

class IncreaseYards {
public:
    void update(GameState& state, int amount);
};

class DecreaseYards {
public:
    void update(GameState& state, int amount);
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

class EnemyRoll {
public:
    void update(GameState& state); // Call ReduceHealth in here based on the enemies rolled tackle rating.
};

class JudgeEncounter {
public:
    void update(GameState& state);
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

class RollNumber {
public:
    int update(int min, int max);
};

