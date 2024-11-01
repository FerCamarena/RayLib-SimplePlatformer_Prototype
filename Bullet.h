//Libraries
#pragma once
#include "raylib.h"

/*-----------------------------------Main class-----------------------------------------*/
class Bullet {
    //Attributes
    public:
        //Variables for graphic rendering
        Texture2D texture;
        Rectangle area = {0, 0};
        Vector2 position = {0, 0};
        Vector2 areaPivot = {0, 0};
        float rotation = 0.0f;
        //Variables for movement logic
        Vector2 direction = {0, 0};
        float speed = 10.0f;
        //Variables to store current state
        bool enabled = true;
        
    private:

    //Methods
    public:
        //Class constructor to create an instance
        Bullet(Texture2D, Vector2, Vector2, float);
        //Method for process all logic
        void Update();
        //Method for process all graphics
        void Draw() const;

    private:
        //Method called once for initialize default values
        void Initialize();

};