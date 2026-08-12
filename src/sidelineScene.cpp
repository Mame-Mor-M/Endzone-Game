#include "sidelineScene.hpp"
#include <iostream>

void SidelineScene::Load() {
	npcs = { {1, {"Coach", 360,20}}, {2, {"Trainer", 700,250}}, {3, {"Water Boy", 360,500}} };
	name = "Sideline";
}

void SidelineScene::Update(float dt) {

}

std::map<int, Scene::NPC> SidelineScene::GetNPCs() {
	return npcs;
}

std::vector<float> SidelineScene::GetEnemySpeeds() {
	return enemySpeeds;
}

std::vector<sf::Vector2f> SidelineScene::GetEnemyPositions() {
	return enemyPositions;
}

