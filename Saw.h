//Libraries
#pragma once
#include "Entity.h"
#include "Tilemap.h"

/*-----------------------------------Main class-----------------------------------------*/
class Saw : public Entity {
    //Attributes
    public:
        //Variables for graphic rendering
        Texture2D texture = LoadTexture("./assets/Entities/spritesheet_enemy_saw.png");
        //Variables to store current states
        bool stuck = false;
        
    private:

    //Methods
    public:
        //Class constructors to create an instance
        Saw(Texture2D, Vector2, Vector2, Tilemap&);
        Saw(Vector2, Vector2, Tilemap&);
        //Method for process all logic
        void Update() override;

    private:

};