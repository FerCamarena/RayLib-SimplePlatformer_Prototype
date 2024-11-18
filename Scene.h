//Libraries
#pragma once
#include "raylib.h"
#include "raymath.h"

/*-----------------------------------Class main-----------------------------------------*/
class Scene {
    //Methods
    public:
        //Class virtual destructor
        virtual ~Scene() = default;
        //Method for process all logic
        virtual void Update() = 0;
        //Method for process all graphics
        virtual void Draw() const = 0;
    
    private:

};