#include "BulletManager.h"

vector<Bullet*> BulletManager::m_vecBullet;
int BulletManager::enemiesKilled = 0;
int BulletManager::enemiesToKill = 4;

BulletManager::~BulletManager() {
    for (auto p : m_vecBullet)
        delete p;
    m_vecBullet.clear();
}

void BulletManager::draw() {
    for(auto p : m_vecBullet)
        p->render();
}

int BulletManager::checkCollision(vector<Enemy*> _m_vecBullet) {
    for(auto it = m_vecBullet.begin(); it != m_vecBullet.end();){
        for(auto it2 = _m_vecBullet.begin(); it2 != _m_vecBullet.end();){
            if(CollisionManager::checkSphereCollisions((*it2)->getSphereCollider(), (*it)->getSphereCollider())){
                if(enemiesKilled < enemiesToKill){
                    SDL_Log("Killed");
                    EnemyManager::s_enemies.erase((*it2)->key);
                    it2 = _m_vecBullet.erase(it2);
                    enemiesKilled++;
                }else{
                    SDL_Log("You Won !");
                    return -1;
                }
            }
            else{
                ++it2;
            }
        }
        ++it;
    }
    return enemiesKilled;
}

void BulletManager::add(float _xPos, float _yPos, float _zPos, float _xDir, float _yDir, float _zDir, float _angle) {
    m_vecBullet.push_back(new Bullet(_xPos, _yPos, _zPos, _xDir, _yDir, _zDir, _angle));
}

void BulletManager::update(){
    for(auto p : m_vecBullet)
        p->update();
}
