//Libraries
#include "Tilemap.h"

//Class constructors to create an instance (with overloads)
Tilemap::Tilemap(Texture2D _texture, Rectangle _tiles[15], int _tileSize) {
    //Storing received values as attributes
    this->texture = _texture;
    this->tiles[15] = _tiles[15];
    this->tileSize = _tileSize;
};
Tilemap::Tilemap(Texture2D _texture, Rectangle _tiles[15]) {
    //Storing received values as attributes
    this->texture = _texture;
    this->tiles[15] = _tiles[15];
};
Tilemap::Tilemap(Texture2D _texture, int _tileSize) {
    //Storing received values as attributes
    this->texture = _texture;
    this->tileSize = _tileSize;
};
Tilemap::Tilemap(Texture2D _texture) {
    //Storing received values as attributes
    this->texture = _texture;
};


//Method for process all logic
void Tilemap::Update() {

}

//Method for process all logic
void Tilemap::DrawBackground() const {
    //Drawing bg1 tilemap
    for (int y = 0; y < (int)this->background.size(); y++) {
        for (int x = 0; x < (int)this->background[y].size(); x++) {
            Vector2 tilePosition = {
                ((float)x * this->tileSize) - (this->parallaxOffset.x * 2) + (this->tileSize * 0.5f),
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
                ((float)x * this->tileSize) - (this->parallaxOffset.x * 8) + (this->tileSize * 2),
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
Vector2 Tilemap::CheckTilePosition(Vector2 checkPosition) const {
    //Calculating position
    Vector2 tilePosition = {(float)((int)(checkPosition.x / this->tileSize)), (float)((int)(checkPosition.y / this->tileSize))};
    //Returning position
    return tilePosition;
}

//Method for checking tile type in tile position
int Tilemap::CheckTileType(Vector2 tilePosition) const {
    //Calculating tile position
    int posX = tilePosition.x;
    int posY = tilePosition.y;
    //Returning the type of the collision tilemap tile
    return this->hitbox[posY][posX];
}

//Looking for collisions under the entities
bool Tilemap::CheckCollisionDown(Vector2 entityPosition, Vector2 entitySize) const {
    //PointA
    Vector2 pointA = {entityPosition.x - (entitySize.x / 2), entityPosition.y + 1};
    //PointB
    Vector2 pointB = {entityPosition.x + (entitySize.x / 2), entityPosition.y + 1};
    //Precalculating
    Vector2 tilePointA = CheckTilePosition(pointA);
    Vector2 tilePointB = CheckTilePosition(pointB);
    //Checking types on points
    if (CheckTileType(tilePointA) > 0 ||
    CheckTileType(tilePointB) > 0) return true;
    else return false;
}

//Looking for collisions over the entities
bool Tilemap::CheckCollisionOver(Vector2 entityPosition, Vector2 entitySize) const {
    //PointC
    Vector2 pointC = {entityPosition.x - (entitySize.x / 2), entityPosition.y - entitySize.y - 1};
    //PointD
    Vector2 pointD = {entityPosition.x + (entitySize.x / 2), entityPosition.y - entitySize.y - 1};
    //Precalculating
    Vector2 tilePointC = CheckTilePosition(pointC);
    Vector2 tilePointD = CheckTilePosition(pointD);
    //Checking types on points
    if (CheckTileType(tilePointC) == 1 ||
    CheckTileType(tilePointD) == 1) return true;
    else return false;
}

//Function for detecting when colliding with a tile with collision in the left side of entities
bool Tilemap::CheckCollisionLeft(Vector2 entityPosition, Vector2 entitySize) const {
    //PointE
    Vector2 pointE = {entityPosition.x - 1, entityPosition.y - 1};
    //PointF
    Vector2 pointF = {entityPosition.x - 1, entityPosition.y - (entitySize.y * 0.5f)};
    //PointG
    Vector2 pointG = {entityPosition.x - 1, entityPosition.y - entitySize.y};
    //Precalculating
    Vector2 tilePointE = CheckTilePosition(pointE);
    Vector2 tilePointF = CheckTilePosition(pointF);
    Vector2 tilePointG = CheckTilePosition(pointG);
    //Returning on each case
    if (CheckTileType(tilePointE) == 1 ||
    CheckTileType(tilePointF) == 1 ||
    CheckTileType(tilePointG) == 1 ||
    pointE.x <= this->tileSize ||
    pointF.x <= this->tileSize ||
    pointG.x <= this->tileSize) return true;
    else return false;
}

//Function for detecting when colliding with a tile with collision in the right side of entities
bool Tilemap::CheckCollisionRight(Vector2 entityPosition, Vector2 entitySize) const {
    //PointH
    Vector2 pointH = {entityPosition.x + entitySize.x, entityPosition.y - 1};
    //PointI
    Vector2 pointI = {entityPosition.x + entitySize.x, entityPosition.y - (entitySize.y * 0.5f)};
    //PointJ
    Vector2 pointJ = {entityPosition.x + entitySize.x, entityPosition.y - entitySize.y};
    //Precalculating
    Vector2 tilePointH = CheckTilePosition(pointH);
    Vector2 tilePointI = CheckTilePosition(pointI);
    Vector2 tilePointJ = CheckTilePosition(pointJ);
    //Returning for each case
    if (CheckTileType(tilePointH) == 1 ||
    CheckTileType(tilePointI) == 1 ||
    CheckTileType(tilePointJ) == 1 ||
    pointH.x >= GetScreenWidth() - this->tileSize ||
    pointI.x >= GetScreenWidth() - this->tileSize ||
    pointJ.x >= GetScreenWidth() - this->tileSize) return true;
    else return false;
}

//Function for detecting collision with tiles in the left step of entities
bool Tilemap::CheckCollisionLeftStep(Vector2 entityPosition, Vector2 entitySize) const {
    //PointK
    Vector2 pointK = {entityPosition.x - (entitySize.x / 2) - 1, entityPosition.y + 1};
    //Precalculating
    Vector2 tilePointK = CheckTilePosition(pointK);
    //Returning on each case
    if (CheckTileType(tilePointK) != 0 ||
    pointK.x <= this->tileSize) return true;
    else return false;
}

//Function for detecting collision with tiles in the right step of entities
bool Tilemap::CheckCollisionRightStep(Vector2 entityPosition, Vector2 entitySize) const {
    //PointL
    Vector2 pointL = {entityPosition.x + (entitySize.x / 2) + 1, entityPosition.y + 1};
    //Precalculating
    Vector2 tilePointL = CheckTilePosition(pointL);
    //Returning on each case
    if (CheckTileType(tilePointL) != 0 ||
    pointL.x >= GetScreenWidth() - this->tileSize) return true;
    else return false;
}

//Function to detect tile collision with custom directions
bool Tilemap::CheckCollisionCustom(Vector2 entityPosition, Vector2 collisionDirection) const {
    //PointM
    Vector2 pointM = {entityPosition.x + collisionDirection.x, entityPosition.y + collisionDirection.y};
    //Precalculating
    Vector2 tilePointM = CheckTilePosition(pointM);
    //Returning on each case
    if (CheckTileType(tilePointM) == 1 ||
    (pointM.x < this->tileSize && collisionDirection.x < 0) ||
    (pointM.x > GetScreenWidth() - this->tileSize && collisionDirection.x > 0)) return true;
    else return false;
}

//Function to detect tile collision in exact points
bool Tilemap::CheckCollisionPoint(Vector2 pointPosition) const {
    //PointN
    Vector2 pointN = pointPosition;
    if ((pointN.y < 0.0f) || (pointN.y > GetScreenHeight()) ||
        (pointN.x < this->tileSize) || (pointN.x > GetScreenWidth())) return true;
    //Precalculating
    Vector2 tilePointN = CheckTilePosition(pointN);
    //Returning on each case
    if (CheckTileType(tilePointN) > 0) return true;
    else return false;
}