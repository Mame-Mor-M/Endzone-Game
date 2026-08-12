#include "sidelineScene.hpp"
#include <iostream>

void SidelineScene::Load() {
	npcs[0] = { "Coach", 200.f, 100.f };
	name = "Sideline";
}

void SidelineScene::Update(float dt) {

}

std::vector<float> SidelineScene::GetEnemySpeeds() {
	return enemySpeeds;
}

std::vector<sf::Vector2f> SidelineScene::GetEnemyPositions() {
	return enemyPositions;
}

