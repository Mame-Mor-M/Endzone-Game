#pragma once
#include "renderer.hpp"

class Scene {
protected:
	std::string npcType = "";
public:
	struct NPC {
		NPCTypes npcType;
		float x = 0.f;
		float y = 0.f;

		NPC(NPCTypes npcType, float x, float y) : npcType(npcType), x(x), y(y) {}
	};


	virtual ~Scene() = default;

	virtual void Load() = 0;
	virtual void Update(float dt) = 0;


	virtual std::vector<sf::Vector2f> GetEnemyPositions() { return {}; };
	virtual void SetEnemyPosition(int index, sf::Vector2f position) {};
	virtual void SpawnEnemy(int num) {};
	virtual void DespawnEnemy(int index) {};
	virtual const std::map<int, std::unique_ptr<NPC>>& GetNPCs() { return {}; };
	virtual std::vector<float> GetEnemySpeeds() { return {}; };
};