//Base class
#include "GameDone.h"

//User libraries
#include "SceneManager.h"

//Class constructors to create an instance
GameDone::GameDone() {}

//Method for process all logic
void GameDone::Update() {
}

//Method for process all graphics
void GameDone::Draw() const {
    DrawText("LEVEL DONE", 100, 100, 20, DARKGRAY);
    DrawText("Press R to Retry level 1", 100, 120, 20, DARKGRAY);
    DrawText("Press ENTER to Return to Menu", 100, 140, 20, DARKGRAY);
    DrawText("Press SPACE to Start level 2", 100, 160, 20, DARKGRAY);
}