//
// Created by Tomás Francisco on 20/06/16.
//

#ifndef CG_PROJECT_ROOMWINDOW_HPP
#define CG_PROJECT_ROOMWINDOW_HPP

#include "OpenGL.hpp"
#include "textures.hpp"
#include "materials.hpp"
#include "primitives.hpp"

void drawWindow(GLint width, GLint height, GLboolean isNight);
void drawTableBack(GLint width, GLint height, GLint depth, GLboolean isNight);

#endif //CG_PROJECT_ROOMWINDOW_HPP
