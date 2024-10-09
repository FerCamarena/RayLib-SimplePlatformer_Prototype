//Libraries
#include "raylib.h"

//--------------------------------------------------------------------------------------
//User attributes

//Map variables
#define tilemapSizeX 25
#define tilemapSizeY 14
int tileSize = 64;
//#const int tilemapSizeX = screenWidth / tileSize;
//#const int tilemapSizeY = screenHeight / tileSize;

//--------------------------------------------------------------------------------------
//User methods

//--------------------------------------------------------------------------------------
//Main function
int main(void) {
    //Initialization
    const int screenWidth = tilemapSizeX * tileSize, screenHeight = tilemapSizeY * tileSize;
    InitWindow(screenWidth, screenHeight, "Base platformer - Prototype");
    SetTargetFPS(60);
    
    //--------------------------------------------------------------------------------------
    //User properties
    
    //Tilemap variables
    Texture2D tilesheet = LoadTexture("./assets/tilesheet_complete.png");
    Rectangle tiles[] = {
        {0, 0, 0, 0},                                      // 0 Empty
        {0 * tileSize, 0 * tileSize, tileSize, tileSize},  // 1 Full
        {1 * tileSize, 0 * tileSize, tileSize, tileSize},  // 2 Curved left
        {2 * tileSize, 0 * tileSize, tileSize, tileSize},  // 3 Curved center
        {3 * tileSize, 0 * tileSize, tileSize, tileSize},  // 4 Curved right
    };
    int tilemap[tilemapSizeY][tilemapSizeX] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,2,3,3,4,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,4,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,2,3,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };
    
    //Character variables
    Vector2 characterSize = {40, 52};
    Vector2 currentPosition = {386, 16};
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
            if(currentPosition.x  < screenWidth){
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
        if(currentPosition.y + characterSize.y > screenHeight){
            currentPosition.y = screenHeight - characterSize.y;
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
            characterSize.y = 42;
        } else {
            //Detecting when key is released
            if(IsKeyReleased(KEY_S)){
                //Moving the player once
                currentPosition.y = currentPosition.y - 24;
            }
            //Resetting character size
            characterSize.y = 52;
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
                //#Displaying the full tilesheet 
                //#DrawTexture(tilesheet, 0, 0, WHITE);
                //Drawing tilemap
                for(int x = 0; x < tilemapSizeX; x++){
                    for(int y = 0; y < tilemapSizeY; y++){
                        Vector2 tilePosition = {x * tileSize, y * tileSize};
                        int tileIndex = tilemap[y][x];
                        //Drawing single tile
                        DrawTextureRec(tilesheet, tiles[tileIndex], tilePosition, WHITE);
                    }
                }
                //Drawing character
                DrawRectangle(currentPosition.x, currentPosition.y, characterSize.x, characterSize.y, GOLD);
            //EndMode2D();
        EndDrawing();
    }
    //--------------------------------------------------------------------------------------
    //End
    CloseWindow();
    return 0;
}