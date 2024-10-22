//Libraries
#include "raylib.h"

//--------------------------------------------------------------------------------------
//User attributes

//Map variables
#define tilemapSizeX 25
#define tilemapSizeY 14
int tileSize = 64;

//--------------------------------------------------------------------------------------
//User methods

//Locking for tile position on current tilemap
Vector2 checkTilePosition(Vector2 checkPosition, int tileSize){
    //Calculating position
    Vector2 tilePosition = {(float)((int)(checkPosition.x / tileSize)), (float)((int)(checkPosition.y / tileSize))};
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
    Vector2 cameraAcceleration = {0,0};
    mainCamera.offset = (Vector2){(float)screenWidth * 0.5f, (float)screenHeight * 0.5f};
    mainCamera.rotation = 0;
    mainCamera.zoom = 1.5f;

    //Tilemap variables
    Texture2D tilesheet = LoadTexture("./assets/Tilemaps/spritesheet_red_tilemap.png");
    Texture2D characters = LoadTexture("./assets/Entities/spritesheet_characters.png");
    Rectangle tiles[] = {
        {0, 0, 0, 0},                                      // 00 Empty
        {0 * (float)tileSize, 3 * (float)tileSize, (float)tileSize, (float)tileSize},  // 01 Fill main
        {0 * (float)tileSize, 2 * (float)tileSize, (float)tileSize, (float)tileSize},  // 02 Fill random
        {1 * (float)tileSize, 3 * (float)tileSize, (float)tileSize, (float)tileSize},  // 03 Floor main
        {1 * (float)tileSize, 0 * (float)tileSize, (float)tileSize, (float)tileSize},  // 04 Floor center
        {2 * (float)tileSize, 1 * (float)tileSize, (float)tileSize, (float)tileSize},  // 05 Floor left
        {2 * (float)tileSize, 0 * (float)tileSize, (float)tileSize, (float)tileSize},  // 06 Floor right
        {5 * (float)tileSize, 3 * (float)tileSize, (float)tileSize, (float)tileSize},  // 07 Platf main
        {5 * (float)tileSize, 0 * (float)tileSize, (float)tileSize, (float)tileSize},  // 08 Platf center
        {5 * (float)tileSize, 2 * (float)tileSize, (float)tileSize, (float)tileSize},  // 09 Platf left
        {5 * (float)tileSize, 1 * (float)tileSize, (float)tileSize, (float)tileSize},  // 10 Platf right
        {6 * (float)tileSize, 4 * (float)tileSize, (float)tileSize, (float)tileSize},  // 11 Edge left
        {6 * (float)tileSize, 3 * (float)tileSize, (float)tileSize, (float)tileSize},  // 12 Edge right
        {2 * (float)tileSize, 3 * (float)tileSize, (float)tileSize, (float)tileSize},  // 13 Edge left
        {2 * (float)tileSize, 2 * (float)tileSize, (float)tileSize, (float)tileSize},  // 14 Edge right
    };
    int bg2Tilemap[tilemapSizeY + 2][tilemapSizeX + 4] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        { 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
        { 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
        { 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
        { 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
    };
    int bg1Tilemap[tilemapSizeY + 1][tilemapSizeX + 8] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        { 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1},
        { 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    int baseTilemap[tilemapSizeY][tilemapSizeX] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 9,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8,10, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 9, 8, 8,10, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8,10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {14, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,13},
        { 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
    };
    int collisionTilemap[tilemapSizeY][tilemapSizeX] = {
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };

    //Character variables
    Vector2 characterSize = {20, 52};
    Vector2 currentPosition = {386, 16};
    Vector2 currentVelocity = {0, 0};
    Vector2 currentAcceleration = {0, 0};
    Vector2 characterMid = {(characterSize.x * 0.5f), (characterSize.y * 0.5f)};
    int animationState = 0;
    int frameLimit = 1;
    int frameLoop = 0;
    int animRate = 20;

    //Parallax variables
    Vector2 parallaxPositionOffset = {0, 32};

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
        bool floorCollision = checkCollisionDown(currentPosition, characterSize, collisionTilemap, tileSize);
        Vector2 pointA = {currentPosition.x, currentPosition.y + characterSize.y + 1};
        Vector2 tilePointA = checkTilePosition(pointA, tileSize); 
        
        //Falling down
        if(floorCollision && currentVelocity.y >= 0){
            //Edge hopping
            if(checkTileType(tilePointA, collisionTilemap) == 1 ||
            (int)(currentPosition.y + characterSize.y) % tileSize < 24) {
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
        
        //Setting default animation
        if (currentVelocity.y == 0 && floorCollision) {
            frameLimit = 1;
            animationState = 0;
        } else if (currentVelocity.y < 0 && !floorCollision) {
            animationState = 2;
            frameLoop = 2;
            frameLimit = 2;
        }

        //Jumping
        if(IsKeyDown(KEY_W) && currentVelocity.y == 0 &&
        ((floorCollision && (int)(currentPosition.y + characterSize.y) % tileSize < 4) ||
        currentPosition.y + characterSize.y >= screenHeight)){
            //Adding jump force
            currentAcceleration.y -= 20;
            animationState = 2;
            frameLimit = 2;
            frameLoop = 0;
            animRate = 0;
        }
        
        //Collisions on the left of the character
        bool leftCollision = checkCollisionLeft(currentPosition, characterSize, collisionTilemap, tileSize);
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
                animationState = floorCollision ? 1 : 2;
                frameLimit = 3;
            }
        }
        
        //Collisions on the right of the haracter
        bool rightCollision = checkCollisionRight(currentPosition, characterSize, collisionTilemap, tileSize);
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
                animationState = currentVelocity.y == 0 && floorCollision ? 1 : 2;
                frameLimit = 3;
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
            animationState = 5;
            frameLimit = 1;
            frameLoop = 1;
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
        Vector2 cameraLowerFocus = {(mainCamera.offset.x / mainCamera.zoom) + characterMid.x, (mainCamera.offset.y / mainCamera.zoom) + characterMid.y};
        Vector2 cameraUpperFocus = {(screenWidth - cameraLowerFocus.x) + characterMid.x, (screenHeight - cameraLowerFocus.y) + characterMid.y};

        //Offseting parallax with camera
        if (currentPosition.x >= cameraLowerFocus.x && (currentPosition.x + characterSize.x) <= cameraUpperFocus.x) {
            if(currentVelocity.x > 1) parallaxPositionOffset.x += 0.5f;
            else if(currentVelocity.x < -1) parallaxPositionOffset.x -= 0.5f;
        }
        if (currentPosition.y >= cameraLowerFocus.y && (currentPosition.y + characterSize.y) <= cameraUpperFocus.y) {
            if(currentVelocity.y > 1) parallaxPositionOffset.y += 0.5f;
            else if(currentVelocity.y < -1) parallaxPositionOffset.y -= 0.5f;
        }

        //Updating camera position in X axys
        if(currentPosition.x + characterMid.x  + 1 > cameraLowerFocus.x &&
        currentPosition.x + characterMid.x - 1 < cameraUpperFocus.x){
            mainCamera.target.x = currentPosition.x + characterMid.x;
        } else if (currentPosition.x + characterMid.x <= cameraLowerFocus.x){
            mainCamera.target.x = cameraLowerFocus.x;
        } else if (currentPosition.x + characterMid.x >= cameraUpperFocus.x){
            mainCamera.target.x = cameraUpperFocus.x;
        }

        //Updating camera position in Y axys
        if(currentPosition.y + characterMid.y + 1 > cameraLowerFocus.y &&
        currentPosition.y + characterMid.y - 1 < cameraUpperFocus.y){
            mainCamera.target.y = currentPosition.y + 26 + (IsKeyDown(KEY_S)? - 10 : 0);
        } else if (currentPosition.y + characterMid.y <= cameraLowerFocus.y){
            mainCamera.target.y = cameraLowerFocus.y;
        } else if (currentPosition.y + characterMid.y >= cameraUpperFocus.y){
            mainCamera.target.y = cameraUpperFocus.y;
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

        //Character sprite rectangle
        Vector2 sprite = {currentPosition.x - 22, currentPosition.y - (12 + (IsKeyDown(KEY_S)? + 10 : 0))};

        //Processing character animations
        animRate++;
        if (animRate > (60 / (frameLimit * frameLimit)) && !IsKeyDown(KEY_S)) { //Temp
            frameLoop++;
            if (animationState == 2) frameLoop = 2;
            animRate = 0;
        }
        if (frameLoop > frameLimit) frameLoop = 0;

        //--------------------------------------------------------------------------------------
        //Graphic logic
        BeginDrawing();
            //Clearing the image with background color
            ClearBackground(PURPLE);
            //Drawing bg2 tilemap
            for(int x = 0; x < tilemapSizeX + 4; x++){
                for(int y = 0; y < tilemapSizeY + 2; y++){
                    Vector2 tilePosition = {((float)x * tileSize) - (parallaxPositionOffset.x * 0.5f), ((float)y * tileSize) - (parallaxPositionOffset.y * 0.5f)};
                    int tileIndex = bg2Tilemap[y][x];
                    //Drawing single tile
                    DrawTextureRec(tilesheet, tiles[tileIndex], tilePosition, WHITE);
                }
            }
            //Drawing bg1 tilemap
            for(int x = 0; x < tilemapSizeX + 8; x++){
                for(int y = 0; y < tilemapSizeY + 1; y++){
                    Vector2 tilePosition = {((float)x * tileSize) - (parallaxPositionOffset.x * 2), ((float)y * tileSize) - (parallaxPositionOffset.y * 4)};
                    int tileIndex = bg1Tilemap[y][x];
                    //Drawing single tile
                    DrawTextureRec(tilesheet, tiles[tileIndex], tilePosition, WHITE);
                }
            }
            BeginMode2D(mainCamera);
                //#Displaying the full tilesheet 
                //#DrawTexture(tilesheet, 0, 0, WHITE);
                //Drawing base tilemap
                for(int x = 0; x < tilemapSizeX; x++){
                    for(int y = 0; y < tilemapSizeY; y++){
                        Vector2 tilePosition = {((float)x * tileSize), ((float)y * tileSize)};
                        int tileIndex = baseTilemap[y][x];
                        //Drawing single tile
                        DrawTextureRec(tilesheet, tiles[tileIndex], tilePosition, WHITE);
                    }
                }
                //Drawing character
                DrawTextureRec(characters, {(float)(animationState * tileSize), (float)(frameLoop * tileSize), (float)tileSize, (float)tileSize}, sprite, GOLD);
            EndMode2D();
        EndDrawing();
    }
    //--------------------------------------------------------------------------------------
    //End
    CloseWindow();
    return 0;
}