//
// Created by gdemers on 12/7/2020.
//

#include "Enemy.h"


Enemy::Enemy(EnemyType enemyType, int posX, int posZ) : Unit(posX, posZ) {
    switch (enemyType) {
        case EnemyType::Monster:
            this->m_health = 4;
            // need to implement animation for a monster
            break;
        case EnemyType::Boss:
            this->m_health = 12;
            // need to implement animation for a boss
            break;
        case EnemyType::Soldier:
            this->m_health = 3;
            for (int i = (int) EnemyAnimationType::Back; i != (int) EnemyAnimationType::Attack; i++) {
                handleTexture((EnemyAnimationType) i);
                //std::cout << "texture : " << i << std::endl;
            }
            break;
    }
}

Enemy::~Enemy() {

}

void Enemy::handleTexture(EnemyAnimationType enemyAnimationType) {
    switch (enemyAnimationType) {
        case EnemyAnimationType::Back:
            for (int i = 1; i <= nbTexture; i++) {
                this->loadTexture(
                        path_soldierT + std::string("movement/back/back_") + std::to_string(i) + std::string(".png"),
                        "soldier_back_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Forward:
            for (int i = 1; i <= nbTexture; i++) {
                this->loadTexture(path_soldierT + std::string("movement/forward/forward_") + std::to_string(i) +
                                  std::string(".png"),
                                  "soldier_forward_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Left:
            for (int i = 1; i <= nbTexture; i++) {
                this->loadTexture(
                        path_soldierT + std::string("movement/left/left_") + std::to_string(i) + std::string(".png"),
                        "soldier_left_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Left_Back:
            for (int i = 1; i <= nbTexture; i++) {
                this->loadTexture(path_soldierT + std::string("movement/left_back/left_back_") + std::to_string(i) +
                                  std::string(".png"),
                                  "soldier_left_back_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Right:
            for (int i = 1; i <= nbTexture; i++) {
                this->loadTexture(
                        path_soldierT + std::string("movement/right/right_") + std::to_string(i) + std::string(".png"),
                        "soldier_right_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Right_Back:
            for (int i = 1; i <= nbTexture; i++) {
                this->loadTexture(path_soldierT + std::string("movement/right_back/right_back_") + std::to_string(i) +
                                  std::string(".png"),
                                  "soldier_right_back_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Side_Left:
            for (int i = 1; i <= nbTexture; i++) {
                this->loadTexture(path_soldierT + std::string("movement/side_left/side_left_") + std::to_string(i) +
                                  std::string(".png"),
                                  "soldier_side_left_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Side_Right:
            for (int i = 1; i <= nbTexture; i++) {
                this->loadTexture(path_soldierT + std::string("movement/side_right/side_right_") + std::to_string(i) +
                                  std::string(".png"),
                                  "soldier_side_right_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Death:
            for (int i = 1; i <= nbTexture; i++) {
                this->loadTexture(path_soldierT + std::string("death/death_") + std::to_string(i) + std::string(".png"),
                                  "soldier_death_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Attack:
            for (int i = 1; i <= nbTextureAttack; i++) {
                this->loadTexture(
                        path_soldierT + std::string("attack/attack_") + std::to_string(i) + std::string(".png"),
                        "soldier_attack_" + std::to_string(i), true);
            }
            break;
    }
}
