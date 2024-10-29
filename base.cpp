//Libraries
#include "raylib.h"

//DEV Notes
//
//Project made by Fernando C.
//Base platformer example using Raylib

//--------------------------------------------------------------------------------------
//Project attributes

//Map variables
#define tilemapSizeX 25
#define tilemapSizeY 15
int tileSize = 64;

//--------------------------------------------------------------------------------------
//User methods

//Locking for tile position on current tilemap
Vector2 checkTilePosition(Vector2 checkPosition, int tileSize) {
    //Calculating position
    Vector2 tilePosition = {(float)((int)(checkPosition.x / tileSize)), (float)((int)(checkPosition.y / tileSize))};
    //Returning position
    return tilePosition;
}

//Checking if the tilemap position is a collision tile
int checkTileType(Vector2 tilePosition, int collisiontilemap[][tilemapSizeX]) {
    //Calculating tile position
    int posX = tilePosition.x;
    int posY = tilePosition.y;
    //Returning the type of the collision tilemap tile
    return collisiontilemap[posY][posX];
}

//Looking for collisions under the character
bool checkCollisionDown(Vector2 characterPosition, Vector2 characterSize, int collisiontilemap[][tilemapSizeX], int tileSize) {
    //PointA
    Vector2 pointA = {characterPosition.x, characterPosition.y + characterSize.y + 1};
    //PointB
    Vector2 pointB = {characterPosition.x + characterSize.x - 1, characterPosition.y + characterSize.y + 1};
    //Precalculating
    Vector2 tilePointA = checkTilePosition(pointA, tileSize);
    Vector2 tilePointB = checkTilePosition(pointB, tileSize);
    //Checking types on points
    if (checkTileType(tilePointA, collisiontilemap) > 0 ||
    checkTileType(tilePointB, collisiontilemap) > 0) return true;
    else return false;
}

//Detecting character collinding on its left
bool checkCollisionLeft(Vector2 characterPosition, Vector2 characterSize, int collisiontilemap[][tilemapSizeX], int tileSize) {
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
    if (checkTileType(tilePointC, collisiontilemap) == 1 ||
    checkTileType(tilePointD, collisiontilemap) == 1 ||
    checkTileType(tilePointE, collisiontilemap) == 1 ||
    pointD.x < tileSize) return true;
    else return false;
}

//Function for detecting when colliding with a tile with collision in the right side of the player
bool checkCollisionRight(Vector2 characterPosition, Vector2 characterSize, int collisiontilemap[][tilemapSizeX], int tileSize) {
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
    if (checkTileType(tilePointF, collisiontilemap) == 1 ||
    checkTileType(tilePointG, collisiontilemap) == 1 ||
    checkTileType(tilePointH, collisiontilemap) == 1 ||
    pointG.x > GetScreenWidth() - tileSize) return true;
    else return false;
}

