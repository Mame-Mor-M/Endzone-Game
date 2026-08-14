#include "sidelineScene.hpp"
#include <iostream>

void SidelineScene::Load() {
	npcs[1] = std::make_unique<NPC>("Coach", 360, 20);
	npcs[2] = std::make_unique<NPC>("Trainer", 700, 250);
	npcs[3] = std::make_unique<NPC>("Water Boy", 360, 500);

	name = "Sideline";
}

void SidelineScene::Update(float dt) {

}

const std::map<int, std::unique_ptr<Scene::NPC>>& SidelineScene::GetNPCs() {
	return npcs;
}

std::vector<float> SidelineScene::GetEnemySpeeds() {
	return enemySpeeds;
}

std::vector<sf::Vector2f> SidelineScene::GetEnemyPositions() {
	return enemyPositions;
}

