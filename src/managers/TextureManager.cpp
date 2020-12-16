//
// Created by gdemers on 12/7/2020.
//

#include "TextureManager.h"

std::map<std::string, Texture *> TextureManager::s_textureMap;

void TextureManager::addT(GLuint idTexture, std::string nameT) {
    Texture *tempT = new Texture{idTexture, 1};
    s_textureMap[nameT] = tempT;
}

void TextureManager::deleteT(std::string nameT) {
    for (std::map<std::string, Texture *>::iterator it = s_textureMap.begin(); it != s_textureMap.end(); ++it) {
        if (it->first.compare(nameT) == 0) {
            s_textureMap.erase(it->first);
            break;
        }
    }
}

void TextureManager::loadT(std::string path, std::string nameT, bool mipmap) {
    bool isLoaded = false;
    GLuint idTexture = loadTexture(path.c_str(), mipmap);
    if (idTexture != 0) {
        for (std::map<std::string, Texture *>::iterator it = s_textureMap.begin(); it != s_textureMap.end(); ++it) {
            if (it->first.compare(nameT) == 0) {
                isLoaded = true;
                s_textureMap.at(it->first)->m_nbTime++;
                break;
            }
        }
        if (!isLoaded) {
            addT(idTexture, nameT);
        }
    } else { SDL_Log("GLuint idTexture invalid"); }
}

GLuint TextureManager::getTextureID(std::string nameT) {
    for (std::map<std::string, Texture *>::iterator it = s_textureMap.begin(); it != s_textureMap.end(); ++it) {
        if (it->first.compare(nameT) == 0) {
            return s_textureMap.at(it->first)->m_idTexture;
        }
    }
    return -1;
}

void TextureManager::clear() {
    s_textureMap.clear();
}
