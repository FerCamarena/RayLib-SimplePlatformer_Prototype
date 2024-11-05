//Libraries
#include "Sprite.h"

//Class constructor to create an instance
Sprite::Sprite(Texture2D _texture, Vector2 _position, Vector2 _size) {
    //Storing received values as attributes
    this->texture = _texture;
    this->position = _position;
    this->size = _size;
}