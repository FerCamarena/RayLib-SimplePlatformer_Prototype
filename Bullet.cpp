//Libraries
#include "Bullet.h"
#include "raymath.h"

//Class constructor to create an instance
Bullet::Bullet(Texture2D _texture, Vector2 _position, Vector2 _direction, float _speed, bool _enabled):
    texture(_texture), position(_position), direction(_direction), speed(_speed), enabled(_enabled) {}

//Method for process all graphics
void Bullet::Update() {
    //Check if enabled
    if (this->enabled) {
        //Check if has a size
        if (this->size.x == 0.0f && this->size.y == 0.0f) {
            //Scaling to max texture size
            Vector2 fullSize = {this->texture.width, this->texture.height};
            this->size = fullSize;
        //Keep a null size
        } else this->size = {0.0f, 0.0f};
        //Moving through a scaled direction
        Vector2 scaledDirection = Vector2Scale(this->direction, this->speed);
        this->position = Vector2Add(this->position, scaledDirection);
    }
}

//Method for process all logic
void Bullet::Draw() {
    DrawTexture(texture, position.x, position.y, WHITE);
}