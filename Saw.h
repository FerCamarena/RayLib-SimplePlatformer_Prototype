//Libraries
#pragma once
#include "Entity.h"
#include "Tilemap.h"

/*-----------------------------------Main class-----------------------------------------*/
class Saw : public Entity {
    //Attributes
    public:
        //Variables for graphic rendering
        Rectangle area = {
            0.0f, 0.0f,
            (float)texture.width, (float)texture.height
        };
        //Variables to store current states
        bool stuck = false;
        
    private:

    //Methods
    public:
        //Class constructors to create an instance
        Saw(Texture2D, Vector2, Vector2, Tilemap&);
        //Method for process all logic
        void Update() override;

    private:

};