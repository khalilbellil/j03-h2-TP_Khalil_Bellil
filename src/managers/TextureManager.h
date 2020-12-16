//
// Created by gdemers on 12/7/2020.
//

#ifndef J03_SU_H20_GROUPTP_TEXTUREMANAGER_H
#define J03_SU_H20_GROUPTP_TEXTUREMANAGER_H
#pragma once

#include "../utils/IncludeHeader.h"


struct Texture {
    GLuint m_idTexture;
    int m_nbTime;
};

class TextureManager {
    static void addT(GLuint idTexture, std::string nameT);

public:
    static std::map<std::string, Texture *> s_textureMap;

    static void loadT(std::string path, std::string nameT, bool mipmap);

    static void deleteT(std::string nameT);

    static GLuint getTextureID(std::string nameT);

    static void clear();
};

#endif //J03_SU_H20_GROUPTP_TEXTUREMANAGER_H
