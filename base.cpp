//Libraries
#include "raylib.h"
#include "raymath.h"

/*-----------------------------------DEV NOTES------------------------------------------*/
//
//Project made by Fernando C.
//Base platformer example using Raylib
//
/*--------------------------------------------------------------------------------------*/

/*------------------------------Project attributes--------------------------------------*/

//Map variables 8:4.5 - 16:9 - 24:13.5
#define tilemapSizeX 25
#define tilemapSizeY 15
int tileSize = 64;

/*---------------------------------User methods-----------------------------------------*/
//Tilemap

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
    Vector2 pointB = {entityPosition.x + entitySize.x, entityPosition.y + entitySize.y + 1};
    //Precalculating
    Vector2 tilePointA = CheckTilePosition(pointA, tileSize);
    Vector2 tilePointB = CheckTilePosition(pointB, tileSize);
    //Checking types on points
    if (CheckTileType(tilePointA, collisiontilemap) > 0 ||
    CheckTileType(tilePointB, collisiontilemap) > 0) return true;
    else return false;
}

//Function for detecting when colliding with a tile with collision in the left side of entities
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
    pointD.x <= tileSize) return true;
    else return false;
}

//Function for detecting when colliding with a tile with collision in the right side of entities
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
    pointG.x >= GetScreenWidth() - tileSize) return true;
    else return false;
}

//Function for detecting collision with tiles in the left step of entities
bool CheckCollisionLeftStep(Vector2 entityPosition, Vector2 entitySize, int collisiontilemap[][tilemapSizeX], int tileSize) {
    //PointI
    Vector2 pointI = {entityPosition.x - 1, entityPosition.y + entitySize.y + 1};
    //Precalculating
    Vector2 tilePointI = CheckTilePosition(pointI, tileSize);
    //Returning on each case
    if (CheckTileType(tilePointI, collisiontilemap) != 0 ||
    pointI.x <= tileSize) return true;
    else return false;
}

//Function for detecting collision with tiles in the right step of entities
bool CheckCollisionRightStep(Vector2 entityPosition, Vector2 entitySize, int collisiontilemap[][tilemapSizeX], int tileSize) {
    //PointJ
    Vector2 pointJ = {entityPosition.x + entitySize.x + 1, entityPosition.y + entitySize.y + 1};
    //Precalculating
    Vector2 tilePointJ = CheckTilePosition(pointJ, tileSize);
    //Returning on each case
    if (CheckTileType(tilePointJ, collisiontilemap) != 0 ||
    pointJ.x <= tileSize) return true;
    else return false;
}

//Function to detect tile limits with different entity directions
bool CheckCollisionCustom(Vector2 entityPosition, Vector2 collisionDirection, int collisiontilemap[][tilemapSizeX], int tileSize) {
    //PointJ
    Vector2 pointJ = {entityPosition.x + collisionDirection.x, entityPosition.y + collisionDirection.y};
    //Precalculating
    Vector2 tilePointJ = CheckTilePosition(pointJ, tileSize);
    //Returning on each case
    if (CheckTileType(tilePointJ, collisiontilemap) == 1 ||
    (pointJ.x < tileSize && collisionDirection.x < 0) ||
    (pointJ.x > GetScreenWidth() - tileSize && collisionDirection.x > 0)) return true;
    else return false;
}

