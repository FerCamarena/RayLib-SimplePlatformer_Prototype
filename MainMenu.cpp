//Base class
#include "MainMenu.h"

//User libraries
#include "SceneManager.h"

//Class constructors to create an instance
MainMenu::MainMenu() {}

//Method for process all logic
void MainMenu::Update() {
    //Checking for user inputs to make transitions
    if (IsKeyPressed(KEY_ONE)) {
        SceneManager::ChangeScene(3);
    } else if (IsKeyPressed(KEY_TWO)) {
        SceneManager::ChangeScene(4);
    }
}

//Method for process all graphics
void MainMenu::Draw() const {
    DrawText("MAIN MENU", 100, 100, 20, WHITE);
    DrawText("Press ONE to Start level 1", 100, 120, 20, WHITE);
    DrawText("Press TWO to Start level 1", 100, 140, 20, WHITE);
}