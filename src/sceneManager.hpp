#include "scene.hpp"
#include "sidelineScene.hpp"
#include "midfieldScene.hpp"
#include "ownTerritoryScene.hpp"
#include "opposingTerritoryScene.hpp"

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
    Level currentLevel = Level::OwnTerritory;
private:
    Scene* currentScene = new OwnTerritoryScene();
};