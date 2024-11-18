//Base class
#include "GameOver.h"

//User libraries
#include "SceneManager.h"

//Class constructors to create an instance
GameOver::GameOver() {}

//Method for process all logic
void GameOver::Update() {
    //Checking for inputs to start a new game
    if (IsKeyPressed(KEY_ENTER)) {
        SceneManager::ChangeScene(0);
    } else if (IsKeyPressed(KEY_R)) {
        SceneManager::ChangeScene(3);
    }
}

//Method for process all graphics
void GameOver::Draw() const {
    DrawText("GAME OVER", 100, 100, 20, DARKGRAY);
    DrawText("Press R to Retry level 1", 100, 120, 20, DARKGRAY);
    DrawText("Press ENTER to Return to Menu", 100, 140, 20, DARKGRAY);
}