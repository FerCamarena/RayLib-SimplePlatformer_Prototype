//Libraries
#include "raylib.h"
#include "raymath.h"
#include <vector>

//User libraries
#include "Cursor.h"
#include "Tilemap.h"
#include "Character.h"
#include "View.h"
#include "Bullet.h"
#include "Saw.h"
#include "Muggle.h"

/*-------------------------------------DEV NOTES----------------------------------------*/
//
//Project made by Fernando C.
//Base platformer example using Raylib
//
/*--------------------------------------------------------------------------------------*/

/*--------------------------------Project attributes------------------------------------*/

/*---------------------------------Custom functions-------------------------------------*/

/*-----------------------------------Main function--------------------------------------*/
int main(void) {
    //Initialization
    const Vector2 screenSize = {1280.0f, 720.0f};
    InitWindow(screenSize.x, screenSize.y, "Base platformer - Prototype - Fernando C. - v0.0.89-alpha");
    SetTargetFPS(60);
    
    /*---------------------------------Game properties--------------------------------------*/

    //Level variables
    int ammoLeft = 3;

    //Tilemap variables
    Texture2D levelTilesheet = LoadTexture("./assets/Tilemaps/spritesheet_tilemap_red.png");
    Tilemap map = Tilemap(levelTilesheet);
    
    //Character variables
    Texture2D charactersTilesheet = LoadTexture("./assets/Entities/spritesheet_characters.png");
    Character player = Character(charactersTilesheet, {650.0f, 400.0f}, {20.0f, 52.0f}, map);

    //View variables
    Camera2D mainCamera;
    mainCamera.offset = {screenSize.x * 0.5f, screenSize.y * 0.5f};
    mainCamera.rotation = 0.0f;
    mainCamera.zoom = 1.5f;
    View view = View(screenSize, mainCamera, player);

    //Bullets variables
    Texture2D bulletTexture = LoadTexture("./assets/Other/bullet.png");
    std::vector<Bullet> bulletsList; 

    //Muggle enemies variables
    Texture2D muggleEnemyTilesheet = LoadTexture("./assets/Entities/spritesheet_enemies.png");
    Muggle muggleEnemy = Muggle(muggleEnemyTilesheet, {800.0f, 400.0f}, {32.0f, 52.0f}, map);

    //Saw enemies variables
    Texture2D sawEnemyTilemap = LoadTexture("./assets/Entities/spritesheet_enemies.png");
    Saw sawEnemy = Saw(sawEnemyTilemap, {264.0f, 340.0f}, {0.0f, 0.0f}, map); 

    //Cursor variables
    Texture2D cursorTexture = LoadTexture("./assets/Other/cursor-aim-empty.png");
    std::vector<Texture2D> cursorTextures = {
        LoadTexture("./assets/Other/cursor-aim-empty.png"),
        LoadTexture("./assets/Other/cursor-aim-full.png")
    };
    Cursor cursor = Cursor(cursorTexture, {0, 0}, {0, 0}, cursorTextures, mainCamera.zoom, ammoLeft);

    /*-------------------------------------Game loop----------------------------------------*/
    while (!WindowShouldClose()) {
        //Brain logic
        
        //=====LEVEL=====
        
        //Hiding cursor by default
        HideCursor();

        //Updating tilemap values
        map.parallaxOffset = view.positionOffset;
        map.Update();

        //Detecting click to create a bullet when has ammo
        if (ammoLeft > 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            //Decreasing ammo
            ammoLeft--;
            //Storing position
            Vector2 newBulletPosition = Vector2Add(player.position, player.half);
            //Storing direction
            Vector2 newBulletVector = Vector2Subtract(GetScreenToWorld2D(GetMousePosition(), mainCamera), newBulletPosition);
            Vector2 newBulletDirection = Vector2Normalize(newBulletVector);
            //Creating new bullet instance
            Bullet newBullet = Bullet(bulletTexture, newBulletPosition, {0, 0}, newBulletDirection, 10.0f);
            //Storing new bullet
            bulletsList.push_back(newBullet);
        }

        //=====LEVEL=====

        //=====BULLETS=====
    
        //Updating each bullet spawned
        for (auto& bullet : bulletsList) {
            //Make each bullet update itself
            bullet.Update();
        }

        //=====BULLETS=====

        //=====CHARACTER=====

        //Updating character
        player.Update();

        //=====CHARACTER=====

        //=====SAW ENEMY=====

        //Updating saw enemy
        sawEnemy.Update();

        //=====SAW ENEMY=====

        //=====DUMB ENEMY=====

        //Updating muggle enemy
        muggleEnemy.Update();
    
        //=====DUMB ENEMY=====

        //======VIEW======

        view.Update();

        //======VIEW======

        //=====CURSOR=====
        
        cursor.Update();

        //=====CURSOR=====

        /*-------------------------------------Draw phase---------------------------------------*/
        BeginDrawing();
            //Clearing the image with background color
            ClearBackground(PURPLE);
            //Drawing level
            map.DrawBackground();
            BeginMode2D(mainCamera);
                //#Displaying the full levelTilesheet 
                //#DrawTexture(levelTilesheet, 0, 0, WHITE);
                //Drawing base tilemap
                map.Draw();
                //Drawing character
                player.Draw();
                //Drawing base enemy
                muggleEnemy.Draw();
                //Drawing saw enemy
                sawEnemy.Draw();
                //Drawing bullets
                for (const Bullet& bullet : bulletsList) {
                    //Calling draw method for each bullet
                    bullet.Draw();
                }
            EndMode2D();
            //DEBUG

            //Drawing cursor
            cursor.Draw();
        EndDrawing();
    }
    /*----------------------------------------End-------------------------------------------*/
    CloseWindow();
    return 0;
}