//Libraries
#pragma once
#include "raylib.h"
#include "Scene.h"

/*-----------------------------------Class main-----------------------------------------*/
class MainMenu : public Scene {
    //Methods
    public:
        //Class constructors to create an instance
        MainMenu();
        //Class virtual destructor
        virtual ~MainMenu() = default;
        //Method for process all logic
        void Update() override;
        //Method for process all graphics
        void Draw() override;
        
    private:

};