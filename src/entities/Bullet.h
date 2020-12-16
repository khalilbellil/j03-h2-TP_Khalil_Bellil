//
// Created by Khalil B on 2020-12-15.
//

#ifndef J03_H2_TP_KHALIL_BELLIL_BULLET_H
#define J03_H2_TP_KHALIL_BELLIL_BULLET_H
#include "SphereCollider.h"
#include <GL/gl.h>
#include <GL/glu.h>
class Bullet {
    float xStartPos;
    float yStartPos;
    float zStartPos;
    float xPos;
    float yPos;
    float zPos;
    float speed;
    float xDir;
    float yDir;
    float zDir;
    float angle;
    SphereCollider m_sphereCollider;
public:
    Bullet(float _xStartPos, float _yStartPos, float _zStartPos, float _xDir, float _yDir, float _zDir, float angle);
    ~Bullet();
    void init();
    void update();
    void render();
    void quit();
    SphereCollider& getSphereCollider();
};


#endif //J03_H2_TP_KHALIL_BELLIL_BULLET_H
