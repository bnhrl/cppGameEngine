#pragma once
#include "../Game.h"

#include "Models.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "Bullet.h"

using namespace bnhe;

class ArcadeGame : public Game {
public:
	virtual int Run() override;

    Player* CreatePlayer(Scene* scene);

    void CreateEnemy(Scene* scene, Player* player);
    void CreateBullet(Scene* scene);
    void CreatePowerUp(Scene* scene, Player* player);

    void StartGame(Scene* scene, Player*& player);

    float points = 0.f;
    const float MAX_TIME_UNTIL_ENEMY = 5.f;
    const float MAX_TIME_UNTIL_BULLET = 5.f;
    const float MAX_TIME_UNTIL_POWER_UP = 8.f;
    float MAX_timeUntilEnemy = MAX_TIME_UNTIL_ENEMY;
    float MAX_timeUntilBullet = MAX_TIME_UNTIL_BULLET;
    float MAX_timeUntilPowerUp = MAX_TIME_UNTIL_POWER_UP;
    float timeUntilEnemy = MAX_timeUntilEnemy;
    float timeUntilBullet = MAX_timeUntilBullet;
    float timeUntilPowerUp = MAX_timeUntilPowerUp;
};