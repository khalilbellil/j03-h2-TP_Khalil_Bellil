//
// Created by Khalil B on 2020-12-15.
//

#ifndef J03_H2_TP_KHALIL_BELLIL_MENUMANAGER_H
#define J03_H2_TP_KHALIL_BELLIL_MENUMANAGER_H
#include "../utils/IncludeHeader.h"
#include <SDL2/SDL_ttf.h>
#include "GameManager.h"


class MenuManager {
    private:
        SDL_Window *window;
        SDL_GLContext context;
        bool isRunning;
        SDL_Event event;
        const Uint8* state;
        int dxMouse, dyMouse;
        GameManager* game;
        TTF_Font * font;
        bool playIsSelected = true;
    public:
        MenuManager();
        virtual ~MenuManager();
        void initialize(GameManager* _game);
        void handleEvents();
        void update();
        void renderText(const TTF_Font *Font, const GLubyte& R, const GLubyte& G, const GLubyte& B, const double& X,
                        const double& Y, const double& Z, const std::string& Text);
        void render();
        void quit();
        bool getIsRunning() const;
};


#endif //J03_H2_TP_KHALIL_BELLIL_MENUMANAGER_H
