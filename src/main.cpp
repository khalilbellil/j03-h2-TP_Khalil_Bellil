#include "managers/GameManager.h"
#include "managers/MenuManager.h"

int main(int argc, char **args) {
    srand(time(NULL));
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    GameManager *game = new GameManager();
    MenuManager *menu = new MenuManager();
    game->initialize("TP OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                     SCREEN_WIDTH, SCREEN_HEIGHT, false);
    menu->initialize(game);
    while (menu->getIsRunning()) {
        frameStart = SDL_GetTicks();
        menu->handleEvents();
        menu->update();
        menu->render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    menu->quit();
    while (game->getIsRunning()) {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->quit();
    delete game;
    return 0;
}