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

//Locking for tile position on current tilemap
Vector2 checkTilePosition(Vector2 checkPosition, int tileSize){
    //Calculating position
    Vector2 tilePosition = {(int)(checkPosition.x / tileSize), (int)(checkPosition.y / tileSize)};
    //Returning position
    return tilePosition;
}

//Checking if the tilemap position is a collision tile
int checkTileType(Vector2 tilePosition, int collisiontilemap[][tilemapSizeX]){
    //Calculating tile position
    int posX = tilePosition.x;
    int posY = tilePosition.y;
    //Returning the type of the collision tilemap tile
    return collisiontilemap[posY][posX];
}

//Looking for collisions under the character
bool checkCollisionDown(Vector2 characterPosition, Vector2 characterSize, int collisiontilemap[][tilemapSizeX], int tileSize){
    //PointA
    Vector2 pointA = {characterPosition.x, characterPosition.y + characterSize.y + 1};
    //PointB
    Vector2 pointB = {characterPosition.x + characterSize.x - 1, characterPosition.y + characterSize.y + 1};
    //Precalculating
    Vector2 tilePointA = checkTilePosition(pointA, tileSize);
    Vector2 tilePointB = checkTilePosition(pointB, tileSize);
    //Checking types on points
    if(checkTileType(tilePointA, collisiontilemap) > 0 ||
    checkTileType(tilePointB, collisiontilemap) > 0) return true;
    else return false;
}

//Detecting character collinding on its left
bool checkCollisionLeft(Vector2 characterPosition, Vector2 characterSize, int collisiontilemap[][tilemapSizeX], int tileSize){
    //PointC
    Vector2 pointC = {characterPosition.x - 1, characterPosition.y};
    //PointD
    Vector2 pointD = {characterPosition.x - 1, characterPosition.y + (characterSize.y * 0.5f)};
    //PointE
    Vector2 pointE = {characterPosition.x - 1, characterPosition.y + characterSize.y - 1};
    //Precalculating
    Vector2 tilePointC = checkTilePosition(pointC, tileSize);
    Vector2 tilePointD = checkTilePosition(pointD, tileSize);
    Vector2 tilePointE = checkTilePosition(pointE, tileSize);
    //Returning on each case
    if(checkTileType(tilePointC, collisiontilemap) == 1 ||
    checkTileType(tilePointD, collisiontilemap) == 1 ||
    checkTileType(tilePointE, collisiontilemap) == 1) return true;
    else return false;
}

//Function for detecting when colliding with a tile with collision in the right side of the player
bool checkCollisionRight(Vector2 characterPosition, Vector2 characterSize, int collisiontilemap[][tilemapSizeX], int tileSize){
    //PointC
    Vector2 pointF = {characterPosition.x + characterSize.x, characterPosition.y};
    //PointD
    Vector2 pointG = {characterPosition.x + characterSize.x, characterPosition.y + (characterSize.y * 0.5f)};
    //PointE
    Vector2 pointH = {characterPosition.x + characterSize.x, characterPosition.y + characterSize.y - 1};
    //Precalculating
    Vector2 tilePointF = checkTilePosition(pointF, tileSize);
    Vector2 tilePointG = checkTilePosition(pointG, tileSize);
    Vector2 tilePointH = checkTilePosition(pointH, tileSize);
    //Returning for each case
    if(checkTileType(tilePointF, collisiontilemap) == 1 ||
    checkTileType(tilePointG, collisiontilemap) == 1 ||
    checkTileType(tilePointH, collisiontilemap) == 1) return true;
    else return false;
}

