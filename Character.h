//Libraries
#pragma once
#include "raylib.h"
#include "Tilemap.h"

/*-----------------------------------Main class-----------------------------------------*/
class Character {
    //Attributes
    public:
        //Variables for environment reference
        const Tilemap& level;
        //Variables for graphic rendering
        Texture2D texture = LoadTexture("./assets/Entities/spritesheet_characters.png");
        Rectangle area = {0.0f, 0.0f, 64.0f, 64.0f};
        Vector2 position = {650.0f, 400.0f};
        Vector2 size = {20.0f, 52.0f};
        Vector2 half = {(this->size.x * 0.5f), (this->size.y * 0.5f)};
        Vector2 areaPivot = {0.0f, 0.0f};
        float rotation = 0.0f;
        //Variables for movement logic
        Vector2 velocity = {0.0f, 0.0f};
        Vector2 acceleration = {0.0f, 0.0f};
        Vector2 direction = {0.0f, 0.0f};
        //Variables to store current states
        bool alive = true;
        bool onward = false;
        bool sliding = false;
        //Variables for controlling animatons
        int textureSize = 64;
        int animationState = 0;
        int animationRate = 20;
        int frameLimit = 1;
        int frameCount = 0;
        
    private:

    //Methods
    public:
        //Class constructor to create an instance
        Character(Texture2D, Vector2, Vector2, Tilemap&);
        //Method for process all logic
        void Update();
        //Method for process all graphics
        void Draw() const;

    private:
        //Method called once for initialize default values
        void Initialize();

};