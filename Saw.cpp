//Libraries
#include "Saw.h"
#include "raymath.h"

//Class constructor to create an instance
Saw::Saw(Texture2D _texture, Vector2 _position, Vector2 _direction, Tilemap& _level) : level(_level) {
    //Storing received values as attributes
    this->texture = _texture;
    this->position = _position;
    this->direction = _direction;

    //Calling a starter function
    this->Initialize();
}

//Method called once for initialize default values
void Saw::Initialize() {

}

//Method for process all graphics
void Saw::Update() {
    //Collisions under the enemy
    bool floorCollision = this->level.CheckCollisionDown(this->position, {0, 0});
    Vector2 pointUnder = {this->position.x, this->position.y + 1};
    Vector2 tileUnder = this->level.CheckTilePosition(pointUnder);

    //Checking direction collisions
    bool UpperRight = this->level.CheckCollisionCustom(this->position, {1, -1}); // upper right
    bool LowerRight = this->level.CheckCollisionCustom(this->position, {1, 1}); // lower right
    bool UpperLeft = this->level.CheckCollisionCustom(this->position, {-1, -1}); // upper left
    bool LowerLeft = this->level.CheckCollisionCustom(this->position, {-1, 1}); // lower left

    //Defining area pivot
    this->areaPivot = {
        this->position.x - 32,
        this->position.y - 32
    };

    //Defining sprite area
    area = {(float)13*64, 0.0f, (float)64, (float)64};
    
    //Clamping forces
    if (this->velocity.y > 32) this->velocity.y = 32;
    else if (this->velocity.y < -32) this->velocity.y = -32;
            
    //Base behaviour
    if (this->stuck) {
        //Changing directions
        if ((UpperLeft && LowerLeft) || (!LowerRight && !LowerLeft && UpperLeft && !UpperRight)) {
            //move up
            this->direction = {0, -1};
        } else if ((LowerLeft && LowerRight) || (!LowerRight && LowerLeft && !UpperLeft && !UpperRight)) {
            //move left
            this->direction = {-1, 0};
        } else if ((UpperRight && LowerRight) || (LowerRight && !LowerLeft && !UpperLeft && !UpperRight)) {
            //move down
            this->direction = {0, 1};
        } else if ((UpperLeft && UpperRight) || (!LowerRight && !LowerLeft && !UpperLeft && UpperRight)) {
            //move right
            this->direction = {1, 0};
        } else {
            this->velocity = {0, 0};
            this->direction = {0, 0};
            this->stuck = false;
        }
        this->position.x += this->direction.x;
        this->position.y += this->direction.y;
    } else {
        //Gravity
        this->acceleration.y += 1;
        //Falling
        if (floorCollision && this->velocity.y >= 0) {
            //Edge hopping condition
            if (this->level.CheckTileType(tileUnder) != 0 ||
            (int)(this->position.y) % this->level.tileSize < 24) {
                //Sleeping gravity after falling
                this->stuck = true;
                //Fixing position to tile position
                this->position.y = (tileUnder.y * this->level.tileSize);
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
    }

    //Calculating physics
    this->velocity = Vector2Add(this->velocity, this->acceleration);
    this->position = Vector2Add(this->position, this->velocity);
    this->velocity.x *= 0.8f;

    //Resetting acceleration
    this->acceleration = {0, 0};
}

//Method for process all graphics
void Saw::Draw() const {
    //Drawing sprite
    DrawTextureRec(texture, area, areaPivot, RED);
}