#ifndef J03_H2_GROUPTP_UIMANAGER_H
#define J03_H2_GROUPTP_UIMANAGER_H
#include "../utils/IncludeHeader.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../entities/Player.h"
#include "../utils/opengl_util.h"
using namespace std;
class UiManager {
private:
    int health;
    int lives;
    int score;
    int ammo;
    TTF_Font * font;
    GLuint weapon_1;
public:
    UiManager();
    ~UiManager();

    void init();
    void update(Player *_player);
    void renderWeapon(const int weapon_nb, const double& X, const double& Y, const double& Z, const double& width, const double& height);
    void renderText(const TTF_Font *Font, const GLubyte& R, const GLubyte& G, const GLubyte& B, const double& X,
                    const double& Y, const double& Z, const std::string& Text);
    void render();
    void quit();

    void setHealth(int value);
    void setLives(int value);
    void setScore(int value);
    void setAmmo(int value);
    int getHealth();
    int getLives();
    int getScore();
    int getAmmo();
};


#endif //J03_H2_GROUPTP_UIMANAGER_H
