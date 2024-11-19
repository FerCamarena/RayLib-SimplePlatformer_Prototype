//Base class
#include "Sprite.h"

//Class constructor to create an instance
Sprite::Sprite(Texture2D _texture, Vector2 _position, Vector2 _size) {
    //Storing received values as attributes
    texture = _texture;
    position = _position;
    size = _size;
}

//Method for process display changes
void Sprite::UpdateDisplay() {
    //Updating entity hitbox
    this->hitbox = {
        this->position.x - (this->size.x / 2), this->position.y - this->size.y,
        (float)this->size.x, (float)this->size.y
    };
    //Updating entity texture
    this->sprite = {
        0.0f, 0.0f,
        64.0f, 64.0f
    };
    //Updating entity area
    this->area = {
        this->position.x, this->position.y,
        64.0f, 64.0f
    };
}