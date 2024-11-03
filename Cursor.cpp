//Libraries
#include "Cursor.h"
#include "raymath.h"

//Class constructor to create an instance
Cursor::Cursor(std::vector<Texture2D> _textures, float& _scale, int& _ammo) : scale(_scale), ammo(_ammo) {
    //Storing received values as attributes
    this->textures = _textures;

    //Calling a starter function
    this->Initialize();
}

//Method called once for initialize default values
void Cursor::Initialize() {

}

//Method for process all graphics
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
    this->areaPivot = {
        (this->textures[0].width * 0.5f),
        (this->textures[0].height * 0.5f)
    };

    //Selecting cursor texture
    this->state = this->ammo > 0;
}

//Method for process all graphics
void Cursor::Draw() const {
    //Drawing sprite
    DrawTexturePro(this->textures[this->state], this->area, this->sprite, this->areaPivot, this->rotation, BLUE);
}