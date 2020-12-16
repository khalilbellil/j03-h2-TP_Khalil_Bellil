#include "UiManager.h"

UiManager::UiManager(){
    health = 0;
    lives = 0;
    score = 0;
    ammo = 0;
}
UiManager::~UiManager(){

}

void UiManager::init() {
    font = TTF_OpenFont("assets/fonts/times.ttf", 16);
    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    weapon_1 = loadTexture("assets/textures/ui/pistol.png");
    if(!weapon_1) {
        printf("Erreur load texture weapon");
    }
}

void UiManager::update(Player *_player) {
    setHealth(_player->getHP());
    setAmmo(_player->getAmmo());
}

void UiManager::renderWeapon(const int weapon_nb, const double& X, const double& Y, const double& Z, const double& width, const double& height) {
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.f, 1.f, -22.f, 3.f, 1.f , 0, 0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, weapon_1);
    glTranslatef(X, 1, Z);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(-1*width, -1*height, 1);
    glTexCoord2f(0, 0);
    glVertex3f(1*width, -1*height, 1);
    glTexCoord2f(0, 1);
    glVertex3f(1*width, 1*height, 1);
    glTexCoord2f(1, 1);
    glVertex3f(-1*width, 1*height, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

void UiManager::renderText(const TTF_Font *Font, const GLubyte& R, const GLubyte& G, const GLubyte& B, const double& X,
                           const double& Y, const double& Z, const std::string& Text) {
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-15.f, -7.f, -22.f, -15.f, -7.f , 0, 0, 1, 0);

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
    glTexCoord2d(1, 0); glVertex3d(X+Message->w*.7f, Y, Z);
    glTexCoord2d(1, 1); glVertex3d(X+Message->w*.7f, Y+Message->h*.7f, Z);
    glTexCoord2d(0, 1); glVertex3d(X, Y+Message->h*.7f, Z);

    glEnd();

    glPopMatrix();

    glDeleteTextures(1, &Texture);
    SDL_FreeSurface(Message);
}

void UiManager::render() {
    glViewport(0, 0, SCREEN_WIDTH/4.f, SCREEN_HEIGHT/6.f); // health
    renderText(font, 255, 255, 255, 0, 0, 0, to_string(health) + "hp");

    glViewport(SCREEN_WIDTH/4.f, 0, SCREEN_WIDTH/4.f, SCREEN_HEIGHT/6.f); // weapon sprite
    renderWeapon(0, 0, 0, 0, 15, 15);

    glViewport((SCREEN_WIDTH/4.f)*2, 0, SCREEN_WIDTH/4.f, SCREEN_HEIGHT/6.f); // ammo
    if(ammo <= 0){
        renderText(font, 0, 0, 255, 5, 0, 0, to_string(ammo));
    }else{
        renderText(font, 255, 0, 0, 5, 0, 0, to_string(ammo));
    }

    glViewport((SCREEN_WIDTH/4.f)*3, 0, SCREEN_WIDTH/4.f, SCREEN_HEIGHT/6.f); // score
    renderText(font, 0, 255, 0, 0, 0, 0, to_string(score) + "/5");
}

void UiManager::quit() {
    TTF_CloseFont( font );
}

void UiManager::setHealth(int value) {
    this->health = value;
}

void UiManager::setLives(int value) {
    this->lives = value;
}

void UiManager::setScore(int value) {
    this->score = value;
}

void UiManager::setAmmo(int value) {
    this->ammo = value;
}

int UiManager::getHealth() {
    return this->health;
}

int UiManager::getLives() {
    return this->lives;
}

int UiManager::getScore() {
    return this->score;
}

int UiManager::getAmmo() {
    return this->ammo;
}
