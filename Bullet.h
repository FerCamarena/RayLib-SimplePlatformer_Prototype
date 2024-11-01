//Libraries
#pragma once
#include "raylib.h"

/*-----------------------------------Main class-----------------------------------------*/
class Bullet {
    //Attributes
    public:
        //Variable to store current bullet state
        bool enabled = false;
        //Variable for graphic rendering
        Texture2D texture;
        Vector2 position = {0, 0};
        Vector2 size = {0, 0};
        //Variable for movement logic
        Vector2 direction = {0, 0};
        float speed = 10.0f;
        
    private:

    //Methods
    public:
        //Method for process all bullet logic
        void Update();

        //Method for process all bullet graphics
        void Draw();

    private:
        //Class constructor to create a bullet instance
        Bullet(Texture2D, Vector2, Vector2, float, bool);
};