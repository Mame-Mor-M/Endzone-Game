#pragma once
#include "scene.hpp"


class MidfieldScene : public Scene 
{
	protected:
		std::string name = "Midfield";
	public:
		void Load() override;
		void Update(float dt) override;

		std::vector<sf::Vector2f> GetEnemyPositions();
		void SetEnemyPosition(int index, sf::Vector2f position);
		void SpawnEnemy(int num);
		void DespawnEnemy(int index);
		std::vector<float> GetEnemySpeeds();
	private:
		std::map<int, NPC> npcs{};
		std::vector<sf::Vector2f> enemyPositions;
		std::vector<float> enemySpeeds;
};