//
// Created by Tomás Francisco on 18/06/16.
//

#include "Navigator.hpp"

GLfloat verticalInclination = 0.0,
        horizontalInclination = 0.0;

GLObserver observer;


void initObserver(GLdouble eyeX,         GLdouble eyeY,        GLdouble eyeZ,
                  GLdouble upX,          GLdouble upY,         GLdouble upZ,
                  GLdouble visionRadius, GLdouble visionAngle, GLdouble visionInclination) {
    observer.eye.x    = eyeX;
    observer.eye.y    = eyeY;
    observer.eye.z    = eyeZ;

    observer.center.x = eyeX - visionRadius * cos(visionAngle);
    observer.center.y = eyeY;
    observer.center.z = eyeZ - visionRadius * sin(visionAngle);

    observer.up.x     = upX;
    observer.up.y     = upY;
    observer.up.z     = upZ;

    observer.vision.radius = visionRadius;
    observer.vision.angle = visionAngle;
    observer.vision.inclination = visionInclination;
}

GLObserver getObserver() {
    return observer;
}

void moveObserver(int key) {
    switch(key) {
        case GLUT_KEY_UP:
            observer.eye.x += observer.vision.inclination * cos(observer.vision.angle);
            observer.eye.z -= observer.vision.inclination * sin(observer.vision.angle);
            break;
        case GLUT_KEY_DOWN:
            observer.eye.x -= observer.vision.inclination * cos(observer.vision.angle);
            observer.eye.z += observer.vision.inclination * sin(observer.vision.angle);
            break;
        case GLUT_KEY_LEFT:
            observer.vision.angle += 0.1;
            break;
        case GLUT_KEY_RIGHT:
            observer.vision.angle -= 0.1;
            break;
    }
}

void updateObserver(void) {
    observer.center.x = observer.eye.x + observer.vision.radius * cos(observer.vision.angle);
    observer.center.z = observer.eye.z - observer.vision.radius * sin(observer.vision.angle);
    glutPostRedisplay();
}

void Special(int key, int x, int y) {
    moveObserver(key);
    updateObserver();
}

void Keyboard(unsigned char key, int x, int y) {
    switch (key) {
        //--------------------------- Direccao da Lanterna
        case 's':
        case 'S':
            horizontalInclination = horizontalInclination - 0.05;
            if (horizontalInclination < -MAX_HORIZONTAL_INCLINATION) {
                horizontalInclination = -horizontalInclination;
            }
            updateObserver();
            break;
        case 'd':
        case 'D':
            horizontalInclination = horizontalInclination + 0.05;
            if (horizontalInclination > MAX_HORIZONTAL_INCLINATION) {
                horizontalInclination = MAX_HORIZONTAL_INCLINATION;
            }
            updateObserver();
            break;
        case 'e':
        case 'E':
            verticalInclination = verticalInclination + 0.05;
            if (verticalInclination > MAX_VERTICAL_INCLINATION) {
                verticalInclination = MAX_VERTICAL_INCLINATION;
            }
            updateObserver();
            break;
        case 'c':
        case 'C':
            verticalInclination = verticalInclination - 0.05;
            if (verticalInclination < -MAX_VERTICAL_INCLINATION) {
                verticalInclination = -MAX_VERTICAL_INCLINATION;
            }
            updateObserver();
            break;
            //--------------------------- Escape
        case 27:
            exit(0);
    }
}

GLfloat getVerticalInclination() {
    return verticalInclination;
}

GLfloat getHorizontalInclination() {
    return horizontalInclination;
}