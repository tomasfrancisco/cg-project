//
//  scene.cpp
//  cg-project
//
//  Created by Tomás Francisco and Madalena Fernandinho.
//  Copyright © 2016 Tomás Francisco and Madalena Fernandinho. All rights reserved.
//

#include "Scene.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

GLfloat ambientColor[] = {WHITE_COLOR, 1.0};

Loader bowling;
//Camera camera;

void loadObjects() {
    char file[20] = "bowling.obj";

    bowling.Load(file);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();

    //glTranslated(0,0,camera.dist);

    //glRotated(camera.pitch, 1,0,0);
    //glRotated(camera.yaw,0,1,0);

    bowling.Draw();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {

}

void special(int key, int x, int y) {

}

void initLights() {
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
}

void init(void) {
    glClearColor(WHITE_COLOR, 1.0);
    glShadeModel(GL_SMOOTH);

    //initLights();
    //glEnable(GL_LIGHTING);

    glEnable(GL_DEPTH_TEST);

    loadObjects();
}

void start(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH   | GLUT_STENCIL );
    glutInitWindowSize (SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition (400, 400);
    glutCreateWindow ("Computational Graphic Project");

    init();

    glutDisplayFunc(display);

    //glutSpecialFunc(special);
    //glutMotionFunc(Camera::Motion);
    //glutMouseFunc(Camera::Mouse);
    //glutKeyboardFunc(keyboard);

    glutMainLoop();
}