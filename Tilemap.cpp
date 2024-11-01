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

//Method for process all logic
void Tilemap::DrawBackground() const {
    //Drawing bg1 tilemap
    for (int i = 0; i < this->background.size(); i++) {
        if (this->background[i].size() >= 2) {
            Vector2 tilePosition = {
                ((float)this->background[i][0] * this->tileSize) - (this->parallaxOffset.x * 2) + (this->tileSize * 1),
                ((float)this->background[i][1] * this->tileSize) - (this->parallaxOffset.y * 2)
            };
            //Drawing single tile
            DrawTextureRec(this->texture, this->tiles[i], tilePosition, BLACK);
        }
    }
    //Drawing bg2 tilemap
    for (int i = 0; i < this->horizon.size(); i++) {
        if (this->horizon[i].size() >= 2) {
            //Calculating each tile position
            Vector2 tilePosition = {
                ((float)this->horizon[i][0] * this->tileSize) - (this->parallaxOffset.x * 8) + (this->tileSize * 4),
                ((float)this->horizon[i][1] * this->tileSize) - (this->parallaxOffset.y * 8)
            };
            //Drawing single tile
            DrawTextureRec(this->texture, this->tiles[i], tilePosition, GRAY);
        }
    }
}

//Method for process all logic
void Tilemap::Draw() const {
    //Drawing base tilemap
    for (int i = 0; i < this->drawn.size(); i++) {
        if (this->drawn[i].size() >= 2) {
            //Calculating each tile position
            Vector2 tilePosition = {
                ((float)this->drawn[i][0] * this->tileSize),
                ((float)this->drawn[i][1] * this->tileSize)
            };
            //Drawing single tile
            DrawTextureRec(this->texture, this->tiles[i], tilePosition, WHITE);
        }
    }
}