//Libraries
#pragma once
#include "raylib.h"
#include "Scene.h"

/*-----------------------------------Class main-----------------------------------------*/
class Level_01 : public Scene {
    //Methods
    public:
        //Class constructors to create an instance
        Level_01();
        //Class virtual destructor
        virtual ~Level_01() = default;
        //Method for process all logic
        void Update() override;
        //Method for process all graphics
        void Draw() override;

    private:

};