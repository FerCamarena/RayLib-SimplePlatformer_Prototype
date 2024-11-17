//Libraries
#pragma once
#include <vector>
#include <memory>
#include "raylib.h"
#include "Scene.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "GameWon.h"
#include "Level_01.h"
#include "Level_02.h"

/*-----------------------------------Class main-----------------------------------------*/
class SceneManager {
    //Attributes
    public:

    private:
        //Scene variables
        static std::unique_ptr<Scene> currentScene;

    //Methods
    public:
        //Method for handling scene transitions
        static void ChangeScene(std::unique_ptr<Scene> newScene);
        //Method for process all logic
        static void Update();
        //Method for process all graphics
        static void Draw();

    private:

};