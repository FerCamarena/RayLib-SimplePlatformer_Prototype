//Libraries
#include "Entity.h"

//Class constructor to create an instance
Entity::Entity(Texture2D _texture, Vector2 _position, Vector2 _size, Tilemap& _level) : Sprite(_texture, _position, _size), level(_level) {}

void Entity::Draw() const {
    //Drawing sprite
    DrawTextureRec(this->texture, this->area, this->areaPivot, RED);
}