#include "scene.hpp"
#include "sidelineScene.hpp"
#include "midfieldScene.hpp"

enum Level {
    Sideline,
    Midfield,
    BeforeMidfield,
    AfterMidfield
};

class SceneManager {
public:
    Scene* GetCurrentScene();
    void SetCurrentScene(int sceneIndex);
    Level currentLevel = Level::Midfield;
private:
    Scene* currentScene = new MidfieldScene();
};