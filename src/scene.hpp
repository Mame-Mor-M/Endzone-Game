#pragma once
#include "renderer.hpp"

class Scene {
protected:
	std::string name = "";
public:

	struct NPC {
		std::string name;
		float x = 0.f;
		float y = 0.f;
	};


	virtual ~Scene() = default;

	virtual void Load() = 0;
	virtual void Update(float dt) = 0;


	virtual std::vector<sf::Vector2f> GetEnemyPositions() { return {}; };
	virtual void SetEnemyPosition(int index, sf::Vector2f position) {};
	virtual void SpawnEnemy(int num) {};
	virtual void DespawnEnemy(int index) {};
	virtual std::map<int, NPC> GetNPCs() { return {}; };
	virtual std::vector<float> GetEnemySpeeds() { return {}; };
};