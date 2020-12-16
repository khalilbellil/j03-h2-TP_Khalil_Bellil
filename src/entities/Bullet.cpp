//
// Created by Khalil B on 2020-12-15.
//

#include "Bullet.h"
#include <cmath>
#define TORAD M_PI/180.0

Bullet::Bullet(float _xStartPos, float _yStartPos, float _zStartPos, float _xDir, float _yDir, float _zDir, float _angle) {
    xStartPos = _xStartPos;
    yStartPos = _yStartPos;
    zStartPos = _zStartPos;
    xPos = 0;
    yPos = 1.f;
    zPos = 0;
    speed = .1f;
    xDir = _xDir;
    yDir = _yDir;
    zDir = _zDir;
    angle = _angle;
}

Bullet::~Bullet() {
}

void Bullet::update() {
    xStartPos += sin(angle * TORAD) * speed;
    zStartPos += cos(angle * TORAD) * speed;
    m_sphereCollider = {xStartPos, yStartPos, zStartPos, 0.5};
}

void Bullet::render() {
//    glRotated(angle, 0, 1, 0);
//    glPushMatrix();
//    glTranslatef(xStartPos , yStartPos, zStartPos);
//    glBegin(GL_QUADS);
//    //face bas
//    glColor3f(104.f/255.f,104.f/255.f,114.f/255.f);
//    glVertex3f(-1, -1, -1);
//    glVertex3f(-1, -1, 1);
//    glVertex3f(1, -1, 1);
//    glVertex3f(1, -1, -1);
//    //face verte
//    glColor3f(82.f/255.f,86.f/255.f,89.f/255.f);
//    glVertex3f(-1, -1, -1);
//    glVertex3f(-1, 1, -1);
//    glVertex3f(-1, 1, 1);
//    glVertex3f(-1, -1, 1);
//    //face rouge
//    glColor3f(87.f/255.f,89.f/255.f,107.f/255.f);
//    glVertex3f(-1, -1, -1);
//    glVertex3f(1, -1, -1);
//    glVertex3f(1, 1, -1);
//    glVertex3f(-1, 1, -1);
//    //face bleue
//    glColor3f(82.f/255.f,86.f/255.f,89.f/255.f);
//    glVertex3f(1, -1, -1);
//    glVertex3f(1, -1, 1);
//    glVertex3f(1, 1, 1);
//    glVertex3f(1, 1, -1);
//    //face bleue
//    glColor3f(1, 1, 0);
//    glVertex3f(-1, -1, 1);
//    glVertex3f(1, -1, 1);
//    glVertex3f(1, 1, 1);
//    glVertex3f(-1, 1, 1);
//    //face mauve
//    glColor3f(104.f/255.f,104.f/255.f,114.f/255.f);
//    glVertex3f(-1, 1, 1);
//    glVertex3f(1, 1, 1);
//    glVertex3f(1, 1, -1);
//    glVertex3f(-1, 1, -1);
//    glEnd();
//    glPopMatrix();
}

void Bullet::quit() {

}

SphereCollider& Bullet::getSphereCollider() {
    return m_sphereCollider;
}
