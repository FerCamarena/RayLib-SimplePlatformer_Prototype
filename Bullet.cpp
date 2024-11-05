//Libraries
#include "Bullet.h"
#include "raymath.h"

//Class constructor to create an instance
Bullet::Bullet(Texture2D _texture, Vector2 _position, Vector2 _size, Vector2 _direction, float _speed) : Sprite(_texture, _position, _size) {
    //Storing received values as attributes
    this->speed = _speed;
    this->direction = _direction;
}

//Method for process all logic
void Bullet::Update() {
    //Defining area pivot
    this->areaPivot = {
        this->position.x - (texture.width / 2),
        this->position.y - (this->texture.height / 2)
    };
    //Check if enabled
    if (this->enabled) {
        //Check if already has a area size
        if (this->scaledArea.width == 0 && this->scaledArea.height == 0) {
            //Scaling area to max texture size
            Rectangle fullSizeArea = {
                0.0f, 0.0f,
                (float)this->texture.width, (float)this->texture.height
            };
            this->scaledArea = fullSizeArea;
        //Keep a null area size
        } else this->scaledArea = {0.0f, 0.0f, 0.0f, 0.0f};
        //Moving through a scaled direction
        Vector2 scaledDirection = Vector2Scale(this->direction, this->speed);
        this->position = Vector2Add(this->position, scaledDirection);
    }
}

//Method for process all graphics
void Bullet::Draw() const {
    //Drawing sprite
    DrawTextureRec(texture, scaledArea, areaPivot, YELLOW);
}