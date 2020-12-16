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
    font = nullptr;
}

MenuManager::~MenuManager() {
}

void MenuManager::initialize(GameManager* _game) {
    game = _game;
    window = _game->window;
    font = TTF_OpenFont("assets/fonts/times.ttf", 16);
    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
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
        playIsSelected = true;
    }
    if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
        playIsSelected = false;
    }
    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
    }
    if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
    }
    if (state[SDL_SCANCODE_SPACE]) {
        isRunning = false;
        if(playIsSelected){
            game->setIsRunning(true);
        }
    }
    if (state[SDL_SCANCODE_C]) {
    }

}

void MenuManager::update() {

}

void MenuManager::renderText(const TTF_Font *Font, const GLubyte& R, const GLubyte& G, const GLubyte& B, const double& X,
                           const double& Y, const double& Z, const std::string& Text) {
    glPushMatrix();
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();


    SDL_Color Color = {R, G, B};
    SDL_Surface *Message = TTF_RenderText_Blended(const_cast<TTF_Font*>(Font), Text.c_str(), Color);
    unsigned Texture = 0;

    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 Message->pixels);

    glRotated(180, 0, 0, 1);
    glBegin(GL_QUADS);

    glTexCoord2d(0, 0); glVertex3d(X, Y, Z);
    glTexCoord2d(1, 0); glVertex3d(X+Message->w*.2f, Y, Z);
    glTexCoord2d(1, 1); glVertex3d(X+Message->w*.2f, Y+Message->h*.2f, Z);
    glTexCoord2d(0, 1); glVertex3d(X, Y+Message->h*.2f, Z);

    glEnd();

    glPopMatrix();

    glDeleteTextures(1, &Texture);
    SDL_FreeSurface(Message);
}

void MenuManager::render() {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(-15.f, -7.f, -22.f, -15.f, -7.f , 0, 0, 1, 0);

    //draw

    if(playIsSelected){
        glTranslatef(-7.5f, .0f, .0f);
        renderText(font, 255, 255, 255, 0, 0, 0, "Jouer");
        glTranslatef(-7.5f, -10.0f, .0f);
        renderText(font, 255, 0, 0, 0, 0, 0, "Quitter");
    }else{
        glTranslatef(-7.5f, .0f, .0f);
        renderText(font, 255, 0, 0, 0, 0, 0, "Jouer");
        glTranslatef(-7.5f, -10.0f, .0f);
        renderText(font, 255, 255, 255, 0, 0, 0, "Quitter");
    }




    glFlush();
    SDL_GL_SwapWindow(window);
}

void MenuManager::quit() {
    TTF_CloseFont( font );
}

bool MenuManager::getIsRunning() const {
    return isRunning;
}
