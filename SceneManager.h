//Libraries
#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "raylib.h"
#include "Scene.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "GameDone.h"
#include "Level_01.h"
#include "Level_02.h"

/*-----------------------------------Class main-----------------------------------------*/
class SceneManager {
    //Attributes
    public:

    private:
        //Scene variables
        static std::unique_ptr<Scene> currentScene;
        static std::vector<std::function<std::unique_ptr<Scene>()>> builtScenes;

    //Methods
    public:
        //Class constructors to create an instance
        SceneManager();
        //Class virtual destructor
        virtual ~SceneManager() = default;
        //Method for process all logic
        static void Update();
        //Method for process all graphics
        static void Draw();
        //Method for handling scene transitions
        static void ChangeScene(int);

    private:

};