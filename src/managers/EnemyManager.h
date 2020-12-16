//
// Created by gdemers on 12/7/2020.
//

#ifndef J03_SU_H20_GROUPTP_ENEMYMANAGER_H
#define J03_SU_H20_GROUPTP_ENEMYMANAGER_H
#pragma once

#include "../utils/IncludeHeader.h"
#include "../entities/Enemy.h"
#include "MapManager.h"

class EnemyManager {
    static bool isInitialized;
    static int cpt;
    static const int maxEnemies = 30;
public:
    static std::map<int, Enemy *> s_enemies;

    static void initialize();
    static void update(Player target);
    static void clear();
    static void draw();
};

#endif //J03_SU_H20_GROUPTP_ENEMYMANAGER_H