//--------------------------------------------------------------------------------------
//Main function
int main(void) {
    //Initialization
    const int screenWidth = tilemapSizeX * tileSize, screenHeight = tilemapSizeY * tileSize;
    InitWindow(screenWidth, screenHeight, "Base platformer - Prototype");
    SetTargetFPS(60);
    
    //--------------------------------------------------------------------------------------
    //User properties

    //Camera variables
    Camera2D mainCamera;
    mainCamera.offset = (Vector2){(float)screenWidth * 0.5f, (float)screenHeight * 0.5f};
    mainCamera.rotation = 0;
    mainCamera.zoom = 1.5f;
    Vector2 cameraAcceleration = {0,0};

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
        {0,0,0,0,0,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,4,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,2,3,3,4,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,4,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };
    int collisiontilemap[tilemapSizeY][tilemapSizeX] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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

        //Clamping forces
        if(currentVelocity.y > 32) currentVelocity.y = 32;
        else if (currentVelocity.y < -32) currentVelocity.y = -32;
        
        //Collisions under the character
        bool floorCollision = checkCollisionDown(currentPosition, characterSize, collisiontilemap, tileSize);
        Vector2 pointA = {currentPosition.x, currentPosition.y + characterSize.y + 1};
        Vector2 tilePointA = checkTilePosition(pointA, tileSize); 
        
        //Falling down
        if(floorCollision && currentVelocity.y >= 0){
            //Edge hopping
            if(checkTileType(tilePointA, collisiontilemap) == 1 ||
            (int)(currentPosition.y + characterSize.y) % tileSize < 12) {
                //Fixing position to tile position
                currentPosition.y = (tilePointA.y * tileSize) - characterSize.y;
                //Reseting forces
                currentVelocity.y = 0;
                currentAcceleration.y = 0;
                //Preventing falling from screen 
                if((currentPosition.y + characterSize.y) > screenHeight){
                    currentPosition.y = screenHeight - characterSize.y;
                }
            }
        }
        
        //Jumping
        if(IsKeyDown(KEY_W) && currentVelocity.y == 0 &&
        ((floorCollision && (int)(currentPosition.y + characterSize.y) % tileSize < 4) ||
        currentPosition.y + characterSize.y >= screenHeight)){
            //Adding jump force
            currentAcceleration.y -= 16;
        }
        
        //Collisions on the left of the character
        bool leftCollision = checkCollisionLeft(currentPosition, characterSize, collisiontilemap, tileSize);
        Vector2 pointX1 = {currentPosition.x - 1, currentPosition.y + characterSize.y - 1};
        Vector2 tilePointX1 = checkTilePosition(pointX1, tileSize); 
        
        //Moving left
        if(IsKeyDown(KEY_A)){
            if(leftCollision){
                //Fixing position due to fast collision
                currentPosition.x = (tilePointX1.x * tileSize) + tileSize;
                //Resetting forces when colliding
                currentVelocity.x = 0;
                currentAcceleration.x = 0;
            } else if(currentPosition.x > 0){
                //Moving
                currentAcceleration.x -= 1.5f;
            }
        }
        
        //Collisions on the right of the haracter
        bool rightCollision = checkCollisionRight(currentPosition, characterSize, collisiontilemap, tileSize);
        Vector2 pointX2 = {currentPosition.x - 1, currentPosition.y + characterSize.y - 1};
        Vector2 tilePointX2 = checkTilePosition(pointX2, tileSize); 
        
        //Moving right
        if(IsKeyDown(KEY_D)){
            if(rightCollision){
                //Fixing position due to fast collision
                currentPosition.x = (tilePointX2.x * tileSize) + tileSize - characterSize.x;
                //Resetting forces when colliding
                currentVelocity.x = 0;
                currentAcceleration.x = 0;
            } else if(currentPosition.x + characterSize.x < tileSize * tilemapSizeX){
                //Moving
                currentAcceleration.x += 1.5f;
            }
        }
        
        //Limiting up movement with screen
        if(currentPosition.y < 0){
            //Limiting going over screen
            currentPosition.y = 0;
            currentVelocity.y = 0;
        }
        if(currentPosition.x < 0) currentPosition.x = 0;
        if(currentPosition.x + characterSize.x > tileSize * tilemapSizeX) currentPosition.x = tileSize * tilemapSizeX - characterSize.x;
        
        //Crouch
        if(IsKeyDown(KEY_S)){
            //Detecting when key is just pressed
            if(IsKeyPressed(KEY_S)){
                //Moving the player once
                currentPosition.y = currentPosition.y + 10;
            }
            //Decreasing character size
            characterSize.y = 42;
        } else {
            //Detecting when key is just released
            if(IsKeyReleased(KEY_S)){
                //Moving the player once
                currentPosition.y = currentPosition.y - 10;
            }
            //Resetting character size
            characterSize.y = 52;
        }
        
        //Calculating physics
        currentVelocity.y += currentAcceleration.y;
        currentVelocity.x *= 0.85f;
        currentPosition.y += currentVelocity.y;
        currentVelocity.x += currentAcceleration.x;
        currentPosition.x += currentVelocity.x;
    
        //Resetting gravity
        currentAcceleration.x = 0;
        currentAcceleration.y = 0;
           
        //Calculating camera positions
        Vector2 cameraLimits = {((800 + (tileSize / 2)) / mainCamera.zoom), ((400 + tileSize * 2) / mainCamera.zoom)};
        Vector2 cameraLeftFocus = {(cameraLimits.x - (characterSize.x * 0.5f)), (cameraLimits.y - (26 * 0.5f))};
        Vector2 cameraRightFocus = {((screenWidth - cameraLimits.x) - (characterSize.x * 0.5f)), ((screenHeight - cameraLimits.y) - (26 * 0.5f))};

        //Updating camera position in x axys
        if(currentPosition.x > cameraLeftFocus.x &&
        currentPosition.x < cameraRightFocus.x){
            mainCamera.target.x = currentPosition.x + (characterSize.x * 0.5f);
        } else if (currentPosition.x < cameraRightFocus.x){
            mainCamera.target.x = cameraLimits.x;
        } else if (currentPosition.x > cameraLeftFocus.x){
            mainCamera.target.x = screenWidth - cameraLimits.x;
        }

        //Updating camera position in Y axys
        if(currentPosition.y >= cameraLeftFocus.y &&
        currentPosition.y <= cameraRightFocus.y){
            mainCamera.target.y = currentPosition.y + (26 * 0.5f);
        } else if (currentPosition.y < cameraRightFocus.y){
            mainCamera.target.y = cameraLimits.y;
        } else if (currentPosition.y > cameraLeftFocus.y){
            mainCamera.target.y = screenHeight - cameraLimits.y;
        }

        //Updating camera acceleration
        cameraAcceleration.x = currentVelocity.x * currentVelocity.x / 8;
        if(currentVelocity.x < 0) cameraAcceleration.x *= -1; 
        cameraAcceleration.y = currentVelocity.y * currentVelocity.y / 64;
        if(currentVelocity.y < 0) cameraAcceleration.y *= -1;

        //Reducing camera acceleration
        cameraAcceleration.x *= 0.85f;
        cameraAcceleration.y *= 0.85f;

        //Setting camera target with accelerations
        mainCamera.target.x += cameraAcceleration.x * 2;
        mainCamera.target.y += cameraAcceleration.y * 2;

        //--------------------------------------------------------------------------------------
        //Graphic logic
        BeginDrawing();
            BeginMode2D(mainCamera);
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
            EndMode2D();
        EndDrawing();
    }
    //--------------------------------------------------------------------------------------
    //End
    CloseWindow();
    return 0;
}