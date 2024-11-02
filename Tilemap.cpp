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

//Method for getting tile position in world position
Vector2 Tilemap::CheckTilePosition(Vector2 checkPosition) {
    //Calculating position
    Vector2 tilePosition = {(float)((int)(checkPosition.x / this->tileSize)), (float)((int)(checkPosition.y / this->tileSize))};
    //Returning position
    return tilePosition;
}

//Method for checking tile type in tile position
int Tilemap::CheckTileType(Vector2 tilePosition) {
    //Calculating tile position
    int posX = tilePosition.x;
    int posY = tilePosition.y;
    //Returning the type of the collision tilemap tile
    return this->hitbox[posY][posX];
}

//Looking for collisions under the character
bool Tilemap::CheckCollisionDown(Vector2 entityPosition, Vector2 entitySize) {
    //PointA
    Vector2 pointA = {entityPosition.x, entityPosition.y + entitySize.y + 1};
    //PointB
    Vector2 pointB = {entityPosition.x + entitySize.x, entityPosition.y + entitySize.y + 1};
    //Precalculating
    Vector2 tilePointA = CheckTilePosition(pointA);
    Vector2 tilePointB = CheckTilePosition(pointB);
    //Checking types on points
    if (CheckTileType(tilePointA) > 0 ||
    CheckTileType(tilePointB) > 0) return true;
    else return false;
}

//Function for detecting when colliding with a tile with collision in the left side of entities
bool Tilemap::CheckCollisionLeft(Vector2 entityPosition, Vector2 entitySize) {
    //PointC
    Vector2 pointC = {entityPosition.x - 1, entityPosition.y};
    //PointD
    Vector2 pointD = {entityPosition.x - 1, entityPosition.y + (entitySize.y * 0.5f)};
    //PointE
    Vector2 pointE = {entityPosition.x - 1, entityPosition.y + entitySize.y - 1};
    //Precalculating
    Vector2 tilePointC = CheckTilePosition(pointC);
    Vector2 tilePointD = CheckTilePosition(pointD);
    Vector2 tilePointE = CheckTilePosition(pointE);
    //Returning on each case
    if (CheckTileType(tilePointC) == 1 ||
    CheckTileType(tilePointD) == 1 ||
    CheckTileType(tilePointE) == 1 ||
    pointD.x <= tileSize) return true;
    else return false;
}

//Function for detecting when colliding with a tile with collision in the right side of entities
bool Tilemap::CheckCollisionRight(Vector2 entityPosition, Vector2 entitySize) {
    //PointC
    Vector2 pointF = {entityPosition.x + entitySize.x, entityPosition.y};
    //PointD
    Vector2 pointG = {entityPosition.x + entitySize.x, entityPosition.y + (entitySize.y * 0.5f)};
    //PointE
    Vector2 pointH = {entityPosition.x + entitySize.x, entityPosition.y + entitySize.y - 1};
    //Precalculating
    Vector2 tilePointF = CheckTilePosition(pointF);
    Vector2 tilePointG = CheckTilePosition(pointG);
    Vector2 tilePointH = CheckTilePosition(pointH);
    //Returning for each case
    if (CheckTileType(tilePointF) == 1 ||
    CheckTileType(tilePointG) == 1 ||
    CheckTileType(tilePointH) == 1 ||
    pointG.x >= GetScreenWidth() - tileSize) return true;
    else return false;
}

//Function for detecting collision with tiles in the left step of entities
bool Tilemap::CheckCollisionLeftStep(Vector2 entityPosition, Vector2 entitySize) {
    //PointI
    Vector2 pointI = {entityPosition.x - 1, entityPosition.y + entitySize.y + 1};
    //Precalculating
    Vector2 tilePointI = CheckTilePosition(pointI);
    //Returning on each case
    if (CheckTileType(tilePointI) != 0 ||
    pointI.x <= tileSize) return true;
    else return false;
}

//Function for detecting collision with tiles in the right step of entities
bool Tilemap::CheckCollisionRightStep(Vector2 entityPosition, Vector2 entitySize) {
    //PointJ
    Vector2 pointJ = {entityPosition.x + entitySize.x + 1, entityPosition.y + entitySize.y + 1};
    //Precalculating
    Vector2 tilePointJ = CheckTilePosition(pointJ);
    //Returning on each case
    if (CheckTileType(tilePointJ) != 0 ||
    pointJ.x <= tileSize) return true;
    else return false;
}

//Function to detect tile limits with different entity directions
bool Tilemap::CheckCollisionCustom(Vector2 entityPosition, Vector2 collisionDirection) {
    //PointJ
    Vector2 pointJ = {entityPosition.x + collisionDirection.x, entityPosition.y + collisionDirection.y};
    //Precalculating
    Vector2 tilePointJ = CheckTilePosition(pointJ);
    //Returning on each case
    if (CheckTileType(tilePointJ) == 1 ||
    (pointJ.x < tileSize && collisionDirection.x < 0) ||
    (pointJ.x > GetScreenWidth() - tileSize && collisionDirection.x > 0)) return true;
    else return false;
}
