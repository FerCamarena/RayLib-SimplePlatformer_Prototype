//Libraries
#pragma once
#include "raylib.h"
#include "Sprite.h"

/*-----------------------------------Main class-----------------------------------------*/
class Bullet : public Sprite {
    //Attributes
    public:
        //Variables for movement logic
        Vector2 direction = {0.0f, 0.0f};
        float speed = 10.0f;
        //Variables to store current state
        bool enabled = true;
        
    private:

    //Methods
    public:
        //Class constructor to create an instance
        Bullet(Texture2D, Vector2, Vector2, Vector2, float);
        //Method for process all logic
        void Update() override;
        //Method for process all graphics
        void Draw() const override;

    private:

};