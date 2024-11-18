//Base class
#include "MainMenu.h"

//User libraries
#include "SceneManager.h"

//Class constructors to create an instance
MainMenu::MainMenu() {}

//Method for process all logic
void MainMenu::Update() {

//Method for process all graphics
void MainMenu::Draw() const {
    DrawText("MAIN MENU", 100, 100, 20, WHITE);
    DrawText("Press SPACE to Start level 1", 100, 120, 20, WHITE);
}