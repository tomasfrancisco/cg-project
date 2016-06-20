//
// Created by Tomás Francisco on 19/06/16.
//

#ifndef CG_PROJECT_BILLARDTABLE_HPP
#define CG_PROJECT_BILLARDTABLE_HPP

#include "OpenGL.hpp"
#include "primitives.hpp"
#include "textures.hpp"
#include "materials.hpp"
#include "colors.hpp"

#define PI 3.14159

void drawBilliardTable(GLint width, GLint height);
bool testBarsColision(GLdouble x, GLdouble z);
void runColisionWithBalls(GLdouble * xPosition, GLdouble * zPosition, GLdouble * rotation, GLdouble radius);

#endif //CG_PROJECT_BILLARDTABLE_HPP
