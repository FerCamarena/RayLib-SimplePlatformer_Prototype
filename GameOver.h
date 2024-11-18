//Libraries
#pragma once
#include "Scene.h"

/*-----------------------------------Class main-----------------------------------------*/
class GameOver : public Scene {
    //Methods
    public:
        //Class constructors to create an instance
        GameOver();
        //Class virtual destructor
        virtual ~GameOver() = default;
        //Method for process all logic
        void Update() override;
        //Method for process all graphics
        void Draw() const override;
        
    private:

};