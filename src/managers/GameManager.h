//
// Created by gdemers on 12/7/2020.
//

#ifndef J03_SU_H20_GROUPTP_GAMEMANAGER_H
#define J03_SU_H20_GROUPTP_GAMEMANAGER_H
#pragma once
#include "../utils/IncludeHeader.h"
#include "../managers/MapManager.h"
#include "../entities/Player.h"
#include "../managers/CollisionManager.h"
#include "../entities/map/Skybox.h"
#include "../entities/PlayerHUD.h"
#include "../managers/PassiveManager.h"
#include "../managers/UiManager.h"
#include "EnemyManager.h"
#include <SDL2/SDL_ttf.h>

class GameManager {
private:
    SDL_Window *window;
    SDL_GLContext context;
    bool isRunning;
    SDL_Event event;
    const Uint8* state;
    int dxMouse, dyMouse;
    UiManager* uiManager;
public:
    GameManager();
    virtual ~GameManager();
    void initialize(const char* _windowTitle, int _windowPosX, int _windowPosY, int _screenWidth, int _screenHeight, bool fullScreen);
    void handleEvents();
    void update();
    void render();
    void quit();
    bool getIsRunning() const;
    Player *m_player;
    Skybox *m_skybox;
    PlayerHUD *playerHud;
    PassiveManager *m_passiveManager;
    bool isColliding;
};

#endif //J03_SU_H20_GROUPTP_GAMEMANAGER_H