//--------------------------------------------------------------------------------------
//Main function
int main(void) {
    //Initialization
    const int screenWidth = (tilemapSizeX * tileSize) - tileSize, screenHeight = (tilemapSizeY * tileSize) - tileSize;
    InitWindow(screenWidth, screenHeight, "Base platformer - Prototype - Fernando C. - v0.0.37-alpha");
    SetTargetFPS(60);
    
    //--------------------------------------------------------------------------------------
    //Game properties

    //Camera variables
    Camera2D mainCamera;
    Vector2 cameraAcceleration = {0,0};
    mainCamera.offset = (Vector2){(float)screenWidth * 0.5f, (float)screenHeight * 0.5f};
    mainCamera.rotation = 0;
    mainCamera.zoom = 1.5f;

    //Tilemap variables
    Texture2D tilesheet = LoadTexture("./assets/Tilemaps/spritesheet_tilemap_red.png");
    Texture2D characters = LoadTexture("./assets/Entities/spritesheet_characters.png");
    Texture2D enemies = LoadTexture("./assets/Entities/spritesheet_enemies.png");
    Rectangle tiles[] = {
        {0, 0, 0, 0},                                                                   // 00 Empty
        {0 * (float)tileSize, 3 * (float)tileSize, (float)tileSize, (float)tileSize},   // 01 Fill main
        {0 * (float)tileSize, 2 * (float)tileSize, (float)tileSize, (float)tileSize},   // 02 Fill random
        {1 * (float)tileSize, 3 * (float)tileSize, (float)tileSize, (float)tileSize},   // 03 Floor main
        {1 * (float)tileSize, 0 * (float)tileSize, (float)tileSize, (float)tileSize},   // 04 Floor center
        {2 * (float)tileSize, 1 * (float)tileSize, (float)tileSize, (float)tileSize},   // 05 Floor left
        {2 * (float)tileSize, 0 * (float)tileSize, (float)tileSize, (float)tileSize},   // 06 Floor right
        {5 * (float)tileSize, 3 * (float)tileSize, (float)tileSize, (float)tileSize},   // 07 Platf main
        {5 * (float)tileSize, 0 * (float)tileSize, (float)tileSize, (float)tileSize},   // 08 Platf center
        {5 * (float)tileSize, 2 * (float)tileSize, (float)tileSize, (float)tileSize},   // 09 Platf left
        {5 * (float)tileSize, 1 * (float)tileSize, (float)tileSize, (float)tileSize},   // 10 Platf right
        {6 * (float)tileSize, 4 * (float)tileSize, (float)tileSize, (float)tileSize},   // 11 Edge left
        {6 * (float)tileSize, 3 * (float)tileSize, (float)tileSize, (float)tileSize},   // 12 Edge right
        {2 * (float)tileSize, 3 * (float)tileSize, (float)tileSize, (float)tileSize},   // 13 Edge left
        {2 * (float)tileSize, 2 * (float)tileSize, (float)tileSize, (float)tileSize},   // 14 Edge right
    };
    int bg2Tilemap[tilemapSizeY + 2][tilemapSizeX + 4] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        { 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
        { 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
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
        { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        { 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        { 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1},
        { 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1},
        { 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    int baseTilemap[tilemapSizeY][tilemapSizeX] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 9,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8,10, 0, 0},
        { 0, 0, 0, 0, 9, 8, 8,10, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8,10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {14, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,13},
        { 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1},
    };
    int collisionTilemap[tilemapSizeY][tilemapSizeX] = {
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 1},
        { 1, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    //Character variables
    Vector2 characterSize = {20, 52};
    Vector2 currentPosition = {850, 400};
    Vector2 currentVelocity = {0, 0};
    Vector2 currentAcceleration = {0, 0};
    Vector2 characterMid = {(characterSize.x * 0.5f), (characterSize.y * 0.5f)};
    int animationState = 0;
    int frameLimit = 1;
    int frameLoop = 0;
    int animRate = 20;
    bool forward = true;
    bool sliding = false;

    //Enemies variables
    Vector2 enemyPosition = {1250, 400};

    //Parallax variables
    Vector2 parallaxPositionOffset = {0, 32};

    //--------------------------------------------------------------------------------------
    //Game loop
    while (!WindowShouldClose()) {
        //Brain logic
        
        //Gravity
        currentAcceleration.y += 1;

        //Clamping forces
        if (currentVelocity.y > 32) currentVelocity.y = 32;
        else if (currentVelocity.y < -32) currentVelocity.y = -32;
        
        //Collisions under the character
        bool floorCollision = checkCollisionDown(currentPosition, characterSize, collisionTilemap, tileSize);
        Vector2 pointA = {currentPosition.x, currentPosition.y + characterSize.y + 1};
        Vector2 tilePointA = checkTilePosition(pointA, tileSize); 
        
        //Collisions on the left of the character
        bool leftCollision = checkCollisionLeft(currentPosition, characterSize, collisionTilemap, tileSize);
        Vector2 pointX1 = {currentPosition.x - 1, currentPosition.y + characterSize.y - 1};
        Vector2 tilePointX1 = checkTilePosition(pointX1, tileSize); 
        
        //Collisions on the right of the character
        bool rightCollision = checkCollisionRight(currentPosition, characterSize, collisionTilemap, tileSize);
        Vector2 pointX2 = {currentPosition.x + characterSize.x, currentPosition.y + characterSize.y - 1};
        Vector2 tilePointX2 = checkTilePosition(pointX2, tileSize); 
        
        //Falling down
        if (floorCollision && currentVelocity.y >= 0) {
            //Edge hopping
            if (checkTileType(tilePointA, collisionTilemap) == 1 ||
            (int)(currentPosition.y + characterSize.y) % tileSize < 24) {
                //Fixing position to tile position
                currentPosition.y = (tilePointA.y * tileSize) - characterSize.y;
                //Reseting forces
                currentVelocity.y = 0;
                currentAcceleration.y = 0;
                //Preventing falling from screen 
                if ((currentPosition.y + characterSize.y) > screenHeight) {
                    currentPosition.y = screenHeight - characterSize.y;
                }
            }
        }
        
        //Setting default animation
        if (currentVelocity.y == 0 && floorCollision) {
            //Restarting animation
            frameLimit = 1;
            animationState = 0;
        } else if (currentVelocity.y < 0 && !floorCollision) {
            //Restarting animation
            animationState = 2;
            frameLoop = 2;
            frameLimit = 2;
        }

        //Forcing movement only when not sliding
        if (!sliding) {
            //Jumping
            if (IsKeyDown(KEY_W) && currentVelocity.y == 0 &&
            ((floorCollision && (int)(currentPosition.y + characterSize.y) % tileSize < 4) ||
            currentPosition.y + characterSize.y >= screenHeight)) {
                //Adding jump force
                currentAcceleration.y -= 20;
                animationState = 2;
                frameLimit = 2;
                frameLoop = 0;
                animRate = 0;
            }
            
            //Lateral movement
            if (IsKeyDown(KEY_A) ||
            IsKeyDown(KEY_D)) {
                //Changing direction
                if (IsKeyDown(KEY_A)) forward = false;
                if (IsKeyDown(KEY_D)) forward = true;

                //Moving only if there's no collision
                if ((!leftCollision && IsKeyDown(KEY_A)) ||
                (!rightCollision && IsKeyDown(KEY_D))) {
                    //Moving with forces
                    currentAcceleration.x += forward ? 1.5f : -1.5f;
                    //Setting animation
                    animationState = currentVelocity.y == 0 && floorCollision ? 1 : 2;
                    frameLimit = 3;
                }
            }
        }

        //Limiting movement within screen && applying lateral collisions
        if (currentPosition.y < 0) {
            //Limiting going over screen
            currentPosition.y = 0;
            currentVelocity.y = 0;
        } //HERE SHOULD ADD GAME OVER
        if (leftCollision && currentVelocity.x < 0) {
            //Fixing position due to fast collision
            currentPosition.x = (tilePointX1.x * tileSize) + tileSize ;
            //Resetting forces when colliding
            currentVelocity.x = sliding ? -currentVelocity.x : 0;
            currentAcceleration.x = sliding ? currentAcceleration.x * 0.8f : 0;
            if (sliding) forward = !forward;
                
        } else if (currentVelocity.x > 0 && rightCollision) {
            //Fixing position due to fast collision
            currentPosition.x = (tilePointX2.x * tileSize) - characterSize.x;
            //Resetting forces when colliding
            currentVelocity.x = sliding ? -currentVelocity.x : 0;
            currentAcceleration.x = sliding ? currentAcceleration.x * 0.8f : 0;
            if (sliding) forward = !forward;
        }
    
        //Slide
        if (IsKeyDown(KEY_S) && floorCollision) {
            //Detecting when key is just pressed
            if (IsKeyPressed(KEY_S)) {
                //Moving the player once
                currentPosition.y = currentPosition.y + 10;
            }
            //Decreasing character size
            characterSize.y = 42;
            //Applying state
            sliding = true;
            animationState = 5;
            frameLimit = 1;
            frameLoop = 1;
        } else if (floorCollision) {
            //Detecting when key is just released
            if (IsKeyReleased(KEY_S)) {
                //Moving the player once
                currentPosition.y = currentPosition.y - 10;
            }
            //Applying state
            sliding = false;
            //Increasing character size
            characterSize.y = 52;
        }
        //Updating character center
        characterMid.y = characterSize.y / 2;
        
        //Calculating physics
        currentVelocity.y += currentAcceleration.y;
        currentVelocity.x *= sliding? 0.95f : 0.8f;
        currentPosition.y += currentVelocity.y;
        currentVelocity.x += currentAcceleration.x;
        currentPosition.x += currentVelocity.x;
    
        //Resetting gravity
        currentAcceleration.x = 0;
        currentAcceleration.y = 0;
        
        //Calculating camera positions
        Vector2 cameraLowerFocus = {
            (mainCamera.offset.x / mainCamera.zoom) - characterMid.x,
            (mainCamera.offset.y / mainCamera.zoom) - characterMid.y
            };
        Vector2 cameraUpperFocus = {
            (screenWidth - cameraLowerFocus.x) + characterMid.x,
            (screenHeight - cameraLowerFocus.y) + characterMid.y
        };

        //Updating camera position in X axys
        if (currentPosition.x + characterMid.x > cameraLowerFocus.x + tileSize &&
        currentPosition.x + characterMid.x < cameraUpperFocus.x - tileSize &&
        !rightCollision && !leftCollision) {
            //Moving middle
            mainCamera.target.x = currentPosition.x + characterMid.x;
            //Updating parallax X axys
            parallaxPositionOffset.x = mainCamera.target.x / 16;
        } else if (currentPosition.x + characterMid.x <= cameraLowerFocus.x + tileSize &&
        !rightCollision && !leftCollision) {
            //Moving left edge
            mainCamera.target.x = cameraLowerFocus.x + tileSize;
        } else if (currentPosition.x + characterMid.x >= cameraUpperFocus.x - tileSize &&
        !rightCollision && !leftCollision) {
            //Moving left edge
            mainCamera.target.x = cameraUpperFocus.x - tileSize;
        }

        //Updating camera position in Y axys
        if (currentPosition.y + characterMid.y > cameraLowerFocus.y &&
        currentPosition.y + characterMid.y < cameraUpperFocus.y) {
            //Moving center
            mainCamera.target.y = currentPosition.y + characterMid.y + (sliding ? -5 : 0);
            //Updating parallax Y axys
            parallaxPositionOffset.y = mainCamera.target.y / 16;
        } else if (currentPosition.y + characterMid.y <= cameraLowerFocus.y) {
            //Moving top edge
            mainCamera.target.y = cameraLowerFocus.y;
        } else if (currentPosition.y + characterMid.y >= cameraUpperFocus.y) {
            //Moving lower edge
            mainCamera.target.y = cameraUpperFocus.y;
        }

        //Updating camera acceleration
        cameraAcceleration.x = currentVelocity.x * currentVelocity.x / 8;
        if (currentVelocity.x < 0) cameraAcceleration.x *= -1; 
        cameraAcceleration.y = currentVelocity.y * currentVelocity.y / 64;
        if (currentVelocity.y < 0) cameraAcceleration.y *= -1;

        //Reducing camera acceleration
        cameraAcceleration.x *= 0.85f;
        cameraAcceleration.y *= 0.85f;

        //Setting camera target with accelerations
        mainCamera.target.x += cameraAcceleration.x * 2;
        mainCamera.target.y += cameraAcceleration.y * 2;

        //Creating character
        animRate++;
        if (animRate > (60 / (frameLimit * frameLimit)) && !sliding) { //Temp (if added animation struct/class can define its animation speed)
            //Updating frames
            frameLoop++;
            if (animationState == 2) frameLoop = 2;
            animRate = 0;
        }
        if (frameLoop > frameLimit) frameLoop = 0;
        Vector2 characterHitbox = {currentPosition.x - 22, currentPosition.y - (12 + ((sliding)? + 10 : 0))};
        Rectangle characterSprite = {(float)(animationState * tileSize), (float)(frameLoop * (tileSize)), (float)(tileSize * (forward? 1 : -1)), (float)tileSize};
        
        //Creating enemy
        Vector2 enemyHitbox = {enemyPosition.x, enemyPosition.y};
        Rectangle enemySprite = {(float)0, (float)0, (float)tileSize, (float)tileSize};

        //--------------------------------------------------------------------------------------
        //Graphic logic
        BeginDrawing();
            //Clearing the image with background color
            ClearBackground(PURPLE);
            //Drawing bg1 tilemap
            for (int x = 0; x < tilemapSizeX + 4; x++) {
                for (int y = 0; y < tilemapSizeY + 1; y++) {
                    Vector2 tilePosition = {((float)x * tileSize) - (parallaxPositionOffset.x * 2) + (tileSize * 1), ((float)y * tileSize) - (parallaxPositionOffset.y * 2)};
                    int tileIndex = bg2Tilemap[y][x];
                    //Drawing single tile
                    DrawTextureRec(tilesheet, tiles[tileIndex], tilePosition, BLACK);
                }
            }
            //Drawing bg2 tilemap
            for (int x = 0; x < tilemapSizeX + 8; x++) {
                for (int y = 0; y < tilemapSizeY + 2; y++) {
                    Vector2 tilePosition = {((float)x * tileSize) - (parallaxPositionOffset.x * 8) + (tileSize * 4), ((float)y * tileSize) - (parallaxPositionOffset.y * 8)};
                    int tileIndex = bg1Tilemap[y][x];
                    //Drawing single tile
                    DrawTextureRec(tilesheet, tiles[tileIndex], tilePosition, GRAY);
                }
            }
            BeginMode2D(mainCamera);
                //#Displaying the full tilesheet 
                //#DrawTexture(tilesheet, 0, 0, WHITE);
                //Drawing base tilemap
                for (int x = 0; x < tilemapSizeX; x++) {
                    for (int y = 0; y < tilemapSizeY; y++) {
                        Vector2 tilePosition = {((float)x * tileSize), ((float)y * tileSize)};
                        int tileIndex = baseTilemap[y][x];
                        //Drawing single tile
                        DrawTextureRec(tilesheet, tiles[tileIndex], tilePosition, WHITE);
                    }
                }
                //Drawing character
                DrawTextureRec(characters, characterSprite, characterHitbox, GOLD);
                //Drawing enemy
                DrawTextureRec(enemies, enemySprite, enemyHitbox, RED);
            EndMode2D();
        EndDrawing();
    }
    //--------------------------------------------------------------------------------------
    //End
    CloseWindow();
    return 0;
}