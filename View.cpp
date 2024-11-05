//Libraries
#include "View.h"

//Class constructors to create an instance (with overloads)
View::View(Vector2 _screenSize, Camera2D& _mainCamera, Character& _player) : mainCamera(_mainCamera), player(_player) {
    //Storing received values as attributes
    this->screenSize = _screenSize;

    //Calling a starter function
    this->Initialize();
};

//Method called once for initialize default values
void View::Initialize() {

}

//Method for process all logic
void View::Update() {
        //Calculating camera positions
        Vector2 cameraLowerFocus = {
            (mainCamera.offset.x / mainCamera.zoom) - player.half.x,
            (mainCamera.offset.y / mainCamera.zoom) - player.half.y + (player.sliding ? -5 : 0)
            };
        Vector2 cameraUpperFocus = {
            (screenSize.x - cameraLowerFocus.x),
            (screenSize.y - cameraLowerFocus.y)
        };

        //Updating camera position in X axys
        if (player.position.x + player.half.x >= cameraLowerFocus.x + player.level.tileSize &&
        player.position.x + player.half.x <= cameraUpperFocus.x - player.level.tileSize) {
            //Moving middle
            mainCamera.target.x = player.position.x + player.half.x;
        } else if (player.position.x + player.half.x < cameraLowerFocus.x + player.level.tileSize) {
            //Moving left edge
            mainCamera.target.x = cameraLowerFocus.x + player.level.tileSize;
        } else if (player.position.x + player.half.x > cameraUpperFocus.x - player.level.tileSize) {
            //Moving left edge
            mainCamera.target.x = cameraUpperFocus.x - player.level.tileSize;
        }

        //Updating camera position in Y axys
        if (player.position.y + player.half.y > cameraLowerFocus.y &&
        player.position.y + player.half.y < cameraUpperFocus.y) {
            //Moving center
            mainCamera.target.y = player.position.y + player.half.y + (player.sliding ? -5 : 0);
        } else if (player.position.y + player.half.y <= cameraLowerFocus.y) {
            //Moving top edge
            mainCamera.target.y = cameraLowerFocus.y;
        } else if (player.position.y + player.half.y >= cameraUpperFocus.y) {
            //Moving lower edge
            mainCamera.target.y = cameraUpperFocus.y;
        }
        //Updating parallax
        positionOffset.x = (int)(mainCamera.target.x / 16);
        positionOffset.y = (int)(mainCamera.target.y / 16);

        //Updating camera acceleration
        cameraAcceleration.x = player.velocity.x * player.velocity.x / 8;
        if (player.velocity.x < 0) cameraAcceleration.x *= -1; 
        cameraAcceleration.y = player.velocity.y * player.velocity.y / 64;
        if (player.velocity.y < 0) cameraAcceleration.y *= -1;

        //Reducing camera acceleration
        cameraAcceleration.x *= 0.85f;
        cameraAcceleration.y *= 0.85f;

        //Setting camera target with accelerations
        mainCamera.target.x += cameraAcceleration.x * 2;
        mainCamera.target.y += cameraAcceleration.y * 2;
}