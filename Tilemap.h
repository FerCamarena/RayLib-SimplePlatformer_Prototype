//Libraries
#pragma once
#include "raylib.h"
#include "json.hpp"
#include <vector>
#include <fstream>
using json = nlohmann::json;

//Add comments for every class in each parameter group and check for protection modifiers
/*-----------------------------------Main class-----------------------------------------*/
class Tilemap {
    //Attributes
    public:
        //Variables for graphic rendering
        Texture2D texture = LoadTexture("./assets/Tilemaps/spritesheet_tilemap_red.png");
        int tileSize;
        int width;
        int height;
        Rectangle tileset[15];
        std::vector<std::vector<int>> background;
        std::vector<std::vector<int>> horizon;
        std::vector<std::vector<int>> drawn;
        std::vector<std::vector<int>> hitbox;
        std::vector<std::vector<int>> spawns;
        Vector2 parallaxOffset = {0.0f, 0.0f};

    private:

    //Methods
    public:
        //Class constructor to create an instance
        Tilemap(Texture2D, int);
        //Method for process all logic
        void Update();
        //Methods for process all graphics
        void Draw() const;
        void DrawBackground() const;
        //Methods called for internal calculations
        Vector2 CheckTilePosition(Vector2) const;
        int CheckTileType(Vector2) const;
        //Methods for solving external collision calls
        bool CheckCollisionDown(Vector2, Vector2) const;
        bool CheckCollisionOver(Vector2, Vector2) const;
        bool CheckCollisionLeft(Vector2, Vector2) const;
        bool CheckCollisionRight(Vector2, Vector2) const;
        bool CheckCollisionCustom(Vector2, Vector2) const;
        bool CheckCollisionPoint(Vector2) const;
        bool CheckCollisionRightStep(Vector2, Vector2) const;
        bool CheckCollisionLeftStep(Vector2, Vector2) const;

    private:

};