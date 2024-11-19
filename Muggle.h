//Libraries
#pragma once

//User libraries
#include "Entity.h"

/*-----------------------------------Main class-----------------------------------------*/
class Muggle : public Entity {
    //Attributes
    public:
        
    private:

    //Methods
    public:
        //Class constructors to create an instance
        Muggle(Texture2D, Vector2, Vector2, Tilemap&);
        Muggle(Vector2, Vector2, Tilemap&);
        //Class virtual destructor
        virtual ~Muggle() = default;
        //Method for process all logic
        void Update() override;

    private:

};