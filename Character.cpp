//Libraries
#include "Character.h"
#include "raymath.h"

//Class constructor to create an instance
Character::Character(Texture2D _texture, Vector2 _position, Vector2 _size, Tilemap& _level) : Entity(_texture, _position, _size, _level) {}

//Method for process all graphics
void Character::Update() {
    //Updating from inherited class
    Entity::Update();

    //Creating custom character sprite
    this->sprite = {(float)(this->animationState * this->textureSize), (float)(this->frameCount * (this->textureSize)), (float)(this->textureSize * (this->onward ? 1 : -1)), (float)this->textureSize};
    
    //Collisions under the character
    bool floorCollision = this->level.CheckCollisionDown(this->position, this->size);
    Vector2 pointUnder = {this->position.x, this->position.y + 1};
    Vector2 tileUnder = this->level.CheckTilePosition(pointUnder);
    
    //Collisions over the character
    bool roofCollision = this->level.CheckCollisionOver(this->position, this->size);
    Vector2 pointOver = {this->position.x, this->position.y + 1};
    
    //Collisions on the left of the character
    bool leftCollision = this->level.CheckCollisionLeft(this->position, this->size);
    Vector2 pointLeft = {this->position.x - (size.x / 2), this->position.y - 1};
    
    //Collisions on the right of the character
    bool rightCollision = this->level.CheckCollisionRight(this->position, this->size);
    Vector2 pointRight = {this->position.x + (size.x / 2), this->position.y - 1};
    
    //Gravity
    this->acceleration.y += 1;

    //Falling
    if (floorCollision && this->velocity.y >= 0) {
        //Edge hopping condition
        if (this->level.CheckTileType(tileUnder) == 1 ||
        (int)(this->position.y + 1) % this->level.tileSize < 24) {
            //Fixing position to tile position
            this->position.y = (tileUnder.y * this->level.tileSize) - 1;
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
    
    //Setting default animation
    if (this->velocity.y == 0 && floorCollision) {
        //Restarting animation
        this->frameLimit = 1;
        this->animationState = 0;
    } else if (this->velocity.y < 0 && !floorCollision) {
        //Restarting animation
        this->animationState = 2;
        this->frameCount = 2;
        this->frameLimit = 2;
    }

    //Forcing movement only when not this->sliding
    if (!this->sliding) {
        //Jumping
        if (IsKeyDown(KEY_W) && this->velocity.y == 0 && !roofCollision &&
        ((floorCollision && (int)(this->position.y + 1) % this->textureSize < 4)/* ||
        this->position.y + this->size.y >= screenHeight*/)) {
            //Adding jump force
            this->acceleration.y -= 20;
            this->animationState = 2;
            this->frameLimit = 2;
            this->frameCount = 0;
            this->animationRate = 0;
        }
        
        //Lateral movement
        if (IsKeyDown(KEY_A) ||
        IsKeyDown(KEY_D)) {
            //Changing direction
            if (IsKeyDown(KEY_A)) this->onward = false;
            if (IsKeyDown(KEY_D)) this->onward = true;

            //Moving only if there's no collision
            if ((!leftCollision && IsKeyDown(KEY_A)) ||
            (!rightCollision && IsKeyDown(KEY_D))) {
                //Moving with forces
                this->acceleration.x += this->onward ? 1.5f : -1.5f;
                //Setting animation
                this->animationState = this->velocity.y == 0 && floorCollision ? 1 : 2;
                this->frameLimit = 3;
            }
        }
    }

    //Limiting movement within screen && applying lateral collisions
    if (this->position.y < 0) {
        //Limiting going over screen
        this->position.y = 0;
        this->velocity.y = 0;
    } //HERE SHOULD ADD GAME OVER
    if (leftCollision && this->velocity.x < 0) {
        //Fixing position due to fast collision
        this->position.x = pointLeft.x + (size.x / 2) + 1;
        //Resetting forces when colliding
        this->velocity.x = this->sliding ? -this->velocity.x : 0;
        //this->acceleration.x = this->sliding ? this->acceleration.x * 0.8f : 0;
        if (this->sliding) this->onward = !this->onward;
    } else if (this->velocity.x > 0 && rightCollision) {
        //Fixing position due to fast collision
        this->position.x = pointRight.x - (size.x / 2) - 1;
        //Resetting forces when colliding
        this->velocity.x = this->sliding ? -this->velocity.x : 0;
        //this->acceleration.x = this->sliding ? this->acceleration.x * 0.8f : 0;
        if (this->sliding) this->onward = !this->onward;
    }

    //Slide
    if (IsKeyDown(KEY_S) && floorCollision) {
        //Detecting when key is just pressed
        if (IsKeyPressed(KEY_S)) {
            //Moving the character once
            this->position.y = this->position.y + 10;
        }
        //Decreasing character size
        this->size.y = 42;
        //Applying state
        this->sliding = true;
        this->animationState = 5;
        this->frameLimit = 1;
        this->frameCount = 1;
    } else if (floorCollision) {
        //Detecting when key is just released
        if (IsKeyReleased(KEY_S)) {
            //Moving the character once
            this->position.y = this->position.y - 10;
        }
        //Applying state
        this->sliding = false;
        //Increasing character size
        this->size.y = 52;
    }
    //Updating character center point
    this->half.y = this->size.y / 2;
    
    //Checking collisions for roof and solid platoforms
    if (roofCollision && this->velocity.y < 0) {
        //Fixing position to tile position
        this->position.y = pointOver.y + 1;
        //Reseting forces
        this->velocity.y = 0;
        this->acceleration.y = 0;
    }

    //Clamping forces
    if (this->velocity.y > 32) this->velocity.y = 32;
    else if (this->velocity.y < -32) this->velocity.y = -32;

    //Calculating physics
    this->velocity.x *= this->sliding ? 0.95f : 0.8f;
    this->velocity.y += this->acceleration.y;
    this->velocity.x += this->acceleration.x;
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;

    //Clamping forces
    if (this->velocity.y > 32) this->velocity.y = 32;
    else if (this->velocity.y < -32) this->velocity.y = -32;

    //Resetting acceleration
    this->acceleration.x = 0;
    this->acceleration.y = 0;
    
    //Animating character
    this->animationRate++;
    if (this->animationRate > (60 / (this->frameLimit * this->frameLimit)) && !this->sliding) { //Temp (if added animation struct/class can define its animation speed)
        //Updating frames
        this->frameCount++;
        if (this->animationState == 2) this->frameCount = 2;
        this->animationRate = 0;
    }
    if (this->frameCount > this->frameLimit) this->frameCount = 0;
}