//
// Created by Khalil B on 2020-12-15.
//

#ifndef J03_H2_TP_KHALIL_BELLIL_BULLETMANAGER_H
#define J03_H2_TP_KHALIL_BELLIL_BULLETMANAGER_H
#include "..\utils\IncludeHeader.h"
#include "../entities/Enemy.h"
#include "../entities/Bullet.h"
#include "CollisionManager.h"
#include <vector>
#include "EnemyManager.h"
using namespace std;

class BulletManager {

    static float m_size;
    static int enemiesKilled;
    static int enemiesToKill;
public:
    static vector<Bullet*> m_vecBullet;
    ~BulletManager();
    static void update();
    static void draw();
    static int checkCollision(vector<Enemy*> _m_vecBullet);
    static void add(float _xPos, float _yPos, float _zPos, float _xDir, float _yDir, float _zDir, float _angle);
};


#endif //J03_H2_TP_KHALIL_BELLIL_BULLETMANAGER_H
