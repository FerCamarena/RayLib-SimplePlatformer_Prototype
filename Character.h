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
        Rectangle area = {
            0.0f, 0.0f,
            (float)texture.width, (float)texture.height
        };
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
        //Method for process all graphics
        void Draw() const override;

    private:

};