//Libraries
#pragma once
#include "raylib.h"

/*-----------------------------------Main class-----------------------------------------*/
class Sprite {
    //Attributes
    public:
        //Variables for graphic rendering
        Texture2D texture;
        Rectangle sprite = {0.0f, 0.0f, 64.0f, 64.0f};
        Rectangle area = {0.0f, 0.0f, 64.0f, 64.0f};
        Vector2 position = {0.0f, 0.0f};
        Vector2 size = {64.0f, 64.0f};
        Vector2 pivot = {sprite.width / 2, sprite.height};
        float rotation = 0.0f;
        
    private:

    //Methods
    public:
        //Class constructors to create an instance
        Sprite(Texture2D, Vector2, Vector2);
        //Class virtual destructor
        virtual ~Sprite() = default;
        //Method for process all logic
        virtual void Update() = 0;
        //Method for process all graphics
        virtual void Draw() const = 0;

    private:

};