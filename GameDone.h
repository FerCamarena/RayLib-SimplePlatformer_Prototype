//Libraries
#pragma once

//User libraries
#include "Scene.h"

/*-----------------------------------Class main-----------------------------------------*/
class GameDone : public Scene {
    //Methods
    public:
        //Class constructors to create an instance
        GameDone();
        //Class virtual destructor
        virtual ~GameDone() = default;
        //Method for process all logic
        void Update() override;
        //Method for process all graphics
        void Draw() const override;
        
    private:

};