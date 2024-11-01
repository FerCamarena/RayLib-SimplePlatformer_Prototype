//Libraries
#include "Bullet.h"
#include "raymath.h"

//Class constructor to create an instance
Bullet::Bullet(Texture2D _texture, Vector2 _position, Vector2 _direction, float _speed, bool _enabled) {
    //Storing received values as attributes
    texture = _texture;
    position = _position;
    direction = _direction;
    speed = _speed;
    enabled = _enabled;

    //Calling a starter function
    this->Initialize();
}

//Method called once for initialize default values
void Bullet::Initialize() {
    //Setting up default area pivot
    this->areaPivot = {
        this->position.x - (texture.width / 2),
        this->position.y - (this->texture.height / 2)
    };
}

//Method for process all graphics
void Bullet::Update() {
    //Check if enabled
    if (this->enabled) {
        //Check if already has a size
        if (this->size.x == 0.0f && this->size.y == 0.0f) {
            //Scaling area to max texture size
            Rectangle fullSize = {0.0f, 0.0f, (float)this->texture.width, (float)this->texture.height};
            this->size = fullSize;
        //Keep a null area size
        } else this->size = {0.0f, 0.0f, 0.0f, 0.0f};
        //Moving through a scaled direction
        Vector2 scaledDirection = Vector2Scale(this->direction, this->speed);
        this->position = Vector2Add(this->position, scaledDirection);
    }
}

//Method for process all logic
void Bullet::Draw() const {
    DrawTexture(texture, position.x, position.y, YELLOW);
}