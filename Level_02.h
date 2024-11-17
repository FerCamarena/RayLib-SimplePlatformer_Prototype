//Libraries
#pragma once
#include "raylib.h"
#include "Scene.h"

/*-----------------------------------Class main-----------------------------------------*/
class Level_02 : public Scene {
    //Methods
    public:
        //Class constructors to create an instance
        Level_02();
        //Class virtual destructor
        virtual ~Level_02() = default;
        //Method for process all logic
        void Update() override;
        //Method for process all graphics
        void Draw() override;
        
    private:

};