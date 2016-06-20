//
// Created by Tomás Francisco on 19/06/16.
//

#include "primitives.hpp"

void drawSquareMesh(GLint width, GLint height) {
    GLfloat widthStep = 1.0f / width;
    GLfloat heightStep = 1.0f / height;

    glPushMatrix();
        glBegin(GL_QUADS);
        for(GLint line = 0; line < height; line += 1) {
            for(GLint column = 0; column < width && column >= 0; column += 1) {
                // (0,0)
                glTexCoord2f(column * widthStep, line * heightStep);
                glNormal3f(0.0, 1.0, 0.0);
                glVertex3d( column, 0.0f, line);            //vertex 1
                // (0,1)
                glTexCoord2f(column * widthStep, (line + 1) * heightStep);
                glNormal3f(0.0, 1.0, 0.0);
                glVertex3d( column, 0.0f, line + 1 );       //vertex 2
                // (1,1)
                glTexCoord2f((column + 1) * widthStep, (line + 1) * heightStep);
                glNormal3f(0.0, 1.0, 0.0);
                glVertex3d( column + 1, 0.0f, line + 1 );   //vertex 3
                // (1,0)
                glTexCoord2f((column + 1) * widthStep, line * heightStep);
                glNormal3f(0.0, 1.0, 0.0);
                glVertex3d( column + 1, 0.0f, line );       //vertex 4
            }
        }
        glEnd();
    glPopMatrix();
}

void drawCube(GLint width, GLint height, GLint depth) {
    glPushMatrix();
    //bottom plane
    drawSquareMesh(width, depth);
    //top plane
    glPushMatrix();
    glTranslatef(0.0f, height, 0.0f);
    drawSquareMesh(width, depth);
    glPopMatrix();
    //back plane
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    drawSquareMesh(width, height);
    glPopMatrix();
    //front plane
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, depth);
    glRotatef(-90, 1, 0, 0);
    drawSquareMesh(width, height);
    glPopMatrix();
    //left plane
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    drawSquareMesh(height, depth);
    glPopMatrix();
    //right plane
    glPushMatrix();
    glTranslatef(width, 0, 0);
    glRotatef(90, 0, 0, 1);
    drawSquareMesh(height, depth);
    glPopMatrix();
    glPopMatrix();
}

void drawLight(GLint radius) {
    glPushMatrix();

    glPopMatrix();
}