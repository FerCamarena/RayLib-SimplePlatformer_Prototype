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
        Rectangle size = {0, 0};
        Vector2 position = {0, 0};
        Vector2 areaPivot = {0, 0};
        //Variable for movement logic
        Vector2 direction = {0, 0};
        float speed = 10.0f;
        //Variable for storing graphic effects
        float rotation = 0.0f;
        
    private:

    //Methods
    public:
        //Class constructor to create a bullet instance
        Bullet(Texture2D, Vector2, Vector2, float, bool);
        //Method for process all bullet logic
        void Update();
        //Method for process all bullet graphics
        void Draw() const;

    private:
        //Method called once for initialize default values
        void Initialize();

};