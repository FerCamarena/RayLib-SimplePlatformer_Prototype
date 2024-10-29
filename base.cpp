//Libraries
#include "raylib.h"

//DEV Notes
//
//Project made by Fernando C.
//Base platformer example using Raylib

//--------------------------------------------------------------------------------------
//Project attributes

//Map variables 8:4.5 - 16:9 - 24:13.5
#define tilemapSizeX 25
#define tilemapSizeY 15
int tileSize = 64;

//--------------------------------------------------------------------------------------
//User methods

//Locking for tile position on current tilemap
Vector2 CheckTilePosition(Vector2 checkPosition, int tileSize) {
    //Calculating position
    Vector2 tilePosition = {(float)((int)(checkPosition.x / tileSize)), (float)((int)(checkPosition.y / tileSize))};
    //Returning position
    return tilePosition;
}

//Checking if the tilemap position is a collision tile
int CheckTileType(Vector2 tilePosition, int collisiontilemap[][tilemapSizeX]) {
    //Calculating tile position
    int posX = tilePosition.x;
    int posY = tilePosition.y;
    //Returning the type of the collision tilemap tile
    return collisiontilemap[posY][posX];
}

//Looking for collisions under the character
bool CheckCollisionDown(Vector2 entityPosition, Vector2 entitySize, int collisiontilemap[][tilemapSizeX], int tileSize) {
    //PointA
    Vector2 pointA = {entityPosition.x, entityPosition.y + entitySize.y + 1};
    //PointB
    Vector2 pointB = {entityPosition.x + entitySize.x - 1, entityPosition.y + entitySize.y + 1};
    //Precalculating
    Vector2 tilePointA = CheckTilePosition(pointA, tileSize);
    Vector2 tilePointB = CheckTilePosition(pointB, tileSize);
    //Checking types on points
    if (CheckTileType(tilePointA, collisiontilemap) > 0 ||
    CheckTileType(tilePointB, collisiontilemap) > 0) return true;
    else return false;
}

//Detecting character collinding on its left
bool CheckCollisionLeft(Vector2 entityPosition, Vector2 entitySize, int collisiontilemap[][tilemapSizeX], int tileSize) {
    //PointC
    Vector2 pointC = {entityPosition.x - 1, entityPosition.y};
    //PointD
    Vector2 pointD = {entityPosition.x - 1, entityPosition.y + (entitySize.y * 0.5f)};
    //PointE
    Vector2 pointE = {entityPosition.x - 1, entityPosition.y + entitySize.y - 1};
    //Precalculating
    Vector2 tilePointC = CheckTilePosition(pointC, tileSize);
    Vector2 tilePointD = CheckTilePosition(pointD, tileSize);
    Vector2 tilePointE = CheckTilePosition(pointE, tileSize);
    //Returning on each case
    if (CheckTileType(tilePointC, collisiontilemap) == 1 ||
    CheckTileType(tilePointD, collisiontilemap) == 1 ||
    CheckTileType(tilePointE, collisiontilemap) == 1 ||
    pointD.x < tileSize) return true;
    else return false;
}

