//
// Created by gdemers on 12/7/2020.
//

#include "GameManager.h"
#include "TextureManager.h"

//GLuint m_textureId;

GameManager::GameManager() {
    window = nullptr;
    context = nullptr;
    isRunning = false;
    state = nullptr;
    m_player = nullptr;
    isColliding = false;
    m_skybox = nullptr;
    playerHud = nullptr;
    uiManager = nullptr;
}

GameManager::~GameManager() {
    delete m_player;
    delete m_skybox;
    delete uiManager;
}

void
GameManager::initialize(const char *_windowTitle, int _windowPosX, int _windowPosY, int _screenWidth, int _screenHeight,
                        bool fullScreen) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("SDL_Init Failed : ", SDL_GetError());
    }
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        SDL_Log("IMG_Init Failed : ", IMG_GetError());
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    GameManager::window = SDL_CreateWindow(_windowTitle, _windowPosX, _windowPosY, _screenWidth, _screenHeight,
                                           SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Window is NULL");
    }
    GameManager::context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        SDL_Log("Context is NULL");
    }
    if(!TTF_WasInit() && TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(1);
    }
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_WarpMouseInWindow(window, _screenWidth / 2, _screenHeight / 2);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    playerHud = new PlayerHUD();

    MapManager::init();
    gluPerspective(70, SCREEN_WIDTH / SCREEN_HEIGHT, 0.1, 500);

    uiManager = new UiManager();
    uiManager->init();
    m_player = new Player(25, -25);
    m_skybox = new Skybox();
    EnemyManager::initialize();
}

void GameManager::handleEvents() {
    SDL_PollEvent(&(GameManager::event));
    GameManager::state = SDL_GetKeyboardState(NULL);
    SDL_GetRelativeMouseState(&dxMouse, &dyMouse);

    float oldPlayerXpos = m_player->getCamX();
    float oldPlayerZpos = m_player->getCamZ();
    float oldPlayerRefX = m_player->getRefX();
    float oldPlayerRefZ = m_player->getRefZ();

    for (int i = 0; i < WallManager::getWalls().size(); ++i) {
        isColliding = CollisionManager::checkSphereCollisions(m_player->getSphereCollider(),
                                                              WallManager::getWalls()[i]->getSphereCollider());
        if (isColliding) {
            break;
        }
    }

    m_player->move(ROTATE, dxMouse);

    if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }
    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
        m_player->move(Direction::FORWARD, -1);
    }
    if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
        m_player->move(Direction::BACKWARD, -1);
    }
    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
        m_player->move(Direction::LEFT, -1);
    }
    if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
        m_player->move(Direction::RIGHT, -1);
    }
    if (state[SDL_SCANCODE_E]) {
        //m_player->move(Direction::UP, -1);
        BulletManager::add(m_player->getCamX(), m_player->getCamY(), m_player->getCamZ(), m_player->getRefX(),
                           m_player->getRefY(), m_player->getRefZ(), m_player->getAlpha());
    }
    if (state[SDL_SCANCODE_C]) {
        m_player->move(Direction::DOWN, -1);
    }
    if (isColliding) {
        m_player->setCamX(oldPlayerXpos);
        m_player->setCamZ(oldPlayerZpos);
        m_player->setRefX(oldPlayerRefX);
        m_player->setRefZ(oldPlayerRefZ);
    }
}

void GameManager::update() {
    uiManager->update(m_player);
    PassiveManager::checkCollision(m_player);
    EnemyManager::update(*m_player);
    vector<Enemy*> enemies;
    int i = 0;
    for( auto const& [k, val] : EnemyManager::s_enemies )
    {
        val->key = k;
        enemies.push_back(val);
        i++;
    }
    BulletManager::update();
    BulletManager::checkCollision(enemies);
}

void GameManager::render() {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //region GAME VIEWPORT rendering:
    glViewport(0, SCREEN_HEIGHT/6.f, SCREEN_WIDTH, SCREEN_HEIGHT - (SCREEN_HEIGHT/6.f));

    MapManager::generateWalls();
    m_player->cameraPos(); // position de la camera
    playerHud->drawFPSWeapon(m_player->getRefX(), 1, m_player->getRefZ(), m_player->getAlpha());
    m_skybox->draw();
    MapManager::drawPlane();
    WallManager::drawWalls();
    PassiveManager::draw();
    EnemyManager::draw();
    BulletManager::draw();
    //endregion

    //region UI VIEWPORT rendering:
    uiManager->render();
    //endregion

    glFlush();
    SDL_GL_SwapWindow(window);
    //SDL_Delay(15);
}

void GameManager::quit() {
    TextureManager::clear();
    MapManager::destructor();
    WallManager::destructor();
    PassiveManager::destructor();
    uiManager->quit();
    SDL_GL_DeleteContext(context);
    context = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool GameManager::getIsRunning() const {
    return isRunning;
}

void GameManager::setIsRunning(bool _new){
    isRunning = _new;
}