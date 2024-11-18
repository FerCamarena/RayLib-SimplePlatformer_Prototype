//Libraries
#include "SceneManager.h"

//Class static parameters
std::unique_ptr<Scene> SceneManager::currentScene = nullptr;

// Vector of scene factories (lambdas)
std::vector<std::function<std::unique_ptr<Scene>()>> SceneManager::builtScenes = {
    []() { return std::make_unique<MainMenu>(); },
    []() { return std::make_unique<GameOver>(); },
    []() { return std::make_unique<GameDone>(); },
    []() { return std::make_unique<Level_01>(); },
    []() { return std::make_unique<Level_02>(); },
};

//Class constructors to create an instance
SceneManager::SceneManager() {
    //Loading first main menu scene
    currentScene = builtScenes[0]();
}

//Method for process all logic
void SceneManager::Update() {
    //Updating scenes accordingly
    if (currentScene) {
        currentScene->Update();
    }
}

//Method for process all graphics
void SceneManager::Draw() {
    //Drawing scenes accordingly
    if (currentScene) {
        currentScene->Draw();
    }
}

//Method for globally changing scenes
void SceneManager::ChangeScene(int newSceneIndex) {
    //Creating new scene from index
    if (newSceneIndex >= 0 && newSceneIndex < builtScenes.size()) {
        currentScene = builtScenes[newSceneIndex]();
    }
}