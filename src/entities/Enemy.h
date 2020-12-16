//
// Created by gdemers on 12/7/2020.
//

#ifndef J03_SU_H20_GROUPTP_ENEMY_H
#define J03_SU_H20_GROUPTP_ENEMY_H
#pragma once

#include "../utils/IncludeHeader.h"
#include "Unit.h"

enum class EnemyType {
    Monster, Boss, Soldier
};
// Attack Animation only has 3 sprites while all the other animations have 5 sprites
enum class EnemyAnimationType{
    Back, Forward, Left, Left_Back, Right, Right_Back, Side_Left, Side_Right, Death, Attack
};

class Enemy : virtual public Unit {
    const int nbTexture = 5;
    const int nbTextureAttack = 3;
    const std::string path_soldierT = "assets/textures/enemies/soldier/";
public:
    Enemy(EnemyType enemyType, int posX, int posZ);

    ~Enemy();

    void handleTexture(EnemyAnimationType enemyAnimationType);
};

#endif //J03_SU_H20_GROUPTP_ENEMY_H
