//Libraries
#include "Entity.h"

//Class constructor to create an instance
Entity::Entity(Texture2D _texture, Vector2 _position, Vector2 _size, Tilemap& _level) : Sprite(_texture, _position, _size), level(_level) {
    //Storing received values as attributes
    this->texture = _texture;
    this->position = _position;
    this->size = _size;
}