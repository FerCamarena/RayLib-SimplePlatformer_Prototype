//Libraries
#include "raylib.h"
#include "raymath.h"

//User libraries
#include "SceneManager.h"

/*-------------------------------------DEV NOTES----------------------------------------*/
//
//                      Project made by Fernando C. (v0.0.145-alpha)
//                      Simple platformer example using Raylib
//
/*--------------------------------------------------------------------------------------*/

/*--------------------------------Project properties------------------------------------*/

/*---------------------------------Custom functions-------------------------------------*/

/*-----------------------------------Main function--------------------------------------*/
int main(void) {
    //Initialization
    const Vector2 screenSize = {1280.0f, 720.0f};
    InitWindow((int)screenSize.x, (int)screenSize.y, "Base platformer - Prototype - Fernando C. - v0.0.145-alpha");
    SetTargetFPS(60);
    //Hiding cursor by default
    HideCursor();
    
    /*---------------------------------Game attributes--------------------------------------*/

    /*-------------------------------------Game loop----------------------------------------*/
    while (!WindowShouldClose()) {
        //Update scenes accordingly
        SceneManager::Update();

        /*-------------------------------------Draw phase---------------------------------------*/
        BeginDrawing();
            //Clearing the image with background color
            ClearBackground(PURPLE);
            //Draw scenes accordingly
            SceneManager::Draw();
        EndDrawing();
    }
    /*----------------------------------------End-------------------------------------------*/
    CloseWindow();
    return 0;
}