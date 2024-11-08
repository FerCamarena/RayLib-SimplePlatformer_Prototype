//Libraries
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <memory>

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
//                      Project made by Fernando C.
//                      Base platformer example using Raylib
//
/*--------------------------------------------------------------------------------------*/

/*--------------------------------Project attributes------------------------------------*/

/*---------------------------------Custom functions-------------------------------------*/

void InitializeLevel(Tilemap& level, std::vector<std::unique_ptr<Entity>>& enemyList) {
    //Hiding cursor by default
    HideCursor();

    //Spawning all enemies
    for (int y = 0; y < (int)level.spawns.size(); y++) {
        for (int x = 0; x < (int)level.spawns[y].size(); x++) {
            switch (level.spawns[y][x]) {
                case 0:
                    continue;
                case 1:
                    enemyList.push_back(std::make_unique<Muggle>(Muggle({(float)x * level.tileSize, (float)y * level.tileSize}, {32.0f, 32.0f}, level)));
                break;
                case 2:
                    enemyList.push_back(std::make_unique<Saw>(Saw({(float)x * level.tileSize, (float)y * level.tileSize}, {32.0f, 32.0f}, level)));
                break;
            }
        }
    }
};

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
    Tilemap level = Tilemap(levelTilesheet);

    //Character variables
    Texture2D charactersTilesheet = LoadTexture("./assets/Entities/spritesheet_characters.png");
    Character player = Character(charactersTilesheet, {650.0f, 400.0f}, {20.0f, 52.0f}, level);

    //View variables
    Camera2D mainCamera;
    mainCamera.offset = {screenSize.x * 0.5f, screenSize.y * 0.5f};
    mainCamera.rotation = 0.0f;
    mainCamera.zoom = 1.5f;
    View view = View(screenSize, mainCamera, player);

    //Bullets variables
    Texture2D bulletTexture = LoadTexture("./assets/Other/bullet.png");
    std::vector<Bullet> bulletsList; 

    //Enemies variables
    std::vector<std::unique_ptr<Entity>> enemyList;

    //Cursor variables
    Texture2D cursorTexture = LoadTexture("./assets/Other/cursor-aim-empty.png");
    std::vector<Texture2D> cursorTextures = {
        LoadTexture("./assets/Other/cursor-aim-empty.png"),
        LoadTexture("./assets/Other/cursor-aim-full.png")
    };
    Cursor cursor = Cursor(cursorTexture, {0, 0}, {0, 0}, cursorTextures, mainCamera.zoom, ammoLeft);

    //Calling function to populate level
    InitializeLevel(level, enemyList);

    /*-------------------------------------Game loop----------------------------------------*/
    while (!WindowShouldClose()) {
        //Brain logic
        
        //=====LEVEL=====

        //Iterating for collisions with each enemy
        for (auto it = enemyList.begin(); it != enemyList.end(); ) {
            //Checking collision with individual enemies
            if (CheckCollisionRecs(player.hitbox, (*it)->hitbox)) {
                //Change to game over scene
                break;
            //Continue checking
            } else ++it;
        }

        //Updating tilemap values
        level.parallaxOffset = view.positionOffset;
        level.Update();

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

        //=====BULLETS=====
    
        //Updating each bullet spawned
        for (auto& bullet : bulletsList) {
            //Make each bullet update itself
            bullet.Update();
        }

        //=====CHARACTER=====

        //Updating character
        player.Update();

        //=====ENEMIES=====

        //Updating enemies
        for (auto& enemy : enemyList) {
            //Calling update method for each enemy
            enemy->Update();
        }

        //======VIEW======

        view.Update();

        //=====CURSOR=====
        
        cursor.Update();

        /*-------------------------------------Draw phase---------------------------------------*/
        BeginDrawing();
            //Clearing the image with background color
            ClearBackground(PURPLE);
            //Drawing level
            level.DrawBackground();
            BeginMode2D(mainCamera);
                //#Displaying the full levelTilesheet 
                //#DrawTexture(levelTilesheet, 0, 0, WHITE);
                //Drawing base tilemap
                level.Draw();
                //Drawing character
                player.Draw();
                //Drawing enemies
                for (const auto& enemy : enemyList) {
                    //Calling draw method for each enemy
                    enemy->Draw();
                }
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