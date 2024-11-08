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
        Rectangle hitbox = {
            this->position.x - (this->size.x / 2), this->position.y - this->size.y,
            (float)this->size.x, (float)this->size.y
        };
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
        //Class constructors to create an instance
        Entity(Texture2D, Vector2, Vector2, Tilemap&);
        //Class virtual destructor
        virtual ~Entity() = default;
        //Method for process all logic
        virtual void Update() override;
        //Method for process all graphics
        virtual void Draw() const override;

    private:

};