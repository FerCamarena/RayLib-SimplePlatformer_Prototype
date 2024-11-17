//Libraries
#pragma once
#include "raylib.h"
#include "Scene.h"

/*-----------------------------------Class main-----------------------------------------*/
class GameWon : public Scene {
    //Methods
    public:
        //Class constructors to create an instance
        GameWon();
        //Class virtual destructor
        virtual ~GameWon() = default;
        //Method for process all logic
        void Update() override;
        //Method for process all graphics
        void Draw() override;
        
    private:

};