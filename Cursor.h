//Libraries
#pragma once
#include "raylib.h"
#include <vector>

/*-----------------------------------Main class-----------------------------------------*/
class Cursor {
    //Attributes
    public:
        //Variables for environment references
        const float& scale;
        const int& ammo;
        //Variables for graphic rendering
        std::vector<Texture2D> textures;
        Rectangle sprite = {0.0f, 0.0f, 64.0f, 64.0f};
        Rectangle area = {0.0f, 0.0f, 16.0f, 16.0f};
        Vector2 position = {0.0f, 0.0f};
        Vector2 areaPivot = {0.0f, 0.0f};
        float rotation = 0.0f;
        int state = 0;
        
    private:

    //Methods
    public:
        //Class constructor to create an instance
        Cursor(std::vector<Texture2D>, float&, int&);
        //Method for process all logic
        void Update();
        //Method for process all graphics
        void Draw() const;

    private:
        //Method called once for initialize default values
        void Initialize();

};