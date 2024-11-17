//Libraries
#pragma once
#include "raylib.h"
#include <vector>
#include "Sprite.h"

/*-----------------------------------Main class-----------------------------------------*/
class Cursor : public Sprite {
    //Attributes
    public:
        //Variables for environment references
        const float& scale;
        const int& ammo;
        //Variables for graphic rendering
        std::vector<Texture2D> textures;
        int state = 0;
        
    private:

    //Methods
    public:
        //Class constructor to create an instance
        Cursor(Texture2D, Vector2, Vector2, std::vector<Texture2D>, float&, int&);
        //Method for process all logic
        void Update() override;
        //Method for process all graphics
        void Draw() const override;

    private:

};