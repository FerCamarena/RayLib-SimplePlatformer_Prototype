//Libraries
#pragma once
#include "raylib.h"

/*-----------------------------------Main class-----------------------------------------*/
class Sprite {
    //Attributes
    public:
        //Variables for graphic rendering
        Texture2D texture;
        Rectangle scaledArea = {0.0f, 0.0f, 16.0f, 16.0f};
        Vector2 position = {0.0f, 0.0f};
        Vector2 size = {64.0f, 64.0f};
        Rectangle spriteArea = {0.0f, 0.0f, size.x, size.y};
        Vector2 areaPivot = {0.0f, 0.0f};
        float rotation = 0.0f;
        
    private:

    //Methods
    public:
        //Class constructor to create an instance
        Sprite(Texture2D, Vector2, Vector2);
        //Method for process all logic
        virtual void Update() = 0;
        //Method for process all graphics
        virtual void Draw() const = 0;

    private:

};