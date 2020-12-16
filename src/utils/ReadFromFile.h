//
// Created by gdemers on 12/7/2020.
//

#ifndef J03_SU_H20_GROUPTP_READFROMFILE_H
#define J03_SU_H20_GROUPTP_READFROMFILE_H
#pragma once
#include "IncludeHeader.h"

class ReadFromFile {
    static std::vector<std::string> m_textureNames;
    static std::string m_texturePath;
    static std::string m_mapFilename;
    static std::vector<std::string> m_mapStrings;
    static std::string m_tempLine;
    static int m_lineLength;
    static int m_lineCount;
public:
    static void readTextureFile();
    static std::string getTexturePath();
    static std::vector<std::string> getTextureNames();
    static void readMapFile();
    static std::vector<std::string> getMapStrings();
    static int getLineLength();
    static int getLineCount();
};


#endif //J03_SU_H20_GROUPTP_READFROMFILE_H