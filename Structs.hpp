//
// Created by Tomás Francisco on 18/06/16.
//

#ifndef CG_PROJECT_STRUCTS_HPP
#define CG_PROJECT_STRUCTS_HPP

#include "OpenGL.hpp"
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    double x, y, z;

};

struct GLPoint {
    GLdouble x, y, z;
};

struct GLVision {
    GLfloat radius, angle, inclination;
};

struct GLObserver {
    GLPoint eye, center, up;
    GLVision vision;
};

struct Face {
    vector <Point> V;
    vector <Point> VN;
    vector <Point> uvs;
};


#endif //CG_PROJECT_STRUCTS_HPP
