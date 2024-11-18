//Base class
#include "Level_02.h"

//User libraries
#include "SceneManager.h"

//Class constructors to create an instance
Level_02::Level_02() {
    //Populating and configuring level
    InitializeLevel();
}

//Method for initialize level
void Level_02::InitializeLevel() {
    //Setting camera options
    mainCamera.offset = {GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f};
    mainCamera.rotation = 0.0f;
    mainCamera.zoom = 1.5f;

    //Spawning all enemies
    for (int y = 0; y < (int)level.spawns.size(); y++) {
        for (int x = 0; x < (int)level.spawns[y].size(); x++) {
            switch (level.spawns[y][x]) {
                case 0:
                    continue;
                case 1:
                    enemyList.push_back(std::make_unique<Muggle>(Muggle({(float)x * level.tileSize, (float)y * level.tileSize}, {32.0f, 32.0f}, level)));
                break;
                case 2:
                    enemyList.push_back(std::make_unique<Saw>(Saw({(float)x * level.tileSize, (float)y * level.tileSize}, {32.0f, 32.0f}, level)));
                break;
            }
        }
    }
}

//Method for process all logic
void Level_02::Update() {
    //=====LEVEL=====
    
    //Checking for inputs to start a new game
    if (IsKeyPressed(KEY_ENTER)) {
        SceneManager::ChangeScene(0);
    } else if (IsKeyPressed(KEY_N)) { //Temp
        SceneManager::ChangeScene(2);
    }

    //Detecting ENEMY-PLAYER collisions
    for (auto enemy = enemyList.begin(); enemy != enemyList.end(); ) {
        //Checking collision with individual enemies
        if (CheckCollisionRecs(player.hitbox, (*enemy)->hitbox)) {
            //Change to game over scene
            SceneManager::ChangeScene(1);
            break;
        //Continue checking
        } else ++enemy;
    }
    //Detecting ENEMY-BULLET collisions
    for (auto enemy = enemyList.begin(); enemy != enemyList.end(); ) {
        //Value to manage better the list iteration
        bool enemyRemoved = false;

        //Iterating for each bullet
        for (auto bullet = bulletsList.begin(); bullet != bulletsList.end();) {
            //Checking collision with individual enemies
            if (!(*bullet)->enabled) {
                //Moving disabled item too pool
                bulletsPool.push_back(std::move(*bullet));
                bullet = bulletsList.erase(bullet);
                continue;
            }
            if (CheckCollisionRecs((*enemy)->hitbox, (*bullet)->hitbox)) {
                //Removing both
                (*bullet)->enabled = false;
                enemy = enemyList.erase(enemy);
                //Marking as collided
                enemyRemoved = true;
                break;
                //Possible ammo reload
                //ammoLeft++;
            }
            ++bullet;
        }
        //Continuing when not colliding
        if (!enemyRemoved) ++enemy;
    }

    //Updating tilemap values
    level.parallaxOffset = view.positionOffset;
    level.Update();

    //Detecting click to create a bullet when has ammo
    if (ammoLeft > 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        //Decreasing ammo
        ammoLeft--;
        //Storing position
        Vector2 newBulletPosition = (Vector2){
            player.position.x - 8,
            player.position.y - player.half.y - 8
        };
        //Storing direction
        Vector2 newBulletVector = Vector2Subtract(GetScreenToWorld2D(GetMousePosition(), mainCamera), newBulletPosition);
        Vector2 newBulletDirection = Vector2Normalize(newBulletVector);

        //Saving a reference with smartpointer
        std::unique_ptr<Bullet> newBullet;
        
        //Checking for object pool
        if (!bulletsPool.empty()) {
            //Moving from object pool
            newBullet = std::move(bulletsPool.back());
            bulletsPool.pop_back();
        } else {
            //Instanciating new bullet
            newBullet = std::make_unique<Bullet>(Bullet(newBulletPosition, {12, 12}, 10.0f, level));
        }
        //Setting values to bullet
        newBullet->SetLaunch(newBulletPosition, newBulletDirection);

        //Storing new bullet
        bulletsList.push_back(std::move(newBullet));
    }

    //=====LEVEL=====

    //=====BULLETS=====

    //Updating each bullet spawned
    for (auto& bullet : bulletsList) {
        //Make each bullet update itself
        bullet->Update();
    }

    //=====CHARACTER=====

    //Updating character
    player.Update();

    //=====ENEMIES=====

    //Updating enemies
    for (auto& enemy : enemyList) {
        //Calling update method for each enemy
        enemy->Update();
    }

    //======VIEW======

    view.Update();

    //=====CURSOR=====
    
    cursor.Update();
}

//Method for process all graphics
void Level_02::Draw() const {
    //Drawing level
    level.DrawBackground();
    BeginMode2D(mainCamera);
        //#Displaying the full levelTilesheet 
        //#DrawTexture(levelTilesheet, 0, 0, WHITE);
        //Drawing base tilemap
        level.Draw();
        //Drawing character
        player.Draw();
        //Drawing enemies
        for (const auto& enemy : enemyList) {
            //Calling draw method for each enemy
            enemy->Draw();
        }
        //Drawing bullets
        for (const auto& bullet : bulletsList) {
            //Calling draw method for each bullet
            bullet->Draw();
        }
        //DEBUG
    EndMode2D();
    //DEBUG
    //Drawing cursor
    cursor.Draw();
}