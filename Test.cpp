//Libraries
#include "raylib.h"
#include "raymath.h"
#include <vector>

//User libraries
#include "Tilemap.h"
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

        //======VIEW======

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
                DrawTextureRec(charactersTilesheet, characterArea, characterSpritePivot, GOLD);
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