//
// Created by gdemers on 12/7/2020.
//

#include "PlayerHUD.h"

PlayerHUD::PlayerHUD() {
    m_textureId = loadTexture("assets/textures/weapons/pistol_1.png");
    std::cout << m_textureId << std::endl;
    if (m_textureId == 0) {
        std::cout << "Unable to load texture" << std::endl;
    }
}

void PlayerHUD::drawFPSWeapon(float x, float y, float z, float angle) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTranslatef(x, 1, z);
    glRotatef(angle, 0,1,0);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(1, -1, 1);
    glTexCoord2f(0, 1);
    glVertex3f(1, 1, 1);
    glTexCoord2f(1, 1);
    glVertex3f(-1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}
