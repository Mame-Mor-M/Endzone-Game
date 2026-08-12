#include "sceneManager.hpp"
#include <iostream>

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}

void SceneManager::SetCurrentScene(int sceneIndex) {
	switch (sceneIndex) {
	case (0):
		currentScene = new SidelineScene();
		currentLevel = Level::Sideline;
		break;
	case(1):
		currentScene = new MidfieldScene();
		currentLevel = Level::Midfield;
		break;
	}
	currentScene->Load();
	std::cout << "Changed level";
	
}