#include "scene.hpp"
#include "../levels/sidelineScene.hpp"
#include "../levels/midfieldScene.hpp"
#include "../levels/ownTerritoryScene.hpp"
#include "../levels/opposingTerritoryScene.hpp"

enum Level {
    Sideline,
    OwnTerritory,
    Midfield,
    OpposingTerritory,
    Count
};

class SceneManager {
public:
    Scene* GetCurrentScene();
    void SetCurrentScene(int sceneIndex);
    Level currentLevel = Level::Sideline;
private:
    Scene* currentScene = new SidelineScene();
};