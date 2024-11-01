//Libraries
#include "Tilemap.h"

//Class constructors to create an instance (with overloads)
Tilemap::Tilemap(Texture2D _texture, Rectangle _tiles[15], std::vector<std::vector<int>> _background, std::vector<std::vector<int>> _horizon,  std::vector<std::vector<int>> _drawn,  std::vector<std::vector<int>> _hitbox, int _tileSize) {
    //Storing received values as attributes
    this->texture = _texture;
    this->tiles[15] = _tiles[15];
    this->background = _background;
    this->horizon = _horizon;
    this->drawn = _drawn;
    this->hitbox = _hitbox;
    this->tileSize = _tileSize;

    //Calling a starter function
    this->Initialize();
};
Tilemap::Tilemap(Texture2D _texture, Rectangle _tiles[15], std::vector<std::vector<int>> _background, std::vector<std::vector<int>> _horizon,  std::vector<std::vector<int>> _drawn,  std::vector<std::vector<int>> _hitbox) {
    //Storing received values as attributes
    this->texture = _texture;
    this->tiles[15] = _tiles[15];
    this->background = _background;
    this->horizon = _horizon;
    this->drawn = _drawn;
    this->hitbox = _hitbox;

    //Calling a starter function
    this->Initialize();
};
Tilemap::Tilemap(Texture2D _texture, std::vector<std::vector<int>> _background, std::vector<std::vector<int>> _horizon,  std::vector<std::vector<int>> _drawn,  std::vector<std::vector<int>> _hitbox, int _tileSize) {
    //Storing received values as attributes
    this->texture = _texture;
    this->background = _background;
    this->horizon = _horizon;
    this->drawn = _drawn;
    this->hitbox = _hitbox;
    this->tileSize = _tileSize;

    //Calling a starter function
    this->Initialize();
};
Tilemap::Tilemap(Texture2D _texture, std::vector<std::vector<int>> _background, std::vector<std::vector<int>> _horizon,  std::vector<std::vector<int>> _drawn,  std::vector<std::vector<int>> _hitbox) {
    //Storing received values as attributes
    this->texture = _texture;
    this->background = _background;
    this->horizon = _horizon;
    this->drawn = _drawn;
    this->hitbox = _hitbox;

    //Calling a starter function
    this->Initialize();
};

//Method called once for initialize default values
void Tilemap::Initialize() {

}

//Method for process all graphics
void Tilemap::Update() {

}

//Method for process all logicº
void Tilemap::DrawBackground() const {
    //Drawing bg1 tilemap
    for (int y = 0; y < (int)this->background.size(); y++) {
        for (int x = 0; x < (int)this->background[y].size(); x++) {
            Vector2 tilePosition = {
                ((float)x * this->tileSize) - (this->parallaxOffset.x * 2) + (this->tileSize * 1),
                ((float)y * this->tileSize) - (this->parallaxOffset.y * 2)
            };
            //Getting the correct tile
            int tileIndex = background[y][x];
            //Drawing single tile
            DrawTextureRec(this->texture, this->tiles[tileIndex], tilePosition, BLACK);
        }
    }
    //Drawing bg2 tilemap
    for (int y = 0; y < (int)this->horizon.size(); y++) {
        for (int x = 0; x < (int)this->horizon[y].size(); x++) {
            //Calculating each tile position
            Vector2 tilePosition = {
                ((float)x * this->tileSize) - (this->parallaxOffset.x * 8) + (this->tileSize * 4),
                ((float)y * this->tileSize) - (this->parallaxOffset.y * 8)
            };
            //Getting the correct tile
            int tileIndex = horizon[y][x];
            //Drawing single tile
            DrawTextureRec(this->texture, this->tiles[tileIndex], tilePosition, GRAY);
        }
    }
}

//Method for process all logic
void Tilemap::Draw() const {
    //Drawing base tilemap
    for (int y = 0; y < (int)this->drawn.size(); y++) {
        for (int x = 0; x < (int)this->drawn[y].size(); x++) {
            //Calculating each tile position
            Vector2 tilePosition = {
                ((float)x * this->tileSize),
                ((float)y * this->tileSize)
            };
            //Getting the correct tile
            int tileIndex = drawn[y][x];
            //Drawing single tile
            DrawTextureRec(this->texture, this->tiles[tileIndex], tilePosition, WHITE);
        }
    }
}