//Function for detecting when colliding with a tile with collision in the right side of the player
bool CheckCollisionRight(Vector2 entityPosition, Vector2 entitySize, int collisiontilemap[][tilemapSizeX], int tileSize) {
    //PointC
    Vector2 pointF = {entityPosition.x + entitySize.x, entityPosition.y};
    //PointD
    Vector2 pointG = {entityPosition.x + entitySize.x, entityPosition.y + (entitySize.y * 0.5f)};
    //PointE
    Vector2 pointH = {entityPosition.x + entitySize.x, entityPosition.y + entitySize.y - 1};
    //Precalculating
    Vector2 tilePointF = CheckTilePosition(pointF, tileSize);
    Vector2 tilePointG = CheckTilePosition(pointG, tileSize);
    Vector2 tilePointH = CheckTilePosition(pointH, tileSize);
    //Returning for each case
    if (CheckTileType(tilePointF, collisiontilemap) == 1 ||
    CheckTileType(tilePointG, collisiontilemap) == 1 ||
    CheckTileType(tilePointH, collisiontilemap) == 1 ||
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
    Vector2 characterPosition = {850, 400};
    Vector2 characterVelocity = {0, 0};
    Vector2 characterAcceleration = {0, 0};
    Vector2 characterSize = {20, 52};
    Vector2 characterHalf = {(characterSize.x * 0.5f), (characterSize.y * 0.5f)};
    int characterAnimState = 0;
    int characterFrameLimit = 1;
    int characterFrameCycle = 0;
    int characterAnimRate = 20;
    bool characterFwd = true;
    bool characterSlide = false;

    //Enemies variables
    Vector2 enemyPosition = {1250, 400};
    Vector2 enemyVelocity = {0, 0};
    Vector2 enemyAcceleration = {0, 0};
    Vector2 enemySize = {20, 52};
    bool enemyFwd = true;

    //Parallax variables
    Vector2 parallaxPositionOffset = {0, 32};

    //--------------------------------------------------------------------------------------
    //Game loop
    while (!WindowShouldClose()) {
        //Brain logic
        
        //=====CHARACTER=====
        
        //Gravity
        characterAcceleration.y += 1;
        
        //Collisions under the character
        bool characterFloorCollision = CheckCollisionDown(characterPosition, characterSize, collisionTilemap, tileSize);
        Vector2 characterPointUnder = {characterPosition.x, characterPosition.y + characterSize.y + 1};
        Vector2 characterTileUnder = CheckTilePosition(characterPointUnder, tileSize); 
        
        //Collisions on the left of the character
        bool characterLeftCollision = CheckCollisionLeft(characterPosition, characterSize, collisionTilemap, tileSize);
        Vector2 characterPointLeft = {characterPosition.x - 1, characterPosition.y + characterSize.y - 1};
        Vector2 characterTileLeft = CheckTilePosition(characterPointLeft, tileSize); 
        
        //Collisions on the right of the character
        bool characterRightCollision = CheckCollisionRight(characterPosition, characterSize, collisionTilemap, tileSize);
        Vector2 characterPointRight = {characterPosition.x + characterSize.x, characterPosition.y + characterSize.y - 1};
        Vector2 characterTileRight = CheckTilePosition(characterPointRight, tileSize); 
        
        //Falling
        if (characterFloorCollision && characterVelocity.y >= 0) {
            //Edge hopping condition
            if (CheckTileType(characterTileUnder, collisionTilemap) == 1 ||
            (int)(characterPosition.y + characterSize.y) % tileSize < 24) {
                //Fixing position to tile position
                characterPosition.y = (characterTileUnder.y * tileSize) - characterSize.y;
                //Reseting forces
                characterVelocity.y = 0;
                characterAcceleration.y = 0;
                //Preventing falling from screen TEMP
                if ((characterPosition.y + characterSize.y) > screenHeight) {
                    characterPosition.y = screenHeight - characterSize.y;
                }
            }
        }
        
        //Setting default animation
        if (characterVelocity.y == 0 && characterFloorCollision) {
            //Restarting animation
            characterFrameLimit = 1;
            characterAnimState = 0;
        } else if (characterVelocity.y < 0 && !characterFloorCollision) {
            //Restarting animation
            characterAnimState = 2;
            characterFrameCycle = 2;
            characterFrameLimit = 2;
        }

        //Forcing movement only when not characterSlide
        if (!characterSlide) {
            //Jumping
            if (IsKeyDown(KEY_W) && characterVelocity.y == 0 &&
            ((characterFloorCollision && (int)(characterPosition.y + characterSize.y) % tileSize < 4) ||
            characterPosition.y + characterSize.y >= screenHeight)) {
                //Adding jump force
                characterAcceleration.y -= 20;
                characterAnimState = 2;
                characterFrameLimit = 2;
                characterFrameCycle = 0;
                characterAnimRate = 0;
            }
            
            //Lateral movement
            if (IsKeyDown(KEY_A) ||
            IsKeyDown(KEY_D)) {
                //Changing direction
                if (IsKeyDown(KEY_A)) characterFwd = false;
                if (IsKeyDown(KEY_D)) characterFwd = true;

                //Moving only if there's no collision
                if ((!characterLeftCollision && IsKeyDown(KEY_A)) ||
                (!characterRightCollision && IsKeyDown(KEY_D))) {
                    //Moving with forces
                    characterAcceleration.x += characterFwd ? 1.5f : -1.5f;
                    //Setting animation
                    characterAnimState = characterVelocity.y == 0 && characterFloorCollision ? 1 : 2;
                    characterFrameLimit = 3;
                }
            }
        }

        //Limiting movement within screen && applying lateral collisions
        if (characterPosition.y < 0) {
            //Limiting going over screen
            characterPosition.y = 0;
            characterVelocity.y = 0;
        } //HERE SHOULD ADD GAME OVER
        if (characterLeftCollision && characterVelocity.x < 0) {
            //Fixing position due to fast collision
            characterPosition.x = (characterTileLeft.x * tileSize) + tileSize ;
            //Resetting forces when colliding
            characterVelocity.x = characterSlide ? -characterVelocity.x : 0;
            characterAcceleration.x = characterSlide ? characterAcceleration.x * 0.8f : 0;
            if (characterSlide) characterFwd = !characterFwd;
                
        } else if (characterVelocity.x > 0 && characterRightCollision) {
            //Fixing position due to fast collision
            characterPosition.x = (characterTileRight.x * tileSize) - characterSize.x;
            //Resetting forces when colliding
            characterVelocity.x = characterSlide ? -characterVelocity.x : 0;
            characterAcceleration.x = characterSlide ? characterAcceleration.x * 0.8f : 0;
            if (characterSlide) characterFwd = !characterFwd;
        }
    
        //Slide
        if (IsKeyDown(KEY_S) && characterFloorCollision) {
            //Detecting when key is just pressed
            if (IsKeyPressed(KEY_S)) {
                //Moving the character once
                characterPosition.y = characterPosition.y + 10;
            }
            //Decreasing character size
            characterSize.y = 42;
            //Applying state
            characterSlide = true;
            characterAnimState = 5;
            characterFrameLimit = 1;
            characterFrameCycle = 1;
        } else if (characterFloorCollision) {
            //Detecting when key is just released
            if (IsKeyReleased(KEY_S)) {
                //Moving the character once
                characterPosition.y = characterPosition.y - 10;
            }
            //Applying state
            characterSlide = false;
            //Increasing character size
            characterSize.y = 52;
        }
        //Updating character center
        characterHalf.y = characterSize.y / 2;
        
        //Clamping forces
        if (characterVelocity.y > 32) characterVelocity.y = 32;
        else if (characterVelocity.y < -32) characterVelocity.y = -32;

        //Calculating physics
        characterVelocity.x *= characterSlide? 0.95f : 0.8f;
        characterVelocity.y += characterAcceleration.y;
        characterVelocity.x += characterAcceleration.x;
        characterPosition.x += characterVelocity.x;
        characterPosition.y += characterVelocity.y;
    
        //Clamping forces
        if (characterVelocity.y > 32) characterVelocity.y = 32;
        else if (characterVelocity.y < -32) characterVelocity.y = -32;

        //Resetting gravity
        characterAcceleration.x = 0;
        characterAcceleration.y = 0;
        
        //=====CHARACTER=====

        //=====ENEMY=====

        //Gravity
        enemyAcceleration.y += 1;
    
        //Collisions under the enemy
        bool enemyFloorCollision = CheckCollisionDown(enemyPosition, enemySize, collisionTilemap, tileSize);
        Vector2 enemyPointUnder = {enemyPosition.x, enemyPosition.y + enemySize.y + 1};
        Vector2 enemyTileUnder = CheckTilePosition(enemyPointUnder, tileSize);
        
        //Collisions on the left of the enemy
        bool enemyLeftCollision = CheckCollisionLeft(enemyPosition, enemySize, collisionTilemap, tileSize);
        
        //Collisions on the right of the enemy
        bool enemyRightCollision = CheckCollisionRight(enemyPosition, enemySize, collisionTilemap, tileSize);
        
        //Falling
        if (enemyFloorCollision && enemyVelocity.y >= 0) {
            //Edge hopping condition
            if (CheckTileType(enemyTileUnder, collisionTilemap) == 1 ||
            (int)(enemyPosition.y + enemySize.y) % tileSize < 24) {
                //Fixing position to tile position
                enemyPosition.y = (enemyTileUnder.y * tileSize) - enemySize.y;
                //Reseting forces
                enemyVelocity.y = 0;
                enemyAcceleration.y = 0;
                //Preventing falling from screen TEMP
                if ((enemyPosition.y + enemySize.y) > screenHeight) {
                    enemyPosition.y = screenHeight - enemySize.y;
                }
            }
        }
        
        //Changing directions
        if ((enemyFwd && enemyVelocity.x > 0 && enemyRightCollision) ||
        (!enemyFwd && enemyVelocity.x < 0 && enemyLeftCollision)) {
            //Inverting direction
            enemyFwd = !enemyFwd;
            //Resetting enemy velocity (optional)
            enemyVelocity.x = 0;
        }

        //Base behaviour
        enemyAcceleration.x = enemyFwd ? 0.5f : -0.5f;

        //Clamping forces
        if (enemyVelocity.y > 32) enemyVelocity.y = 32;
        else if (enemyVelocity.y < -32) enemyVelocity.y = -32;

        //Calculating physics
        enemyVelocity.x *= 0.8f;
        enemyVelocity.y += enemyAcceleration.y;
        enemyVelocity.x += enemyAcceleration.x;
        enemyPosition.x += enemyVelocity.x;
        enemyPosition.y += enemyVelocity.y;

        //Resetting gravity
        enemyAcceleration.x = 0;
        enemyAcceleration.y = 0;

        //=====ENEMY=====

        //=====CAMERA=====

        //Calculating camera positions
        Vector2 cameraLowerFocus = {
            (mainCamera.offset.x / mainCamera.zoom) - characterHalf.x,
            (mainCamera.offset.y / mainCamera.zoom) - characterHalf.y
            };
        Vector2 cameraUpperFocus = {
            (screenWidth - cameraLowerFocus.x) + characterHalf.x,
            (screenHeight - cameraLowerFocus.y) + characterHalf.y
        };

        //Updating camera position in X axys
        if (characterPosition.x + characterHalf.x > cameraLowerFocus.x + tileSize &&
        characterPosition.x + characterHalf.x < cameraUpperFocus.x - tileSize &&
        !characterRightCollision && !characterLeftCollision) {
            //Moving middle
            mainCamera.target.x = characterPosition.x + characterHalf.x;
            //Updating parallax X axys
            parallaxPositionOffset.x = mainCamera.target.x / 16;
        } else if (characterPosition.x + characterHalf.x <= cameraLowerFocus.x + tileSize &&
        !characterRightCollision && !characterLeftCollision) {
            //Moving left edge
            mainCamera.target.x = cameraLowerFocus.x + tileSize;
        } else if (characterPosition.x + characterHalf.x >= cameraUpperFocus.x - tileSize &&
        !characterRightCollision && !characterLeftCollision) {
            //Moving left edge
            mainCamera.target.x = cameraUpperFocus.x - tileSize;
        }

        //Updating camera position in Y axys
        if (characterPosition.y + characterHalf.y > cameraLowerFocus.y &&
        characterPosition.y + characterHalf.y < cameraUpperFocus.y) {
            //Moving center
            mainCamera.target.y = characterPosition.y + characterHalf.y + (characterSlide ? -5 : 0);
            //Updating parallax Y axys
            parallaxPositionOffset.y = mainCamera.target.y / 16;
        } else if (characterPosition.y + characterHalf.y <= cameraLowerFocus.y) {
            //Moving top edge
            mainCamera.target.y = cameraLowerFocus.y;
        } else if (characterPosition.y + characterHalf.y >= cameraUpperFocus.y) {
            //Moving lower edge
            mainCamera.target.y = cameraUpperFocus.y;
        }

        //Updating camera acceleration
        cameraAcceleration.x = characterVelocity.x * characterVelocity.x / 8;
        if (characterVelocity.x < 0) cameraAcceleration.x *= -1; 
        cameraAcceleration.y = characterVelocity.y * characterVelocity.y / 64;
        if (characterVelocity.y < 0) cameraAcceleration.y *= -1;

        //Reducing camera acceleration
        cameraAcceleration.x *= 0.85f;
        cameraAcceleration.y *= 0.85f;

        //Setting camera target with accelerations
        mainCamera.target.x += cameraAcceleration.x * 2;
        mainCamera.target.y += cameraAcceleration.y * 2;

        //=====CAMERA=====

        //Creating character
        characterAnimRate++;
        if (characterAnimRate > (60 / (characterFrameLimit * characterFrameLimit)) && !characterSlide) { //Temp (if added animation struct/class can define its animation speed)
            //Updating frames
            characterFrameCycle++;
            if (characterAnimState == 2) characterFrameCycle = 2;
            characterAnimRate = 0;
        }
        if (characterFrameCycle > characterFrameLimit) characterFrameCycle = 0;
        Vector2 characterHitbox = {characterPosition.x - 22, characterPosition.y - (12 + ((characterSlide)? + 10 : 0))};
        Rectangle characterSprite = {(float)(characterAnimState * tileSize), (float)(characterFrameCycle * (tileSize)), (float)(tileSize * (characterFwd ? 1 : -1)), (float)tileSize};
        
        //Creating enemy
        Vector2 enemyHitbox = {enemyPosition.x - 22, enemyPosition.y - 12};
        Rectangle enemySprite = {(float)0, (float)0, (float)(tileSize * (enemyFwd ? 1 : -1)), (float)tileSize};

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