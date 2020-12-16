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
#include "../managers/BulletManager.h"
#include "../managers/UiManager.h"
#include "EnemyManager.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

class GameManager {
private:

    SDL_GLContext context;
    bool isRunning;
    SDL_Event event;
    const Uint8* state;
    int dxMouse, dyMouse;
    UiManager* uiManager;

    //The music that will be played
    Mix_Music *gMusic = NULL;

    //The sound effects that will be used
    Mix_Chunk *gScratch = NULL;
    Mix_Chunk *gHigh = NULL;
    Mix_Chunk *gMedium = NULL;
    Mix_Chunk *gLow = NULL;
public:
    SDL_Window *window;
    GameManager();
    virtual ~GameManager();
    bool loadMedia();
    void initialize(const char* _windowTitle, int _windowPosX, int _windowPosY, int _screenWidth, int _screenHeight, bool fullScreen);
    void handleEvents();
    void update();
    void render();
    void quit();
    bool getIsRunning() const;
    void setIsRunning(bool _new);
    Player *m_player;
    Skybox *m_skybox;
    PlayerHUD *playerHud;
    PassiveManager *m_passiveManager;
    bool isColliding;
};

#endif //J03_SU_H20_GROUPTP_GAMEMANAGER_H
