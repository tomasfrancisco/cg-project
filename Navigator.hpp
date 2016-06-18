//
// Created by Tomás Francisco on 18/06/16.
//

#ifndef CG_PROJECT_NAVIGATOR_HPP
#define CG_PROJECT_NAVIGATOR_HPP

#include "OpenGL.hpp"
#include "Structs.hpp"
#include <functional>
#include <stdlib.h>
#include <math.h>

#define MAX_VERTICAL_INCLINATION 0.35
#define MAX_HORIZONTAL_INCLINATION 0.5

using namespace std;

extern GLfloat verticalInclination, horizontalInclination;
extern GLObserver observer;

void initObserver(GLdouble eyeX,         GLdouble eyeY,        GLdouble eyeZ,
                  GLdouble upX,          GLdouble upY,         GLdouble upZ,
                  GLdouble visionRadius, GLdouble visionAngle, GLdouble visionInclination);
GLObserver getObserver();
void Special(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);


#endif //CG_PROJECT_NAVIGATOR_HPP
