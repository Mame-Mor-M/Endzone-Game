#pragma once
#include "scene.hpp"



class SidelineScene : public Scene 
{
	protected:
		std::string name = "Sideline";
	public:
		void Load() override;
		void Update(float dt) override;

		std::vector<sf::Vector2f> GetEnemyPositions();
		std::map<int, NPC> GetNPCs();
		std::vector<float> GetEnemySpeeds();
	private:
		std::map<int, NPC> npcs{};
		std::vector<sf::Vector2f> enemyPositions;
		std::vector<float> enemySpeeds;
};