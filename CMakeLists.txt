cmake_minimum_required(VERSION 3.17)
set(
        project_name
        j03-h2-TP_Khalil_Bellil
)
file(
        GLOB_RECURSE
        source_file
        src/*
)
#si besoin de repertoire assets
file(
        COPY
        assets
        DESTINATION
       ${CMAKE_BINARY_DIR}
)
project(${project_name})
set(CMAKE_CXX_STANDARD 17)
add_executable(${project_name} ${source_file} src/managers/WallManager.cpp src/managers/WallManager.h)
if (WIN32)
    target_link_libraries(
            ${project_name}
            -lmingw32
            -lSDL2main
            -lSDL2
            -lSDL2_image
            -lopengl32
            -lglu32
            -lSDL2_ttf
            -lSDL2_mixer
    )
endif ()
if(UNIX)
    target_link_libraries(
            ${project_name}
            -lSDL2main
            -lSDL2
            -lSDL2_image
            -lGL
            -lGLU
            -lSDL2_ttf
            -lSDL2_mixer
    )
endif()