//Libraries
#pragma once
#include "Sprite.h"
#include "Tilemap.h"

/*-----------------------------------Main class-----------------------------------------*/
class Entity : public Sprite {
    //Attributes
    public:
        //Variables for environment reference
        const Tilemap& level;
        //Variables for movement logic
        Vector2 velocity = {0.0f, 0.0f};
        Vector2 acceleration = {0.0f, 0.0f};
        Vector2 direction = {0.0f, 0.0f};
        //Variables to store current states
        bool alive = true;
        bool onward = false;
        //Variables for controlling animatons
        int textureSize = 64;
        int animationState = 0;
        int animationRate = 20;
        int frameLimit = 1;
        int frameCount = 0;
        
    private:

    //Methods
    public:
        Entity(Texture2D, Vector2, Vector2, Tilemap&);
        //Method for process all logic
        virtual void Update() override = 0;
        //Method for process all graphics
        virtual void Draw() const override = 0;

    private:

};