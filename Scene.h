//Libraries
#pragma once

/*-----------------------------------Class main-----------------------------------------*/
class Scene {
    //Methods
    public:
        //Class virtual destructor
        virtual ~Scene() = default;
        //Method for process all logic
        virtual void Update() = 0;
        //Method for process all graphics
        virtual void Draw() = 0;
    
    private:

};