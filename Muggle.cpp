//Libraries
#include "Muggle.h"
#include "raymath.h"

//Class constructor to create an instance
Muggle::Muggle(Texture2D _texture, Vector2 _position, Vector2 _direction, Tilemap& _level) : level(_level) {
    //Storing received values as attributes
    this->texture = _texture;
    this->position = _position;
    this->direction = _direction;

    //Calling a starter function
    this->Initialize();
}

//Method called once for initialize default values
void Muggle::Initialize() {

}

//Method for process all graphics
void Muggle::Update() {
    //Collisions under the enemy
    bool floorCollision = this->level.CheckCollisionDown(this->position, this->size);
    Vector2 pointUnder = {this->position.x, this->position.y + this->size.y + 1};
    Vector2 tileUnder = this->level.CheckTilePosition(pointUnder);
    
    //Checking direction collisions
    bool leftCollision = this->level.CheckCollisionLeft(this->position, this->size);
    bool rightCollision = this->level.CheckCollisionRight(this->position, this->size);
    bool leftStep = this->level.CheckCollisionLeftStep(this->position, this->size);
    bool rightStep = this->level.CheckCollisionRightStep(this->position, this->size);
    
    //Defining area pivot
    this->areaPivot = {
        this->position.x - 16,
        this->position.y - 12};

    //Defining sprite area
    this->area = {0.0f, 0.0f, (float)(64 * (this->onward ? 1 : -1)), 64.0f};

    //Clamping forces
    if (this->velocity.y > 32) this->velocity.y = 32;
    else if (this->velocity.y < -32) this->velocity.y = -32;

    //Falling
    if (floorCollision && this->velocity.y >= 0) {
        //Edge hopping condition
        if (this->level.CheckTileType(tileUnder) == 1 ||
        (int)(this->position.y + this->size.y) % 64 < 24) {
            //Fixing position to tile position
            this->position.y = (tileUnder.y * 64) - this->size.y;
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
    this->velocity.x *= 0.8f;
    this->velocity.y += this->acceleration.y;
    this->velocity.x += this->acceleration.x;
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;

    //Resetting acceleration
    this->acceleration.x = 0;
    this->acceleration.y = 0;
}

//Method for process all graphics
void Muggle::Draw() const {
    //Drawing sprite
    DrawTextureRec(this->texture, this->area, this->areaPivot, RED);
}