/*-------------------------------Main function------------------------------------------*/
int main(void) {
    //Initialization
    const int screenWidth = (tilemapSizeX * tileSize) - tileSize, screenHeight = (tilemapSizeY * tileSize) - tileSize;
    InitWindow(screenWidth, screenHeight, "Base platformer - Prototype - Fernando C. - v0.0.55-alpha");
    SetTargetFPS(60);
    
    /*---------------------------------Game properties--------------------------------------*/

    //Camera variables
    Camera2D mainCamera;
    Vector2 cameraAcceleration = {0,0};
    mainCamera.offset = (Vector2){(float)screenWidth * 0.5f, (float)screenHeight * 0.5f};
    mainCamera.rotation = 0;
    mainCamera.zoom = 1.5f;

    //Level variables
    int bulletCount = 1;

    //Bullet variables
    Texture2D bulletTexture = LoadTexture("./assets/Other/bullet.png");
    Vector2 bulletPosition = {256, 256};
    Vector2 bulletDirection = {0, 0};
    float bulletSpeed = 10.0f;
    bool bulletState = false;
    //float bulletRotation = 0;

    //Tilemap variables
    Texture2D levelTilesheet = LoadTexture("./assets/Tilemaps/spritesheet_tilemap_red.png");
    Texture2D charactersTilesheet = LoadTexture("./assets/Entities/spritesheet_characters.png");
    Texture2D baseEnemiesTilesheet = LoadTexture("./assets/Entities/spritesheet_enemies.png");
    Texture2D sawEnemiesTilesheet = LoadTexture("./assets/Entities/spritesheet_enemies.png");
    Texture2D aimFullCursorTexture = LoadTexture("./assets/Other/cursor-aim-full.png");
    Texture2D aimEmptyCursorTexture = LoadTexture("./assets/Other/cursor-aim-empty.png");
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
        { 0, 0, 0, 0, 5, 4, 4, 6, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8,10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
        { 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    //Character variables
    Vector2 characterVelocity = {0, 0};
    Vector2 characterAcceleration = {0, 0};
    Vector2 characterPosition = {650, 400};
    Vector2 characterSize = {20, 52};
    Vector2 characterHalf = {(characterSize.x * 0.5f), (characterSize.y * 0.5f)};
    int characterAnimState = 0;
    int characterFrameLimit = 1;
    int characterFrameCycle = 0;
    int characterAnimRate = 20;
    bool characterFwd = true;
    bool characterSlide = false;

    //Base enemies variables
    Vector2 baseEnemyPosition = {800, 400};
    Vector2 baseEnemyVelocity = {0, 0};
    Vector2 baseEnemyAcceleration = {0, 0};
    Vector2 baseEnemySize = {32, 52};
    bool baseEnemyFwd = true;

    //Saw enemies variables
    Vector2 sawEnemyPosition = {264, 340};
    Vector2 sawEnemyVelocity = {0, 0};
    Vector2 sawEnemyAcceleration = {0, 0};
    Vector2 sawEnemyDirection = {0, 0};
    bool sawEnemyPlaced = false;

    //Parallax variables
    Vector2 parallaxPositionOffset = {0, 32};

    /*-----------------------------------Game loop------------------------------------------*/
    while (!WindowShouldClose()) {
        //Brain logic
        
        //=====LEVEL=====

        if (bulletCount > 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            //Decreasing bullet amount
            bulletCount--;
            //Positioning bullet
            bulletPosition = Vector2Add(characterPosition, characterHalf);
            //Setting bullet start rotation
            Vector2 bulletVector = Vector2Subtract(GetScreenToWorld2D(GetMousePosition(), mainCamera), bulletPosition);
            bulletDirection = Vector2Normalize(bulletVector);
            bulletDirection = Vector2Scale(bulletDirection, bulletSpeed);
            //Sending bullet WIP
        }

        //=====LEVEL=====

        //=====BULLETS=====

        if (bulletCount == 0) {
            //Move the bullet
            bulletPosition = Vector2Add(bulletPosition, bulletDirection);
            //Enabling bullet
            bulletState = true;
            //Check collisions with enemies WIP
        }

        //Creating bullet
        Vector2 bulletPivot = {bulletPosition.x - (bulletTexture.width / 2), bulletPosition.y - (bulletTexture.height / 2)};
        Rectangle bulletSprite = {0.0f, 0.0f, (float)(bulletState) ? bulletTexture.width : 0.0f, (float)(bulletState) ? bulletTexture.height : 0.0f};
        
        //=====BULLETS=====

        //=====CHARACTER=====
        
        //Creating character sprite
        Vector2 characterSpritePivot = {characterPosition.x - ((tileSize - characterSize.x) / 2), characterPosition.y - ((tileSize - characterSize.y))};
        Rectangle characterArea = {(float)(characterAnimState * tileSize), (float)(characterFrameCycle * (tileSize)), (float)(tileSize * (characterFwd ? 1 : -1)), (float)tileSize};
        
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
        
        //Gravity
        characterAcceleration.y += 1;

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
        //Updating character center point
        characterHalf.y = characterSize.y / 2;
        
        //Clamping forces
        if (characterVelocity.y > 32) characterVelocity.y = 32;
        else if (characterVelocity.y < -32) characterVelocity.y = -32;

        //Calculating physics
        characterVelocity.x *= characterSlide ? 0.95f : 0.8f;
        characterVelocity.y += characterAcceleration.y;
        characterVelocity.x += characterAcceleration.x;
        characterPosition.x += characterVelocity.x;
        characterPosition.y += characterVelocity.y;
    
        //Clamping forces
        if (characterVelocity.y > 32) characterVelocity.y = 32;
        else if (characterVelocity.y < -32) characterVelocity.y = -32;

        //Resetting acceleration
        characterAcceleration.x = 0;
        characterAcceleration.y = 0;
        
        //Animating character
        characterAnimRate++;
        if (characterAnimRate > (60 / (characterFrameLimit * characterFrameLimit)) && !characterSlide) { //Temp (if added animation struct/class can define its animation speed)
            //Updating frames
            characterFrameCycle++;
            if (characterAnimState == 2) characterFrameCycle = 2;
            characterAnimRate = 0;
        }
        if (characterFrameCycle > characterFrameLimit) characterFrameCycle = 0;

        //=====CHARACTER=====

        //=====SAW ENEMY=====

        //Collisions under the enemy
        bool sawEnemyFloorCollision = CheckCollisionDown(sawEnemyPosition, {0, 0}, collisionTilemap, tileSize);
        Vector2 sawEnemyPointUnder = {sawEnemyPosition.x, sawEnemyPosition.y + 1};
        Vector2 sawEnemyTileUnder = CheckTilePosition(sawEnemyPointUnder, tileSize);

        bool UpperRight = CheckCollisionCustom(sawEnemyPosition, {1, -1}, collisionTilemap, tileSize); // upper right
        bool LowerRight = CheckCollisionCustom(sawEnemyPosition, {1, 1}, collisionTilemap, tileSize); // lower right
        bool UpperLeft = CheckCollisionCustom(sawEnemyPosition, {-1, -1}, collisionTilemap, tileSize); // upper left
        bool LowerLeft = CheckCollisionCustom(sawEnemyPosition, {-1, 1}, collisionTilemap, tileSize); // lower left

        //Clamping forces
        if (sawEnemyVelocity.y > 32) sawEnemyVelocity.y = 32;
        else if (sawEnemyVelocity.y < -32) sawEnemyVelocity.y = -32;
              
        //Base behaviour
        if (sawEnemyPlaced) {
            //Changing directions
            if ((UpperLeft && LowerLeft) || (!LowerRight && !LowerLeft && UpperLeft && !UpperRight)) {
                //move up
                sawEnemyDirection = {0, -1};
            } else if ((LowerLeft && LowerRight) || (!LowerRight && LowerLeft && !UpperLeft && !UpperRight)) {
                //move left
                sawEnemyDirection = {-1, 0};
            } else if ((UpperRight && LowerRight) || (LowerRight && !LowerLeft && !UpperLeft && !UpperRight)) {
                //move down
                sawEnemyDirection = {0, 1};
            } else if ((UpperLeft && UpperRight) || (!LowerRight && !LowerLeft && !UpperLeft && UpperRight)) {
                //move right
                sawEnemyDirection = {1, 0};
            } else {
                sawEnemyVelocity = {0, 0};
                sawEnemyDirection = {0, 0};
                sawEnemyPlaced = false;
            }
            sawEnemyPosition.x += sawEnemyDirection.x;
            sawEnemyPosition.y += sawEnemyDirection.y;
        } else {
            //Gravity
            sawEnemyAcceleration.y += 1;
            //Falling
            if (sawEnemyFloorCollision && sawEnemyVelocity.y >= 0) {
                //Edge hopping condition
                if (CheckTileType(sawEnemyTileUnder, collisionTilemap) != 0 ||
                (int)(sawEnemyPosition.y) % tileSize < 24) {
                    //Sleeping gravity after falling
                    sawEnemyPlaced = true;
                    //Fixing position to tile position
                    sawEnemyPosition.y = (sawEnemyTileUnder.y * tileSize);
                    //Reseting forces
                    sawEnemyVelocity.y = 0;
                    sawEnemyAcceleration.y = 0;
                    //Preventing falling from screen TEMP
                    if ((sawEnemyPosition.y) > screenHeight) {
                        sawEnemyPosition.y = screenHeight;
                    }
                }
            }
        }

        //Calculating physics
        sawEnemyVelocity.x *= 0.8f;
        sawEnemyVelocity.x += sawEnemyAcceleration.x;
        sawEnemyVelocity.y += sawEnemyAcceleration.y;
        sawEnemyPosition.x += sawEnemyVelocity.x;
        sawEnemyPosition.y += sawEnemyVelocity.y;

        //Resetting acceleration
        sawEnemyAcceleration.x = 0;
        sawEnemyAcceleration.y = 0;

        //Creating sawEnemy
        Vector2 sawEnemyPivot = {sawEnemyPosition.x - 32, sawEnemyPosition.y - 32};
        Rectangle sawEnemySprite = {(float)13*64, (float)0, (float)tileSize, (float)tileSize};

        //=====SAW ENEMY=====

        //=====BASE ENEMY=====
    
        //Collisions under the enemy
        bool baseEnemyFloorCollision = CheckCollisionDown(baseEnemyPosition, baseEnemySize, collisionTilemap, tileSize);
        Vector2 baseEnemyPointUnder = {baseEnemyPosition.x, baseEnemyPosition.y + baseEnemySize.y + 1};
        Vector2 baseEnemyTileUnder = CheckTilePosition(baseEnemyPointUnder, tileSize);
        
        //Collisions on the left of the baseEnemy
        bool baseEnemyLeftCollision = CheckCollisionLeft(baseEnemyPosition, baseEnemySize, collisionTilemap, tileSize);
        
        //Collisions on the right of the baseEnemy
        bool baseEnemyRightCollision = CheckCollisionRight(baseEnemyPosition, baseEnemySize, collisionTilemap, tileSize);

        //Collisions on the left step of the baseEnemy
        bool baseEnemyLeftStep = CheckCollisionLeftStep(baseEnemyPosition, baseEnemySize, collisionTilemap, tileSize);
        
        //Collisions on the right step of the baseEnemy
        bool baseEnemyRightStep = CheckCollisionRightStep(baseEnemyPosition, baseEnemySize, collisionTilemap, tileSize);
        
        //Clamping forces
        if (baseEnemyVelocity.y > 32) baseEnemyVelocity.y = 32;
        else if (baseEnemyVelocity.y < -32) baseEnemyVelocity.y = -32;

        //Falling
        if (baseEnemyFloorCollision && baseEnemyVelocity.y >= 0) {
            //Edge hopping condition
            if (CheckTileType(baseEnemyTileUnder, collisionTilemap) == 1 ||
            (int)(baseEnemyPosition.y + baseEnemySize.y) % tileSize < 24) {
                //Fixing position to tile position
                baseEnemyPosition.y = (baseEnemyTileUnder.y * tileSize) - baseEnemySize.y;
                //Reseting forces
                baseEnemyVelocity.y = 0;
                baseEnemyAcceleration.y = 0;
                //Preventing falling from screen TEMP
                if ((baseEnemyPosition.y + baseEnemySize.y) > screenHeight) {
                    baseEnemyPosition.y = screenHeight - baseEnemySize.y;
                }
            }
        }
        
        //Changing directions
        if ((baseEnemyFwd && baseEnemyVelocity.x > 0 && (baseEnemyRightCollision || !baseEnemyRightStep)) ||
        (!baseEnemyFwd && baseEnemyVelocity.x < 0 && (baseEnemyLeftCollision || !baseEnemyLeftStep))) {
            //Inverting direction
            baseEnemyFwd = !baseEnemyFwd;
            //Resetting baseEnemy velocity (optional)
            baseEnemyVelocity.x = 0;
        }

        //Base behaviour
        baseEnemyAcceleration.x = baseEnemyFwd ? 0.5f : -0.5f;

        //Gravity
        baseEnemyAcceleration.y += 1;

        //Calculating physics
        baseEnemyVelocity.x *= 0.8f;
        baseEnemyVelocity.y += baseEnemyAcceleration.y;
        baseEnemyVelocity.x += baseEnemyAcceleration.x;
        baseEnemyPosition.x += baseEnemyVelocity.x;
        baseEnemyPosition.y += baseEnemyVelocity.y;

        //Resetting acceleration
        baseEnemyAcceleration.x = 0;
        baseEnemyAcceleration.y = 0;

        //Creating baseEnemy
        Vector2 baseEnemyPivot = {baseEnemyPosition.x - 16, baseEnemyPosition.y - 12};
        Rectangle baseEnemySprite = {(float)0, (float)0, (float)(tileSize * (baseEnemyFwd ? 1 : -1)), (float)tileSize};
        
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

        //=====CURSOR=====
        
        HideCursor();
        float cursorScaleFactor = (tileSize / 2) / mainCamera.zoom;
        float cursorScale = screenHeight / cursorScaleFactor;
        Rectangle cursorSprite = {
            0.0f, 0.0f,
            (float)aimFullCursorTexture.width, (float)aimFullCursorTexture.height
        };
        Rectangle cursorScaledSprite = {
            GetMousePosition().x, GetMousePosition().y,
            cursorScale, cursorScale
        };
        Vector2 cursorSpritePivot = {
            (aimFullCursorTexture.width * 0.33f),
            (aimFullCursorTexture.height * 0.33f)
        };

        //Selecting cursor texture
        Texture2D cursorTexture = (bulletCount > 0) ? aimFullCursorTexture : aimEmptyCursorTexture;

        //=====CURSOR=====

        /*---------------------------------------Draw phase--------------------------------------*/
        BeginDrawing();
            //Clearing the image with background color
            ClearBackground(PURPLE);
            //Drawing bg1 tilemap
            for (int x = 0; x < tilemapSizeX + 4; x++) {
                for (int y = 0; y < tilemapSizeY + 1; y++) {
                    Vector2 tilePosition = {((float)x * tileSize) - (parallaxPositionOffset.x * 2) + (tileSize * 1), ((float)y * tileSize) - (parallaxPositionOffset.y * 2)};
                    int tileIndex = bg2Tilemap[y][x];
                    //Drawing single tile
                    DrawTextureRec(levelTilesheet, tiles[tileIndex], tilePosition, BLACK);
                }
            }
            //Drawing bg2 tilemap
            for (int x = 0; x < tilemapSizeX + 8; x++) {
                for (int y = 0; y < tilemapSizeY + 2; y++) {
                    Vector2 tilePosition = {((float)x * tileSize) - (parallaxPositionOffset.x * 8) + (tileSize * 4), ((float)y * tileSize) - (parallaxPositionOffset.y * 8)};
                    int tileIndex = bg1Tilemap[y][x];
                    //Drawing single tile
                    DrawTextureRec(levelTilesheet, tiles[tileIndex], tilePosition, GRAY);
                }
            }
            BeginMode2D(mainCamera);
                //#Displaying the full levelTilesheet 
                //#DrawTexture(levelTilesheet, 0, 0, WHITE);
                //Drawing base tilemap
                for (int x = 0; x < tilemapSizeX; x++) {
                    for (int y = 0; y < tilemapSizeY; y++) {
                        Vector2 tilePosition = {((float)x * tileSize), ((float)y * tileSize)};
                        int tileIndex = baseTilemap[y][x];
                        //Drawing single tile
                        DrawTextureRec(levelTilesheet, tiles[tileIndex], tilePosition, WHITE);
                    }
                }
                //Drawing character
                DrawTextureRec(charactersTilesheet, characterArea, characterSpritePivot, GOLD);
                //Drawing enemies
                DrawTextureRec(baseEnemiesTilesheet, baseEnemySprite, baseEnemyPivot, RED);
                DrawTextureRec(sawEnemiesTilesheet, sawEnemySprite, sawEnemyPivot, RED);
                //Drawing bullets
                DrawTextureRec(bulletTexture, bulletSprite, bulletPivot, BLUE);
            EndMode2D();
            //Drawing cursor
            DrawTexturePro(cursorTexture, cursorSprite, cursorScaledSprite, cursorSpritePivot, 0.0f, BLUE);
        EndDrawing();
    }
    /*------------------------------------------End-----------------------------------------*/
    CloseWindow();
    return 0;
}