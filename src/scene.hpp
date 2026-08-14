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

		NPC(std::string name, float x, float y) : name(name), x(x), y(y) {}
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