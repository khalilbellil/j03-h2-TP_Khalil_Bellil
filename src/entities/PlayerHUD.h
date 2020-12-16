//
// Created by gdemers on 12/7/2020.
//

#ifndef J03_SU_H20_GROUPTP_PLAYERHUD_H
#define J03_SU_H20_GROUPTP_PLAYERHUD_H
#pragma once
#include "../utils/IncludeHeader.h"

class PlayerHUD {
    GLuint m_textureId = 0;
public:
    PlayerHUD();
    void drawFPSWeapon(float x, float y, float z, float angle);
};

#endif //J03_SU_H20_GROUPTP_PLAYERHUD_H
