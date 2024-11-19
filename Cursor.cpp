//Libraries
#include "Cursor.h"
#include "raymath.h"

//Class constructor to create an instance
Cursor::Cursor(Texture2D _texture, Vector2 _position, Vector2 _size, std::vector<Texture2D> _textures, float& _scale, int& _ammo) : Sprite(_texture, _position, _size), scale(_scale), ammo(_ammo) {
    //Storing received values as attributes
    textures = _textures;

}

//Method for process all logic
void Cursor::Update() {
    //Cursor scaling calculation
    this->area = {
        0.0f, 0.0f,
        (float)this->textures[0].width, (float)this->textures[0].height
    };
    this->sprite = {
        GetMousePosition().x, GetMousePosition().y,
        this->textures[0].width * (this->scale / 2), this->textures[0].height * (this->scale / 2)
    };
    this->pivot = {
        (this->textures[0].width * (0.5f * this->scale) * 0.5f),
        (this->textures[0].height * (0.5f * this->scale) * 0.5f)
    };

    //Selecting cursor texture
    this->state = this->ammo > 0;
}

//Method for process all graphics
void Cursor::Draw() const {
    //Drawing sprite
    DrawTexturePro(this->textures[this->state], this->area, this->sprite, this->pivot, this->rotation, BLUE);
}