//
//  scene.cpp
//  cg-project
//
//  Created by Tomás Francisco and Madalena Fernandinho.
//  Copyright © 2016 Tomás Francisco and Madalena Fernandinho. All rights reserved.
//

#include "scene.hpp"

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 50


void start(int argc, char** argv) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH   | GLUT_STENCIL );
    glutInitWindowSize (SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition (400, 400);
    glutCreateWindow ("Computational Graphic Project");
    glutMainLoop();
}