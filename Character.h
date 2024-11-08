//Libraries
#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Tilemap.h"

/*-----------------------------------Class main-----------------------------------------*/
class Character : public Entity {
    //Attributes
    public:
        //Variables for graphic rendering
        Vector2 half = {
            (this->size.x * 0.5f),
            (this->size.y * 0.5f)
        };
        //Variables to store current states
        bool sliding = false;
        
    private:

    //Methods
    public:
        //Class constructor to create an instance
        Character(Texture2D, Vector2, Vector2, Tilemap&);
        //Method for process all logic
        void Update() override;

    private:

};