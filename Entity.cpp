//Libraries
#include "Entity.h"
#include "raymath.h"

//Class constructor to create an instance
Entity::Entity(Texture2D _texture, Vector2 _position, Vector2 _size, Tilemap& _level) : Sprite(_texture, _position, _size), level(_level) {}

//Method for process all logic
void Entity::Update() {
    UpdateDisplay();
}

void Entity::Draw() const {
    //Drawing sprite
    DrawTextureRec(this->texture, this->sprite, Vector2Subtract(this->position, this->pivot), WHITE);
    //Drawing hitbox
    //DrawRectangle(this->hitbox.x, this->hitbox.y, this->hitbox.width, this->hitbox.height, RED);
}

//Method for process display changes
void Entity::UpdateDisplay() {
    //Updating entity hitbox
    this->hitbox = {
        this->position.x - (this->size.x / 2), this->position.y - this->size.y,
        (float)this->size.x, (float)this->size.y
    };
    //Updating entity sprite
    this->sprite = {
        0.0f, 0.0f,
        (float)this->textureSize, (float)this->textureSize
    };
    //Updating entity area
    this->area = {
        this->position.x, this->position.y,
        (float)this->textureSize, (float)this->textureSize
    };
}