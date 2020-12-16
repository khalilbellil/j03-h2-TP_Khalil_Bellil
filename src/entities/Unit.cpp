//
// Created by gdemers on 12/8/2020.
//

#include "Unit.h"

Unit::Unit(int posX, int posZ) {
    m_health = 3, m_stamina = m_maxStamina, m_isAlive = true, m_isInRange = false, m_isHit = false;
    m_isDetected = false, m_isBored = false, m_isChasing = false;
    m_posX = posX;
    m_posZ = posZ;
    m_posY = 0;
    waypointInit();
    timerInit();
    m_chasingToggleValue = 0; // important value so that we do not reset the timer while chasing every turn
    m_current_waypoint = 0;
}

Unit::~Unit() {
    delete p_attackRateTimer;
    delete p_inChasingStateTimer;
    delete p_chasingCooldownTimer;
}

void Unit::loadTexture(std::string pathT, std::string nameT, bool mipmap) {
    TextureManager::loadT(pathT, nameT, mipmap);
}

void Unit::move(Uint32 deltaTime, State state) {
    if (!m_isInRange && state == State::Patrol) {
        switch (m_current_waypoint) {
            case WYP1:
                if (m_posX != m_wyp1.posX && m_posZ != m_wyp1.posZ) {
                    m_current_waypoint = 0;
                } else {
                    m_current_waypoint = 1;
                }
                // set the position to the next position WYP1
                break;
            case WYP2:
                if (m_posX != m_wyp2.posX && m_posZ != m_wyp2.posZ) {
                    m_current_waypoint = 1;
                } else {
                    m_current_waypoint = 2;
                }
                // set the position to the next position WYP2
                break;
            case WYP3:
                if (m_posX != m_wyp3.posX && m_posZ != m_wyp3.posZ) {
                    m_current_waypoint = 2;
                } else {
                    m_current_waypoint = 3;
                }
                // set the position to the next position WYP3
                break;
            case WYP4:
                if (m_posX != m_wyp4.posX && m_posZ != m_wyp4.posZ) {
                    m_current_waypoint = 3;
                } else {
                    m_current_waypoint = 0;
                }
                // set the position to the next position WYP4
                break;
        }
    } else if (!m_isInRange && state == State::Chase) {
        if (SDL_GetTicks() - p_inChasingStateTimer->getStart() >= m_bored) {
            // set position to current position
            m_isBored = true;
        }
        // set the position to the last position of the target
    } else if (m_isInRange && state == State::Chase) {
        // set position to current position
    } else if (m_isBored && state == State::Idle) {
        // set the position to the current position of the unit
        if (SDL_GetTicks() - p_chasingCooldownTimer->getStart() >= m_cooldown) {
            m_chasingToggleValue = 0;
        }
    }
}
// could be moved in a math class
/***************************************************************************/
int Unit::getMagnitude(Player target) {
    // target magnitude math
    int targetPosX = target.getCamX(), targetPosZ = target.getCamZ();
    int targetMag = (targetPosX * targetPosX) + (targetPosZ * targetPosZ);
    // unit magnitude math
    int myPosX = getPosX(), myPosZ = getPosZ();
    int myMag = (myPosX * myPosX) + (myPosZ * myPosZ);
    // diff magnitude
    int magnitude = abs(targetMag - myMag);
    return magnitude;
}

void Unit::checkDistance(Player target) {
    int magnitude = getMagnitude(target);
    if (magnitude < (m_dstRange * m_dstRange)) {
        m_isInRange = true;
        // could be check if the unity is facing the player target opposite forward
        m_isDetected = true;
        // m_isChasing must only trigger once when switching into chase mode (which it isnt doing right now)
        if (m_chasingToggleValue == 0) {
            m_isChasing = true;
            m_chasingToggleValue++;
        }
    } else {
        m_isInRange = false;
        // have to put m_isDetected to false after magnitude is greater - like after 3sec of chasing becomes false
    }
}

/***************************************************************************/
void Unit::checkHealth() {
    if (m_health <= 0) {
        die();
    }
}

void Unit::checkStamina() {
    if (m_stamina <= 0) {
        // using the same timer for the cooldown of the stamina bar but should still work
        if (SDL_GetTicks() - p_attackRateTimer->getStart() >= m_cooldown) {
            m_stamina = m_maxStamina;
            p_attackRateTimer->restart();
        }
    } else {
        if (SDL_GetTicks() - p_attackRateTimer->getStart() >= m_rate_of_fire) {
            attack();
            p_attackRateTimer->restart();
        }
    }
}

void Unit::checkHit() {
    // if collision box confirm
    hit();
}

void Unit::update(Uint32 deltaTime, Player target, std::string nameT) {
    checkHit();
    checkDistance(target);
    if (!m_isDetected) {
        move(deltaTime, State::Patrol);
    } else {
        if (m_isChasing) { // && it is my first time switching in this state
            p_inChasingStateTimer->restart();
            m_isChasing = false;
        }
        move(deltaTime, State::Chase);
        if (m_isInRange) {
            if (m_isBored) {
                move(deltaTime, State::Idle);
            }
            // checkStamina and attack
            checkStamina();
        }
    }
    draw(nameT);
}

void Unit::attack() {
    // update animation, check collision with player
    // add a chance of hit
    m_stamina--;
}

void Unit::hit() {
    m_health--;
    checkHealth();
}

void Unit::die() {
    m_isAlive = false;
}

/*******************************************************************/

void Unit::waypointInit() {
    // if there is a wall collision change sign
    m_wyp1.posY = m_wyp2.posY = m_wyp3.posY = m_wyp4.posY = m_posY;
    // left, forward
    m_wyp1.posX = m_posX - m_dstRange;
    m_wyp1.posZ = m_posZ + m_dstRange;
    // left, strafe
    m_wyp2.posX = m_posX - m_dstRange;
    m_wyp2.posZ = m_posZ;
    // right, backward
    m_wyp3.posX = m_posX;
    m_wyp3.posZ = m_posZ - m_dstRange;
    // right, strafe
    m_wyp4.posX = m_posX + m_dstRange;
    m_wyp4.posZ = m_posZ;
}

void Unit::timerInit() {
    p_attackRateTimer = new Timer();
    p_inChasingStateTimer = new Timer();
    p_chasingCooldownTimer = new Timer();
}

/*******************************************************************/

void Unit::draw(std::string nameT) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID(nameT));
    glTranslatef(m_posX, 1, m_posZ);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2d(0, 0);
    glVertex3d(-1, -1, -1);
    glTexCoord2d(1, 0);
    glVertex3d(1, -1, -1);
    glTexCoord2d(1, 1);
    glVertex3d(1, 1, -1);
    glTexCoord2d(0, 1);
    glVertex3d(-1, 1, -1);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}
