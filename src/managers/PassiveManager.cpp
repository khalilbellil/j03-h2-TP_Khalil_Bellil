//
// Created by gpelleti on 12/10/2020.
//

#include "PassiveManager.h"

vector<Passive*> PassiveManager::m_vecPassives;
float PassiveManager::m_size = 0.2;

void PassiveManager::destructor() {
    for (auto p : m_vecPassives)
        delete p;
    m_vecPassives.clear();
}

void PassiveManager::checkCollision(Player *player) {
    for(auto it = m_vecPassives.begin(); it != m_vecPassives.end();){
        if(CollisionManager::checkSphereCollisions(player->getSphereCollider(), (*it)->getSphereCollider())){
            switch((*it)->getType()){
                case AMMO:
                    player->setAmmo((*it)->getAmount());
                    break;
                case HEALTH:
                    player->setHP((*it)->getAmount());
                    break;
            }
            delete *it;
            it = m_vecPassives.erase(it);
        }
        else{
            ++it;
        }
    }
}

void PassiveManager::draw() {
    for(auto p : m_vecPassives)
        p->draw();
}

void PassiveManager::add(float xpos, float zpos) {
    Vector3D_WHD vect = {xpos, m_size, zpos, m_size, m_size, m_size};
    PassiveType pt = static_cast<PassiveType>(rand() % LAST);
    m_vecPassives.push_back(new Passive(pt, vect));
}
