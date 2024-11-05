//Libraries
#pragma once
#include "Entity.h"
#include "Tilemap.h"

/*-----------------------------------Main class-----------------------------------------*/
class Muggle : public Entity{
    //Attributes
    public:
        //Variables for graphic rendering
        Rectangle area = {
            0.0f, 0.0f,
            (float)texture.width, (float)texture.height
        };
        
    private:

    //Methods
    public:
        //Class constructor to create an instance
        Muggle(Texture2D, Vector2, Vector2, Tilemap&);
        //Method for process all logic
        void Update() override;
        //Method for process all graphics
        void Draw() const override;

    private:

};