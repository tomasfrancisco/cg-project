//
// Created by Tomás Francisco on 19/06/16.
//

#ifndef CG_PROJECT_TEXTURES_HPP
#define CG_PROJECT_TEXTURES_HPP

#include "OpenGL.hpp"
#include "RgbImage.hpp"

#define TEXTURE_CAMP_FLOOR 0
#define TEXTURE_CAMP_WALL 1
#define TEXTURE_WOOD 2

void initTextures();
GLuint getTexture(int texture_const);

#endif //CG_PROJECT_TEXTURES_HPP
