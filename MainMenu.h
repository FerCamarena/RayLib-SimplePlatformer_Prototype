//Libraries
#pragma once
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
        void Draw() const override;
        
    private:

};