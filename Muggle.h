//Libraries
#pragma once
#include "raylib.h"
#include "Tilemap.h"

/*-----------------------------------Main class-----------------------------------------*/
class Muggle {
    //Attributes
    public:
        //Variables for graphic rendering
        Texture2D texture;
        Rectangle area = {0.0f, 0.0f, 64.0f, 64.0f};
        Vector2 size = {32, 52};
        Vector2 position = {800, 400};
        Vector2 areaPivot = {0, 0};
        float rotation = 0.0f;
        //Variables for movement logic
        Vector2 velocity = {0, 0};
        Vector2 acceleration = {0, 0};
        Vector2 direction = {0, 0};
        //Variables to store current states
        bool alive = true;
        bool onward = true;
        //Variables for environment reference
        const Tilemap& level;
        
    private:

    //Methods
    public:
        //Class constructor to create an instance
        Muggle(Texture2D, Vector2, Vector2, Tilemap&);
        //Method for process all logic
        void Update();
        //Method for process all graphics
        void Draw() const;

    private:
        //Method called once for initialize default values
        void Initialize();

};