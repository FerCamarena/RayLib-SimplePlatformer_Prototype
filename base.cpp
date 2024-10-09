//Libraries
#include "raylib.h"

//--------------------------------------------------------------------------------------
//User attributes

//--------------------------------------------------------------------------------------
//User methods

//--------------------------------------------------------------------------------------
//Main function
int main(void) {
    //Initialization
    InitWindow(800, 450, "Base platformer - Prototype");
    SetTargetFPS(60);
    
    //--------------------------------------------------------------------------------------
    //User properties
    
    //Character variables
    Vector2 characterSize = {24, 48};
    Vector2 currentPosition = {400, 0};
    Vector2 currentVelocity = {0, 0};
    Vector2 currentAcceleration = {0, 0};

    //--------------------------------------------------------------------------------------
    //Game loop
    while (!WindowShouldClose()) {
        //Brain logic
        //Gravity
        currentAcceleration.y += 1;
            
        //Walking left
        if(IsKeyDown(KEY_A)){
            if(currentPosition.x > 0){
                currentAcceleration.x -= 5;
            }
        } else if(IsKeyDown(KEY_A)){
            //currentPosition.x = ((int)tilePointX1.x * tileSize) + tileSize;
            currentVelocity.x = 0;
            currentAcceleration.x = 0;
        }
        
        //Walking right
        if(IsKeyDown(KEY_D)){
            if(currentPosition.x + characterSize.x < 800){
                currentAcceleration.x += 5;
            }
        } else if(IsKeyDown(KEY_D)){
            //currentPosition.x = ((int)tilePointX2.x * tileSize) + tileSize - characterSize.x;
            currentVelocity.x = 0;
            currentAcceleration.x = 0;
        }
        
        //Limiting movement with screen
        if(currentPosition.y < 0){
            currentPosition.y = 0;
            currentVelocity.y = 0;
        }
        if(currentPosition.y > 450 - characterSize.y){
            currentPosition.y = 450 - characterSize.y;
            currentVelocity.y = 0;
        }
        
        //Jumping
        if(IsKeyDown(KEY_W) && currentVelocity.y >= 0){
            currentAcceleration.y -= 16;
        }
        
        //Crouch
        if(IsKeyDown(KEY_S)){
            //Detecting when key is pressed
            if(IsKeyPressed(KEY_S)){
                //Moving the player once
                currentPosition.y = currentPosition.y + 24;
            }
            //Decreasing character size
            characterSize.y = 72;
        } else {
            //Detecting when key is released
            if(IsKeyReleased(KEY_S)){
                //Moving the player once
                currentPosition.y = currentPosition.y - 24;
            }
            //Resetting character size
            characterSize.y = 96;
        }
        
        //Calculating physics
        currentVelocity.y += currentAcceleration.y;
        currentPosition.y += currentVelocity.y;
        currentVelocity.x += currentAcceleration.x;
        currentPosition.x += currentVelocity.x;
    
        //Resetting gravity
        currentAcceleration.x = 0;
        currentVelocity.x = 0;
        currentAcceleration.y = 0;
           
        //--------------------------------------------------------------------------------------
        //Graphic logic
        BeginDrawing();
            //BeginMode2D(mainCamera);
                //Clearing the image with background color
                ClearBackground(PURPLE);
                //Drawing character
                DrawRectangle(currentPosition.x, currentPosition.y, characterSize.x, characterSize.y, GOLD);
            //EndMode2D();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------------
    //End
    CloseWindow();
    return 0;
}