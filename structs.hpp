//
// Created by Tomás Francisco on 20/06/16.
//

#ifndef CG_PROJECT_STRUCTS_HPP
#define CG_PROJECT_STRUCTS_HPP

#include "OpenGL.hpp"

struct Observer {
    GLdouble    position[3],
                lookAt[3],
                upVector[3],
                vision[3];
};

struct Window {
    GLint   windowWidth,
            windowHeight;

    GLfloat mainViewportWidth,
            mainViewportHeight,

            miniMapViewportWidth,
            miniMapViiewportHeight,

            informationViewportWidth,
            informationViewportHeight;
};

struct Ball {
    GLdouble x, y, z;
    GLdouble rotation;
};

struct Light {
    GLfloat position[4],
            quadraticAttenuation,
            linearAttenuation,
            attenuationConstant,
            diffuseColor[4],
            color[4];
};




#endif //CG_PROJECT_STRUCTS_HPP
