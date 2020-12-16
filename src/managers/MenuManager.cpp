//
// Created by gdemers on 12/7/2020.
//

#include "MenuManager.h"
#include "TextureManager.h"


MenuManager::MenuManager() {
    window = nullptr;
    context = nullptr;
    isRunning = false;
    state = nullptr;

}

MenuManager::~MenuManager() {
}

void MenuManager::initialize(GameManager* _game) {
    game = _game;
    isRunning = true; // start menu loop
}

void MenuManager::handleEvents() {
    SDL_PollEvent(&(MenuManager::event));
    MenuManager::state = SDL_GetKeyboardState(NULL);
    SDL_GetRelativeMouseState(&dxMouse, &dyMouse);

    if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }
    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
    }
    if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
    }
    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
    }
    if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
    }
    if (state[SDL_SCANCODE_SPACE]) {
        isRunning = false;
        game->setIsRunning(true);
    }
    if (state[SDL_SCANCODE_C]) {
    }

}

void MenuManager::update() {

}

void MenuManager::render() {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //draw

    glFlush();
    SDL_GL_SwapWindow(window);
    //SDL_Delay(15);
}

void MenuManager::quit() {

}

bool MenuManager::getIsRunning() const {
    return isRunning;
}
