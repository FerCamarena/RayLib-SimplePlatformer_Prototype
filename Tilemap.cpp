//Libraries
#include "Tilemap.h"

//Class constructor to create an instance
Tilemap::Tilemap(Texture2D _texture, int _id) {
    //Storing received values as attributes
    texture = _texture;
    id = _id;
    
    //Storing JSON level info
    std::ifstream archivo(TextFormat("./assets/Level_%02d.json", id));
    if (archivo.is_open()) {
        json JSON;
        archivo >> JSON;
        
        //Obtaning cell info
        if (JSON.contains("tileSize")) tileSize = JSON.at("tileSize").get<int>();

        //Obtaining tilemap dimmensions
        if (JSON.contains("width")) width = JSON.at("width").get<int>();
        if (JSON.contains("height")) height = JSON.at("height").get<int>();
        
        //Obtaining tileset
        if (JSON.contains("tileset")) { //TEMP Must control vectors
            const auto& levelTileset = JSON.at("tileset");
            int index = 0;
            //Assigning each value respectivelly
            for (const auto& tileData : levelTileset) {
                //TEMP Checking for only adding 2 coords
                if (tileData.size() == 2) {
                    tileset[index++] = Rectangle{
                        (float)tileData[0] * tileSize,
                        (float)tileData[1] * tileSize,
                        (float)tileSize,
                        (float)tileSize,
                    };
                }
                if (index >= 15) break; //TEMP Array safety
            }
        }

        //Obtaining diferent tilemaps
        if (JSON.contains("background")) background = JSON.at("background").get<std::vector<std::vector<int>>>(); //TEMP Must control 1D vectors
        if (JSON.contains("horizon")) horizon = JSON.at("horizon").get<std::vector<std::vector<int>>>(); //TEMP Must control 1D vectors
        if (JSON.contains("drawn")) drawn = JSON.at("drawn").get<std::vector<std::vector<int>>>(); //TEMP Must control 1D vectors
        if (JSON.contains("hitbox")) hitbox = JSON.at("hitbox").get<std::vector<std::vector<int>>>(); //TEMP Must control 1D vectors
        if (JSON.contains("spawns")) spawns = JSON.at("spawns").get<std::vector<std::vector<int>>>(); //TEMP Must control 1D vectors
    }
};

//Method for process all logic
void Tilemap::Update() {

}

//Method for process all logic
void Tilemap::DrawBackground() const {
    //Drawing bg1 tilemap
    for (int y = 0; y < (int)this->background.size(); y++) {
        for (int x = 0; x < (int)this->background[y].size(); x++) {
            //Getting the correct tile
            int tileIndex = background[y][x];
            //Skipping blank tiles
            if (tileIndex == 0) continue; 
            Vector2 tilePosition = {
                ((float)x * this->tileSize) - (this->parallaxOffset.x * 2) + (this->tileSize * 0.5f),
                ((float)y * this->tileSize) - (this->parallaxOffset.y * 2)
            };
            //Drawing single tile
            DrawTextureRec(this->texture, this->tileset[tileIndex], tilePosition, BLACK);
        }
    }
    //Drawing bg2 tilemap
    for (int y = 0; y < (int)this->horizon.size(); y++) {
        for (int x = 0; x < (int)this->horizon[y].size(); x++) {
            //Getting the correct tile
            int tileIndex = horizon[y][x];
            //Skipping blank tiles
            if (tileIndex == 0) continue; 
            //Calculating each tile position
            Vector2 tilePosition = {
                ((float)x * this->tileSize) - (this->parallaxOffset.x * 8) + (this->tileSize * 2),
                ((float)y * this->tileSize) - (this->parallaxOffset.y * 8)
            };
            //Drawing single tile
            DrawTextureRec(this->texture, this->tileset[tileIndex], tilePosition, GRAY);
        }
    }
}

