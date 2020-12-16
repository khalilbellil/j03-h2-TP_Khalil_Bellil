//
// Created by gpelletier on 12/8/2020.
//
#pragma once
#ifndef J03_SU_H20_GROUPTP_PLAYER_H
#define J03_SU_H20_GROUPTP_PLAYER_H

#include "../utils/IncludeHeader.h"
#include "SphereCollider.h"
#include "Wall.h"
#include "../managers/CollisionManager.h"

class Player {

private:
    int m_HP;
    int m_Ammo;

    float m_step;
    float m_camX;
    float m_camY;
    float m_camZ;
    float m_refX;
    float m_refY;
    float m_refZ;
    float m_alpha;
    float m_flySpeed;

    SphereCollider m_sphereCollider;

public:

    Player(float startPosX, float startPosZ);
    ~Player();

    void cameraPos();
    void move(Direction direction, int dxMouse);
    SphereCollider& getSphereCollider();
    void setCamX(float camX);
    void setCamZ(float camZ);
    float getCamX();
    float getCamY();
    float getCamZ();
    void setRefX(float refX);
    void setRefZ(float refZ);
    float getRefX();
    float getRefY();
    float getRefZ();
    float getAlpha();

    int getHP();
    int getAmmo();
    void setHP(int i);
    void setAmmo(int i);

    void shoot();
};

#endif //J03_SU_H20_GROUPTP_PLAYER_H