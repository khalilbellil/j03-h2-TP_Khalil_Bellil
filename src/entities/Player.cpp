//
// Created by gpelletier on 12/8/2020.
//

#include "Player.h"
#include <cmath>
#define TORAD M_PI/180.0

Player::Player(float startPosX, float startPosZ) {
    m_step = 0.1;
    m_camX = startPosX;
    m_camY = 1;
    m_camZ = startPosZ;
    m_refX = m_step;
    m_refY = 1;
    m_refZ = 0;
    m_alpha = 0;
    m_flySpeed = 0.1f;
    m_HP = 100;
    m_Ammo = 20;
}

Player::~Player() = default;

void Player::move(Direction direction, int dxMouse) {

    float dX = 0, dZ = 0;

    switch (direction) {
        case FORWARD:
            dZ = cos(m_alpha * TORAD) * m_step;
            dX = sin (m_alpha * TORAD) * m_step;
            m_camZ += dZ;
            m_camX += dX;
            m_refZ += dZ;
            m_refX += dX;
            break;
        case BACKWARD:
            dZ = cos(m_alpha * TORAD) * m_step;
            dX = sin(m_alpha * TORAD) * m_step;
            m_camZ -= dZ;
            m_camX -= dX;
            m_refZ -= dZ;
            m_refX -= dX;
            break;
        case LEFT:
            dZ = cos((90 - m_alpha) * TORAD) * m_step;
            dX = sin((90 - m_alpha) * TORAD) * m_step;
            m_camZ = m_camZ - dZ;
            m_camX = m_camX + dX;
            m_refZ -= dZ;
            m_refX += dX;
            break;
        case RIGHT:
            dZ = cos((90 - m_alpha) * TORAD) * m_step;
            dX = sin((90 - m_alpha) * TORAD) * m_step;
            m_camZ = m_camZ + dZ;
            m_camX = m_camX - dX;
            m_refZ += dZ;
            m_refX -= dX;
            break;
        case ROTATE:
            m_alpha -= dxMouse / 5;
            dZ = cos(m_alpha * TORAD) * m_step;
            dX = sin(m_alpha * TORAD) * m_step;
            m_refZ = m_camZ + dZ;
            m_refX = m_camX + dX;
            break;
        case UP:
            m_camY += m_flySpeed;
            m_refY += m_flySpeed;
            break;
        case DOWN:
            m_camY -= m_flySpeed;
            m_refY -= m_flySpeed;
            break;
    }
    m_sphereCollider = {m_camX, m_camY, m_camZ, 0.5};
}

void Player::cameraPos() {
    gluLookAt(m_camX, m_camY, m_camZ, m_refX, m_refY, m_refZ, 0.0f, 1.0f, 0.0f);
}

void Player::setCamX(float camX) {
    m_camX = camX;
}

void Player::setCamZ(float camZ) {
    m_camZ = camZ;
}

float Player::getCamX() {
    return m_camX;
}

float Player::getCamY() {
    return m_camY;
}

float Player::getCamZ() {
    return m_camZ;
}

void Player::setRefX(float refX) {
    m_refX = refX;
}

void Player::setRefZ(float refZ) {
    m_refZ = refZ;
}

float Player::getRefX() {
    return m_refX;
}

float Player::getRefY() {
    return m_refY;
}

float Player::getRefZ() {
    return m_refZ;
}

SphereCollider &Player::getSphereCollider() {
    return m_sphereCollider;
}

float Player::getAlpha() {
    return m_alpha;
}

void Player::setHP(int i) {
    m_HP += i;
}

void Player::setAmmo(int i) {
    m_Ammo += i;
}

int Player::getHP() {
    return m_HP;
}

int Player::getAmmo() {
    return m_Ammo;
}

void Player::shoot(){
    SDL_Log("Shooting");
}