//Method for process all logic
void Tilemap::Draw() const {
    //Drawing base tilemap
    for (int y = 0; y < (int)this->drawn.size(); y++) {
        for (int x = 0; x < (int)this->drawn[y].size(); x++) {
            //Getting the correct tile
            int tileIndex = drawn[y][x];
            //Skipping blank tiles
            if (tileIndex == 0) continue; 
            //Calculating each tile position
            Vector2 tilePosition = {
                ((float)x * this->tileSize),
                ((float)y * this->tileSize)
            };
            //Drawing single tile
            DrawTextureRec(this->texture, this->tileset[tileIndex], tilePosition, WHITE);
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
    //Checking level limits
    if (pointA.y > GetScreenHeight() - this->tileSize ||
        pointB.y > GetScreenHeight() - this->tileSize) return true;
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
    //Checking level limits
    if (pointC.y < 0 || pointD.y < 0) return true;
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
    Vector2 pointE = {entityPosition.x - (entitySize.x + 0.5f), entityPosition.y - 1};
    //PointF
    Vector2 pointF = {entityPosition.x - (entitySize.x + 0.5f), entityPosition.y - (entitySize.y * 0.5f)};
    //PointG
    Vector2 pointG = {entityPosition.x - (entitySize.x + 0.5f), entityPosition.y - entitySize.y + 1};
    //Checking level limits
    if (pointE.x < this->tileSize ||
        pointF.x < this->tileSize ||
        pointG.x < this->tileSize) return true;
    //Precalculating
    Vector2 tilePointE = CheckTilePosition(pointE);
    Vector2 tilePointF = CheckTilePosition(pointF);
    Vector2 tilePointG = CheckTilePosition(pointG);
    //Returning on each case
    if (CheckTileType(tilePointE) == 1 ||
        CheckTileType(tilePointF) == 1 ||
        CheckTileType(tilePointG) == 1) return true;
    else return false;
}

//Function for detecting when colliding with a tile with collision in the right side of entities
bool Tilemap::CheckCollisionRight(Vector2 entityPosition, Vector2 entitySize) const {
    //PointH
    Vector2 pointH = {entityPosition.x + (entitySize.x + 0.5f), entityPosition.y - 1};
    //PointI
    Vector2 pointI = {entityPosition.x + (entitySize.x + 0.5f), entityPosition.y - (entitySize.y * 0.5f)};
    //PointJ
    Vector2 pointJ = {entityPosition.x + (entitySize.x + 0.5f), entityPosition.y - entitySize.y + 1};
    //Checking level limits
    if (pointH.x > GetScreenWidth() - this->tileSize ||
        pointI.x > GetScreenWidth() - this->tileSize ||
        pointJ.x > GetScreenWidth() - this->tileSize) return true;
    //Precalculating
    Vector2 tilePointH = CheckTilePosition(pointH);
    Vector2 tilePointI = CheckTilePosition(pointI);
    Vector2 tilePointJ = CheckTilePosition(pointJ);
    //Returning for each case
    if (CheckTileType(tilePointH) == 1 ||
        CheckTileType(tilePointI) == 1 ||
        CheckTileType(tilePointJ) == 1) return true;
    else return false;
}

//Function for detecting collision with tiles in the left step of entities
bool Tilemap::CheckCollisionLeftStep(Vector2 entityPosition, Vector2 entitySize) const {
    //PointK
    Vector2 pointK = {entityPosition.x - (entitySize.x / 2) - 1, entityPosition.y + 1};
    //Checking level limits
    if (pointK.x <= this->tileSize) return true;
    //Precalculating
    Vector2 tilePointK = CheckTilePosition(pointK);
    //Returning on each case
    if (CheckTileType(tilePointK) > 0) return true;
    else return false;
}

//Function for detecting collision with tiles in the right step of entities
bool Tilemap::CheckCollisionRightStep(Vector2 entityPosition, Vector2 entitySize) const {
    //PointL
    Vector2 pointL = {entityPosition.x + (entitySize.x / 2) + 1, entityPosition.y + 1};
    //Checking level limits
    if (pointL.x >= GetScreenWidth() - this->tileSize) return true;
    //Precalculating
    Vector2 tilePointL = CheckTilePosition(pointL);
    //Returning on each case
    if (CheckTileType(tilePointL) > 0) return true;
    else return false;
}

//Function to detect tile collision with custom directions
bool Tilemap::CheckCollisionCustom(Vector2 entityPosition, Vector2 collisionDirection) const {
    //PointM
    Vector2 pointM = {entityPosition.x + collisionDirection.x, entityPosition.y + collisionDirection.y};
    //Checking level limits
    if ((pointM.x < this->tileSize && collisionDirection.x < 0) ||
        (pointM.x > GetScreenWidth() - this->tileSize && collisionDirection.x > 0) ||
        (pointM.y < this->tileSize && collisionDirection.y < 0) ||
        (pointM.y > GetScreenHeight() - this->tileSize && collisionDirection.y > 0)) return true;
    //Precalculating
    Vector2 tilePointM = CheckTilePosition(pointM);
    //Returning on each case
    if (CheckTileType(tilePointM) == 1) return true;
    else return false;
}

//Function to detect tile collision in exact points
bool Tilemap::CheckCollisionPoint(Vector2 pointPosition) const {
    //PointN
    Vector2 pointN = pointPosition;
    if (pointN.x < this->tileSize || pointN.x > GetScreenWidth() - this->tileSize ||
        pointN.y < 0.0f || pointN.y > GetScreenHeight() - this->tileSize) return true;
    //Precalculating
    Vector2 tilePointN = CheckTilePosition(pointN);
    //Returning on each case
    if (CheckTileType(tilePointN) > 0) return true;
    else return false;
}