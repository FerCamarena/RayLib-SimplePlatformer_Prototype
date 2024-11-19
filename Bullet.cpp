//Libraries
#include "Bullet.h"
#include "raymath.h"

//Class constructors to create an instance
Bullet::Bullet(Texture2D _texture, Vector2 _position, Vector2 _size, float _speed, Tilemap& _level) : Sprite(_texture, _position, _size), level(_level) {
    //Storing received values as attributes
    speed = _speed;
}
Bullet::Bullet(Vector2 _position, Vector2 _size, float _speed, Tilemap& _level) : Sprite(LoadTexture("./assets/Other/bullet.png"), _position, _size), level(_level) {
    //Storing received values as attributes
    speed = _speed;
}

//Method for launching the bullet with custom parameters
void Bullet::SetLaunch(Vector2 _position, Vector2 _direction) {
    //Sending values to instance
    this->position = _position;
    this->direction = _direction;
    this->enabled = true;
}

//Method for process all logic
void Bullet::Update() {
    //Updating from inherited class
    UpdateDisplay();

    //Check if enabled
    if (this->enabled) {
        //Check if already has a area size
        if (this->area.width == 0 && this->area.height == 0) {
            //Scaling area to max texture size
            Rectangle fullSizeArea = {
                0.0f, 0.0f,
                (float)this->texture.width, (float)this->texture.height
            };
            this->area = fullSizeArea;
        //Keep a null area size
        } else this->area = {0.0f, 0.0f, 0.0f, 0.0f};
        //Moving through a scaled direction
        Vector2 scaledDirection = Vector2Scale(this->direction, this->speed);
        this->position = Vector2Add(this->position, scaledDirection);

        //Checking for map collisions to disable
        Vector2 collisionPoint = Vector2Add(this->position, Vector2Scale(this->size, 0.5f));
        if (this->level.CheckCollisionPoint(collisionPoint)) this->enabled = false;
    }
}

//Method for process all graphics
void Bullet::Draw() const {
    if (!this->enabled) return;
    //Drawing sprite
    DrawTextureRec(this->texture, this->sprite, Vector2Subtract(this->position, (Vector2){(float)this->texture.width / 2, (float)this->texture.height / 2}), YELLOW);
    //Drawing hitbox
    DrawCircleV(this->position, (this->hitbox.width / 2), RED);
}

//Method for updating custom display parameters
void Bullet::UpdateDisplay() {
    //Updating entity hitbox
    this->hitbox = {
        this->position.x - this->size.x / 2, this->position.y - this->size.y / 2,
        this->size.x, this->size.y
    };
    //Updating entity texture
    this->sprite = {
        0.0f, 0.0f,
        (float)this->texture.width, (float)this->texture.height
    };
}