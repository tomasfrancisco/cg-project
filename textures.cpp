//
// Created by Tomás Francisco on 19/06/16.
//

#include "textures.hpp"

GLuint      texture[20];
RgbImage    loader;

void initTextures() {
    glGenTextures(1, &texture[TEXTURE_DAY]);
    glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_DAY]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    loader.LoadBmpFile("textures/day.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 loader.GetNumCols(),
                 loader.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 loader.ImageData());

    glGenTextures(1, &texture[TEXTURE_NIGHT]);
    glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_NIGHT]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    loader.LoadBmpFile("textures/night.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 loader.GetNumCols(),
                 loader.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 loader.ImageData());

    glGenTextures(1, &texture[TEXTURE_WOOD]);
    glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_WOOD]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    loader.LoadBmpFile("textures/wood.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 loader.GetNumCols(),
                 loader.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 loader.ImageData());
}

GLuint getTexture(int texture_const) {
    return texture[texture_const];
}