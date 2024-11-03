//Libraries
#include "raylib.h"
#include "raymath.h"
#include <vector>

//User libraries
#include "Tilemap.h"
#include "Character.h"
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
    const int screenWidth = 1280, screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Base platformer - Prototype - Fernando C. - v0.0.69-alpha");
    SetTargetFPS(60);
    
    /*---------------------------------Game properties--------------------------------------*/

    //Camera variables
    Camera2D mainCamera;
    Vector2 cameraAcceleration = {0,0};
    mainCamera.offset = (Vector2){(float)screenWidth * 0.5f, (float)screenHeight * 0.5f};
    mainCamera.rotation = 0;
    mainCamera.zoom = 1.5f;

    //Level variables
    int ammoLeft = 3;

    //Bullets variables
    Texture2D bulletTexture = LoadTexture("./assets/Other/bullet.png");
    std::vector<Bullet> bulletsList; 

    //Tilemap variables
    Texture2D levelTilesheet = LoadTexture("./assets/Tilemaps/spritesheet_tilemap_red.png");
    Tilemap map = Tilemap(levelTilesheet);
    
    //Character variables
    Texture2D charactersTilesheet = LoadTexture("./assets/Entities/spritesheet_characters.png");
    Character player = Character(charactersTilesheet, {650, 400}, {20, 52}, map);

    //Base enemies variables
    Texture2D muggleEnemyTilesheet = LoadTexture("./assets/Entities/spritesheet_enemies.png");
    Muggle muggleEnemy = Muggle(muggleEnemyTilesheet, {800, 400}, {32, 52}, map);

    //Saw enemies variables
    Texture2D sawEnemyTilemap = LoadTexture("./assets/Entities/spritesheet_enemies.png");
    Saw sawEnemy = Saw(sawEnemyTilemap, {264, 340}, {0, 0}, map); 

    //Parallax variables
    Vector2 parallaxPositionOffset = {0, 32};

    //Cursor variables
    Texture2D aimFullCursorTexture = LoadTexture("./assets/Other/cursor-aim-full.png");
    Texture2D aimEmptyCursorTexture = LoadTexture("./assets/Other/cursor-aim-empty.png");

    /*-------------------------------------Game loop----------------------------------------*/
    while (!WindowShouldClose()) {
        //Brain logic
        
        //=====LEVEL=====

        //Updating tilemap values
        map.parallaxOffset = parallaxPositionOffset;
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
            Bullet newBullet = Bullet(bulletTexture, newBulletPosition, newBulletDirection, 10.0f);
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

        //Calculating camera positions
        Vector2 cameraLowerFocus = {
            (mainCamera.offset.x / mainCamera.zoom) - player.half.x,
            (mainCamera.offset.y / mainCamera.zoom) - player.half.y + (player.sliding ? -5 : 0)
            };
        Vector2 cameraUpperFocus = {
            (screenWidth - cameraLowerFocus.x),
            (screenHeight - cameraLowerFocus.y)
        };

        //Updating camera position in X axys
        if (player.position.x + player.half.x > cameraLowerFocus.x + map.tileSize &&
        player.position.x + player.half.x < cameraUpperFocus.x - map.tileSize) {
            //Moving middle
            mainCamera.target.x = player.position.x + player.half.x;
        } else if (player.position.x + player.half.x <= cameraLowerFocus.x + map.tileSize) {
            //Moving left edge
            mainCamera.target.x = cameraLowerFocus.x + map.tileSize;
        } else if (player.position.x + player.half.x >= cameraUpperFocus.x - map.tileSize) {
            //Moving left edge
            mainCamera.target.x = cameraUpperFocus.x - map.tileSize;
        }

        //Updating camera position in Y axys
        if (player.position.y + player.half.y > cameraLowerFocus.y &&
        player.position.y + player.half.y < cameraUpperFocus.y) {
            //Moving center
            mainCamera.target.y = player.position.y + player.half.y + (player.sliding ? -5 : 0);
        } else if (player.position.y + player.half.y <= cameraLowerFocus.y) {
            //Moving top edge
            mainCamera.target.y = cameraLowerFocus.y;
        } else if (player.position.y + player.half.y >= cameraUpperFocus.y) {
            //Moving lower edge
            mainCamera.target.y = cameraUpperFocus.y;
        }
        //Updating parallax
        parallaxPositionOffset.x = (int)(mainCamera.target.x / 16);
        parallaxPositionOffset.y = (int)(mainCamera.target.y / 16);

        //Updating camera acceleration
        cameraAcceleration.x = player.velocity.x * player.velocity.x / 8;
        if (player.velocity.x < 0) cameraAcceleration.x *= -1; 
        cameraAcceleration.y = player.velocity.y * player.velocity.y / 64;
        if (player.velocity.y < 0) cameraAcceleration.y *= -1;

        //Reducing camera acceleration
        cameraAcceleration.x *= 0.85f;
        cameraAcceleration.y *= 0.85f;

        //Setting camera target with accelerations
        mainCamera.target.x += cameraAcceleration.x * 2;
        mainCamera.target.y += cameraAcceleration.y * 2;

        //======VIEW======

        //=====CURSOR=====
        
        HideCursor();
        float cursorScaleFactor = (map.tileSize / 2) / mainCamera.zoom;
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
        Texture2D cursorTexture = (ammoLeft > 0) ? aimFullCursorTexture : aimEmptyCursorTexture;

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
            DrawTexturePro(cursorTexture, cursorSprite, cursorScaledSprite, cursorSpritePivot, 0.0f, BLUE);
        EndDrawing();
    }
    /*----------------------------------------End-------------------------------------------*/
    CloseWindow();
    return 0;
}