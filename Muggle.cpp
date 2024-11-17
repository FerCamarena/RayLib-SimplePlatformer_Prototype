//Libraries
#include "Muggle.h"
#include "raymath.h"

//Class constructor to create an instance
Muggle::Muggle(Texture2D _texture, Vector2 _position, Vector2 _size, Tilemap& _level) : Entity(_texture, _position, _size, _level) {}
Muggle::Muggle(Vector2 _position, Vector2 _size, Tilemap& _level) : Entity(LoadTexture("./assets/Entities/spritesheet_enemy_muggle.png"), _position, _size, _level) {}

//Method for process all logic
void Muggle::Update() {
    //Updating from inherited class
    Entity::Update();
    
    //Collisions under the enemy
    bool floorCollision = this->level.CheckCollisionDown(this->position, this->size);
    Vector2 pointUnder = {this->position.x, this->position.y + 1};
    Vector2 tileUnder = this->level.CheckTilePosition(pointUnder);
    
    //Checking direction collisions
    bool leftCollision = this->level.CheckCollisionLeft(this->position, this->size);
    bool rightCollision = this->level.CheckCollisionRight(this->position, this->size);
    bool leftStep = this->level.CheckCollisionLeftStep(this->position, this->size);
    bool rightStep = this->level.CheckCollisionRightStep(this->position, this->size);

    //Clamping forces
    if (this->velocity.y > 32) this->velocity.y = 32;
    else if (this->velocity.y < -32) this->velocity.y = -32;

    //Falling
    if (floorCollision && this->velocity.y >= 0) {
        //Edge hopping condition
        if (this->level.CheckTileType(tileUnder) != 0 ||
        (int)(this->position.y) + 1 % level.tileSize < 24) {
            //Fixing position to tile position
            this->position.y = (tileUnder.y * this->textureSize) - 1;
            //Reseting forces
            this->velocity.y = 0;
            this->acceleration.y = 0;
            //Update for work within the tilemap class
            /*
            //Preventing falling from screen TEMP
            if ((this->position.y) > screenHeight) {
                this->position.y = screenHeight;
            }
            */
        }
    }
    
    //Changing directions
    if ((this->onward && this->velocity.x > 0 && (rightCollision || !rightStep)) ||
    (!this->onward && this->velocity.x < 0 && (leftCollision || !leftStep))) {
        //Inverting direction
        this->onward = !this->onward;
        //Resetting baseEnemy velocity (optional)
        this->velocity.x = 0;
    }

    //Base behaviour
    this->acceleration.x = this->onward ? 0.5f : -0.5f;

    //Gravity
    this->acceleration.y += 1;

    //Calculating physics
    this->velocity.x += this->acceleration.x;
    this->velocity.y += this->acceleration.y;
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;
    this->velocity.x *= 0.8f;

    //Resetting acceleration
    this->acceleration.x = 0;
    this->acceleration.y = 0;
}