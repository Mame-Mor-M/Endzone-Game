#pragma once
#include "../managers/scene.hpp"



class SidelineScene : public Scene 
{
	protected:
		std::string name = "Sideline";
	public:
		void Load() override;
		void Update(float dt) override;

		std::vector<sf::Vector2f> GetEnemyPositions();
		const std::map<int, std::unique_ptr<NPC>>& GetNPCs();
		std::vector<float> GetEnemySpeeds();
	private:
		std::map<int, std::unique_ptr<NPC>> npcs{};
		std::vector<sf::Vector2f> enemyPositions;
		std::vector<float> enemySpeeds;
};