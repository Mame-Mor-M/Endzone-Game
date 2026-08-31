#include "opposingTerritoryScene.hpp"
#include <iostream>
#include <random>

void OpposingTerritoryScene::Load() {
	name = "OpposingTerritory";

    SpawnEnemy(4);

}

void OpposingTerritoryScene::Update(float dt) {

}

void OpposingTerritoryScene::SpawnEnemy(int enemyNum) {
    static std::mt19937 gen(std::random_device{}()); // Create generator once so we don't make a new one every call
    std::uniform_int_distribution<> distribX(100, 600); // Distrib transforms the random unsigned int (no defined datatype so it could be anything)
    std::uniform_int_distribution<> distribY(50, 100);
    for (int i = 0; i < enemyNum; i++) {
        sf::Vector2f pos;
        pos.x = distribX(gen);
        pos.y = distribY(gen);

        enemyPositions.push_back(pos);

    }

    std::uniform_int_distribution<> distribSpeed(100, 300);

    for (int i = 0; i < enemyNum; i++) {
        sf::Vector2f pos;
        float speed = distribSpeed(gen);
        enemySpeeds.push_back(speed);
    }
}

void OpposingTerritoryScene::SetEnemyPosition(int index, sf::Vector2f position) {
    enemyPositions[index] = position;
}

std::vector<float> OpposingTerritoryScene::GetEnemySpeeds() {
	return enemySpeeds;
}

void OpposingTerritoryScene::DespawnEnemy(int index) {
    enemyPositions.erase(enemyPositions.begin() + index);
    enemySpeeds.erase(enemySpeeds.begin() + index);
}

std::vector<sf::Vector2f> OpposingTerritoryScene::GetEnemyPositions() {
	return enemyPositions;
}

