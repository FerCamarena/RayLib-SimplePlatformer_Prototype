//Libraries
#include "raylib.h"
#include "raymath.h"
#include <vector>

//User libraries
#include "Bullet.h"
#include "Tilemap.h"

/*-----------------------------------DEV NOTES------------------------------------------*/
//
//Project made by Fernando C.
//Base platformer example using Raylib
//
/*--------------------------------------------------------------------------------------*/

/*-----------------------------Project attributes---------------------------------------*/

/*-------------------------------User functions-----------------------------------------*/

/*-------------------------------Main function------------------------------------------*/
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
    
    //Character variables
    Texture2D charactersTilesheet = LoadTexture("./assets/Entities/spritesheet_characters.png");
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
    Texture2D baseEnemiesTilesheet = LoadTexture("./assets/Entities/spritesheet_enemies.png");
    Texture2D sawEnemiesTilesheet = LoadTexture("./assets/Entities/spritesheet_enemies.png");
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

    //Cursor variables
    Texture2D aimFullCursorTexture = LoadTexture("./assets/Other/cursor-aim-full.png");
    Texture2D aimEmptyCursorTexture = LoadTexture("./assets/Other/cursor-aim-empty.png");

    /*-----------------------------------Game loop------------------------------------------*/
    while (!WindowShouldClose()) {
        //Brain logic
        
        //=====LEVEL=====

        //Creation new instance of tilemap
        std::vector<std::vector<int>> bg2 = {
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
        std::vector<std::vector<int>> bg1 = {
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
        std::vector<std::vector<int>> base = {
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
        std::vector<std::vector<int>> collisions = {
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
        Tilemap map = Tilemap(levelTilesheet, bg2, bg1, base, collisions);

        //Updating tilemap values
        map.parallaxOffset = parallaxPositionOffset;
        map.Update();

        //Detecting click to create a bullet when has ammo
        if (ammoLeft > 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            //Decreasing ammo
            ammoLeft--;
            //Storing position
            Vector2 newBulletPosition = Vector2Add(characterPosition, characterHalf);
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
        
        //Creating character sprite
        Vector2 characterSpritePivot = {characterPosition.x - ((64 - characterSize.x) / 2), characterPosition.y - ((64 - characterSize.y))};
        Rectangle characterArea = {(float)(characterAnimState * 64), (float)(characterFrameCycle * (64)), (float)(64 * (characterFwd ? 1 : -1)), (float)64};
        
        //Collisions under the character
        bool characterFloorCollision = map.CheckCollisionDown(characterPosition, characterSize);
        Vector2 characterPointUnder = {characterPosition.x, characterPosition.y + characterSize.y + 1};
        Vector2 characterTileUnder = map.CheckTilePosition(characterPointUnder); 
        
        //Collisions on the left of the character
        bool characterLeftCollision = map.CheckCollisionLeft(characterPosition, characterSize);
        Vector2 characterPointLeft = {characterPosition.x - 1, characterPosition.y + characterSize.y - 1};
        Vector2 characterTileLeft = map.CheckTilePosition(characterPointLeft); 
        
        //Collisions on the right of the character
        bool characterRightCollision = map.CheckCollisionRight(characterPosition, characterSize);
        Vector2 characterPointRight = {characterPosition.x + characterSize.x, characterPosition.y + characterSize.y - 1};
        Vector2 characterTileRight = map.CheckTilePosition(characterPointRight); 
        
        //Gravity
        characterAcceleration.y += 1;

        //Falling
        if (characterFloorCollision && characterVelocity.y >= 0) {
            //Edge hopping condition
            if (map.CheckTileType(characterTileUnder) == 1 ||
            (int)(characterPosition.y + characterSize.y) % 64 < 24) {
                //Fixing position to tile position
                characterPosition.y = (characterTileUnder.y * 64) - characterSize.y;
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
            ((characterFloorCollision && (int)(characterPosition.y + characterSize.y) % 64 < 4) ||
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
            characterPosition.x = (characterTileLeft.x * 64) + 64 ;
            //Resetting forces when colliding
            characterVelocity.x = characterSlide ? -characterVelocity.x : 0;
            characterAcceleration.x = characterSlide ? characterAcceleration.x * 0.8f : 0;
            if (characterSlide) characterFwd = !characterFwd;
                
        } else if (characterVelocity.x > 0 && characterRightCollision) {
            //Fixing position due to fast collision
            characterPosition.x = (characterTileRight.x * 64) - characterSize.x;
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
        bool sawEnemyFloorCollision = map.CheckCollisionDown(sawEnemyPosition, {0, 0});
        Vector2 sawEnemyPointUnder = {sawEnemyPosition.x, sawEnemyPosition.y + 1};
        Vector2 sawEnemyTileUnder = map.CheckTilePosition(sawEnemyPointUnder);

        bool UpperRight = map.CheckCollisionCustom(sawEnemyPosition, {1, -1}); // upper right
        bool LowerRight = map.CheckCollisionCustom(sawEnemyPosition, {1, 1}); // lower right
        bool UpperLeft = map.CheckCollisionCustom(sawEnemyPosition, {-1, -1}); // upper left
        bool LowerLeft = map.CheckCollisionCustom(sawEnemyPosition, {-1, 1}); // lower left

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
                if (map.CheckTileType(sawEnemyTileUnder) != 0 ||
                (int)(sawEnemyPosition.y) % 64 < 24) {
                    //Sleeping gravity after falling
                    sawEnemyPlaced = true;
                    //Fixing position to tile position
                    sawEnemyPosition.y = (sawEnemyTileUnder.y * 64);
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
        Rectangle sawEnemySprite = {(float)13*64, 0.0f, (float)64, (float)64};

        //=====SAW ENEMY=====

        //=====BASE ENEMY=====
    
        //Collisions under the enemy
        bool baseEnemyFloorCollision = map.CheckCollisionDown(baseEnemyPosition, baseEnemySize);
        Vector2 baseEnemyPointUnder = {baseEnemyPosition.x, baseEnemyPosition.y + baseEnemySize.y + 1};
        Vector2 baseEnemyTileUnder = map.CheckTilePosition(baseEnemyPointUnder);
        
        //Collisions on the left of the baseEnemy
        bool baseEnemyLeftCollision = map.CheckCollisionLeft(baseEnemyPosition, baseEnemySize);
        
        //Collisions on the right of the baseEnemy
        bool baseEnemyRightCollision = map.CheckCollisionRight(baseEnemyPosition, baseEnemySize);

        //Collisions on the left step of the baseEnemy
        bool baseEnemyLeftStep = map.CheckCollisionLeftStep(baseEnemyPosition, baseEnemySize);
        
        //Collisions on the right step of the baseEnemy
        bool baseEnemyRightStep = map.CheckCollisionRightStep(baseEnemyPosition, baseEnemySize);
        
        //Clamping forces
        if (baseEnemyVelocity.y > 32) baseEnemyVelocity.y = 32;
        else if (baseEnemyVelocity.y < -32) baseEnemyVelocity.y = -32;

        //Falling
        if (baseEnemyFloorCollision && baseEnemyVelocity.y >= 0) {
            //Edge hopping condition
            if (map.CheckTileType(baseEnemyTileUnder) == 1 ||
            (int)(baseEnemyPosition.y + baseEnemySize.y) % 64 < 24) {
                //Fixing position to tile position
                baseEnemyPosition.y = (baseEnemyTileUnder.y * 64) - baseEnemySize.y;
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
        Rectangle baseEnemySprite = {(float)0, (float)0, (float)(64 * (baseEnemyFwd ? 1 : -1)), (float)64};
        
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
        if (characterPosition.x + characterHalf.x > cameraLowerFocus.x + 64 &&
        characterPosition.x + characterHalf.x < cameraUpperFocus.x - 64 &&
        !characterRightCollision && !characterLeftCollision) {
            //Moving middle
            mainCamera.target.x = characterPosition.x + characterHalf.x;
            //Updating parallax X axys
            parallaxPositionOffset.x = (int)(mainCamera.target.x / 16);
        } else if (characterPosition.x + characterHalf.x <= cameraLowerFocus.x + 64 &&
        !characterRightCollision && !characterLeftCollision) {
            //Moving left edge
            mainCamera.target.x = (int)(cameraLowerFocus.x + 64);
        } else if (characterPosition.x + characterHalf.x >= cameraUpperFocus.x - 64 &&
        !characterRightCollision && !characterLeftCollision) {
            //Moving left edge
            mainCamera.target.x = (int)(cameraUpperFocus.x - 64);
        }

        //Updating camera position in Y axys
        if (characterPosition.y + characterHalf.y > cameraLowerFocus.y &&
        characterPosition.y + characterHalf.y < cameraUpperFocus.y) {
            //Moving center
            mainCamera.target.y = characterPosition.y + characterHalf.y + (characterSlide ? -5 : 0);
            //Updating parallax Y axys
            parallaxPositionOffset.y = (int)(mainCamera.target.y / 16);
        } else if (characterPosition.y + characterHalf.y <= cameraLowerFocus.y) {
            //Moving top edge
            mainCamera.target.y = (int)cameraLowerFocus.y;
        } else if (characterPosition.y + characterHalf.y >= cameraUpperFocus.y) {
            //Moving lower edge
            mainCamera.target.y = (int)cameraUpperFocus.y;
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
        float cursorScaleFactor = (64 / 2) / mainCamera.zoom;
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

        /*---------------------------------------Draw phase--------------------------------------*/
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
                DrawTextureRec(charactersTilesheet, characterArea, characterSpritePivot, GOLD);
                //Drawing enemies
                DrawTextureRec(baseEnemiesTilesheet, baseEnemySprite, baseEnemyPivot, RED);
                DrawTextureRec(sawEnemiesTilesheet, sawEnemySprite, sawEnemyPivot, RED);
                //Drawing bullets
                for (const auto& bullet : bulletsList) {
                    bullet.Draw();
                }
            EndMode2D();
            //Drawing cursor
            DrawTexturePro(cursorTexture, cursorSprite, cursorScaledSprite, cursorSpritePivot, 0.0f, BLUE);
        EndDrawing();
    }
    /*------------------------------------------End-----------------------------------------*/
    CloseWindow();
    return 0;
}