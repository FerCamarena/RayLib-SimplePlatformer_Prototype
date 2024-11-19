//Libraries
#pragma once

//User libraries
#include "Entity.h"

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
        //Class virtual destructor
        virtual ~Saw() = default;
        //Method for process all logic
        void Update() override;

    private:

};