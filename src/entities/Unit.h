//
// Created by gdemers on 12/7/2020.
//

#ifndef J03_SU_H20_GROUPTP_UNIT_H
#define J03_SU_H20_GROUPTP_UNIT_H
#pragma once

#include "../utils/IncludeHeader.h"
#include "../managers/TextureManager.h"
#include "Player.h"
#include "../utils/Timer.h"

class Unit {
    enum WaypointEnum {
        WYP1, WYP2, WYP3, WYP4
    };
    enum State {
        Patrol, Chase, Idle
    };
    struct WaypointStruct {
        int posX, posY, posZ;
    };
protected:
    const int m_dstRange = 5;
    int m_health, m_stamina;
    const int m_maxStamina = 10;
    bool m_isInRange;
    bool m_isDetected;
    bool m_isHit;
    bool m_isAlive;
    bool m_isBored;
    int m_posX, m_posY, m_posZ;
    const int m_speed = 3;
    const Uint32 m_rate_of_fire = 750;
    Timer *p_attackRateTimer;
    Timer *p_inChasingStateTimer;
    Timer *p_chasingCooldownTimer;
    const Uint32 m_cooldown = 1500;
    const Uint32 m_bored = 3000;
    bool m_isChasing;
    int m_chasingToggleValue;
    WaypointStruct m_wyp1, m_wyp2, m_wyp3, m_wyp4;
    int m_current_waypoint;
public:

    Unit(int posX, int posZ);

    ~Unit();

    virtual void loadTexture(std::string pathT, std::string nameT, bool mipmap);

    virtual void move(Uint32 deltaTime, State state);

    virtual void checkDistance(Player target);

    virtual void checkHealth();

    virtual void checkStamina();

    virtual void checkHit();

    virtual void update(Uint32 deltaTime, Player target, std::string nameT);

    virtual void attack();

    virtual void hit();

    virtual void die();

    int getPosX() { return m_posX; }

    int getPosZ() { return m_posZ; }

    int getMagnitude(Player target);

    virtual void waypointInit();

    virtual void timerInit();

    virtual void draw(std::string nameT);
};

#endif //J03_SU_H20_GROUPTP_UNIT_H
