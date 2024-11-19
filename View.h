//Libraries
#pragma once
#include "raylib.h"
#include "Character.h"

/*-----------------------------------Main class-----------------------------------------*/
class View {
    //Attributes
    public:
        //Variables for graphic rendering
        Camera2D& mainCamera;
        Character& player;
        Vector2 screenSize = {0.0f, 0.0f};
        Vector2 positionOffset = {0.0f, 0.0f};
        Vector2 upperFocus = {0.0f, 0.0f};
        Vector2 lowerFocus = {0.0f, 0.0f};
        Vector2 cameraAcceleration = {0.0f,0.0f};

    private:

    //Methods
    public:
        //Class constructor to create an instance
        View(Vector2, Camera2D&, Character&);
        //Method for process all logic
        void Update();

    private:
        //Method called once for initialize default values
        void Initialize();

};