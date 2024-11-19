//Libraries
#pragma once
#include <vector>
#include <memory>

//User libraries
#include "Scene.h"
#include "Cursor.h"
#include "Tilemap.h"
#include "Character.h"
#include "View.h"
#include "Bullet.h"
#include "Saw.h"
#include "Muggle.h"

/*-----------------------------------Class main-----------------------------------------*/
class Level_02 : public Scene {
    //Attributes
    public:
        //Level variables
        int ammoLeft = 3;

        //Tilemap variables
        Texture2D levelTilesheet = LoadTexture("./assets/Tilemaps/spritesheet_tilemap_red.png");
        Tilemap level = Tilemap(levelTilesheet, 2);

        //Character variables
        Texture2D charactersTilesheet = LoadTexture("./assets/Entities/spritesheet_characters.png");
        Character player = Character(charactersTilesheet, {650.0f, 400.0f}, {20.0f, 52.0f}, level);

        //View variables
        Camera2D mainCamera;
        View view = View((Vector2){(float)GetScreenWidth(), (float)GetScreenHeight()}, mainCamera, player);

        //Bullets variables
        std::vector<std::unique_ptr<Bullet>> bulletsList;
        std::vector<std::unique_ptr<Bullet>> bulletsPool;

        //Enemies variables
        std::vector<std::unique_ptr<Entity>> enemyList;

        //Cursor variables
        Texture2D cursorTexture = LoadTexture("./assets/Other/cursor-aim-empty.png");
        std::vector<Texture2D> cursorTextures = {
            LoadTexture("./assets/Other/cursor-aim-empty.png"),
            LoadTexture("./assets/Other/cursor-aim-full.png")
        };
        Cursor cursor = Cursor(cursorTexture, {0, 0}, {0, 0}, cursorTextures, mainCamera.zoom, ammoLeft);

    private:

    //Methods
    public:
        //Class constructors to create an instance
        Level_02();
        //Class virtual destructor
        virtual ~Level_02() = default;
        //Methods for process all logic
        void Update() override;
        void InitializeLevel();
        //Method for process all graphics
        void Draw() const override;
        
    private:

};