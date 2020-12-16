//
// Created by gdemers on 12/7/2020.
//

#include "EnemyManager.h"

std::map<int, Enemy *> EnemyManager::s_enemies;
int EnemyManager::cpt = 0;
bool EnemyManager::isInitialized = false;

void EnemyManager::initialize() {

    glPushMatrix();
    if (!isInitialized) {
        int value = 0;
        float cubeScale = 1;
        float xPos = ReadFromFile::getLineCount() - cubeScale;
        float yPos = 1;
        float zPos = -ReadFromFile::getLineLength() + cubeScale;

        glTranslatef(xPos, yPos, zPos);
        for (int i = 0; i < ReadFromFile::getLineCount(); ++i) {
            for (int j = 0; j < ReadFromFile::getLineLength(); ++j) {
                value = rand() % 300;
                std::string index = MapManager::getMapStrings().at(i);
                int textureId = index.at(j) - 48;

                if (textureId == 0 && cpt < maxEnemies && value == 10) {
                    EnemyManager::s_enemies.insert(
                            std::pair<int, Enemy *>(cpt++, new Enemy(EnemyType::Soldier, xPos, zPos)));
                }
                if (j < ReadFromFile::getLineLength()) {
                    zPos += cubeScale * 2;
                    glTranslatef(0, 0, cubeScale * 2);
                }
            }
            xPos -= cubeScale * 2;
            zPos -= ReadFromFile::getLineLength() * 2;

            glTranslatef(-cubeScale * 2, 0, -ReadFromFile::getLineLength() * 2);
        }
    }
    glPopMatrix();
    if (cpt == maxEnemies) {
        isInitialized = true;
    }
}

void EnemyManager::update(Player target) {
    for (auto it : s_enemies) {
        it.second->update(0, target, "soldier_forward_1");
    }
}

void EnemyManager::clear() {
    for (auto it : s_enemies) {
        delete it.second;
    }
    s_enemies.clear();
}
