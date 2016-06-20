//
// Created by Tomás Francisco on 20/06/16.
//

#include "roomWindow.hpp"

void drawWindowBar(GLint width, GLint height, GLint depth) {
    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_WOOD));

    glDisable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_LIGHTING);

    //glEnable(GL_CULL_FACE);

    glPushMatrix();

    //front
    glEnable(GL_TEXTURE_2D);
    initMaterials(MATERIAL_GOLD);

    glPushMatrix();
    glTranslatef(0.0f, height, depth);
    glRotatef(90, 1, 0, 0);
    drawSquareMesh(width, height);
    glPopMatrix();

    //bottom
    glPushMatrix();
    glTranslatef(width, 0.0f, 0.0f);
    glRotatef(180, 0, 0, 1);
    drawSquareMesh(width, depth);
    glPopMatrix();

    //top
    glPushMatrix();
    glTranslatef(0.0f, height, 0.0f);
    drawSquareMesh(width, depth);
    glPopMatrix();

    //back
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    drawSquareMesh(width, height);
    glPopMatrix();

    //left
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    drawSquareMesh(height, depth);
    glPopMatrix();

    //right plane
    glPushMatrix();
    glTranslatef(width, height, 0);
    glRotatef(-90, 0, 0, 1);
    drawSquareMesh(height, depth);
    glPopMatrix();
    glPopMatrix();

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}

void drawWindowBars(GLint width, GLint height, GLint depth, GLint altitude) {
    glPushMatrix();
        //back
        glPushMatrix();
            drawWindowBar(width, altitude, depth);
        glPopMatrix();

        //left
        glPushMatrix();
            glTranslatef(0, 0, height);
            glRotatef(90, 0, 1, 0);

            drawWindowBar(height, altitude, depth);
        glPopMatrix();

        //right
        glPushMatrix();
            glTranslatef(width, 0, 0);
            glRotatef(-90, 0, 1, 0);

            drawWindowBar(height, altitude, depth);
        glPopMatrix();

        //front
        glPushMatrix();
            glTranslatef(0, altitude, height);
            glRotatef(180, 1, 0, 0);

            drawWindowBar(width, altitude, depth);
        glPopMatrix();

        //center
        glPushMatrix();
            glTranslatef(width / 2, 0, 0);
            glRotatef(-90, 0, 1, 0);
            drawWindowBar(height, altitude, depth);
        glPopMatrix();

        //middle
        glPushMatrix();
            glTranslatef(0, altitude, (height / 2) - 2);
            glRotatef(180, 1, 0, 0);

            drawWindowBar(width, altitude, depth);
        glPopMatrix();

        //middle
        glPushMatrix();
            glTranslatef(0, altitude, (height / 2) + 3);
            glRotatef(180, 1, 0, 0);

            drawWindowBar(width, altitude, depth);
            glPopMatrix();
    glPopMatrix();
}

void drawTableBack(GLint width, GLint height, GLint depth, GLboolean isNight) {
    if(isNight) {
        glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_NIGHT));
    } else {
        glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_DAY));
    }

    glDisable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_LIGHTING);

    //glEnable(GL_CULL_FACE);

    glPushMatrix();
    //top
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    initMaterials(MATERIAL_PEARL);


    glTranslatef(0.0, depth, 0.0);
    drawSquareMesh(width, height);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_WOOD));

    //bottom
    glPushMatrix();
    glCullFace(GL_FRONT);

    drawSquareMesh(width, height);

    glCullFace(GL_BACK);
    glPopMatrix();

    //left
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    drawSquareMesh(depth, height);
    glPopMatrix();


    //right
    glPushMatrix();
    glTranslatef(width, depth, 0);
    glRotatef(-90, 0, 0, 1);
    drawSquareMesh(depth, height);
    glPopMatrix();

    //back
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    drawSquareMesh(width, depth);
    glPopMatrix();

    //front
    glPushMatrix();
    glTranslatef(0, depth, height);
    glRotatef(90, 1, 0, 0);
    drawSquareMesh(width, depth);
    glPopMatrix();

    glPopMatrix();

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
}

void drawWindow(GLint width, GLint height, GLboolean isNight) {
    GLint   depth = 1,
            altitude = 2;

    GLdouble xSize = ((GLdouble) width / 2);
    GLdouble ySize = ((GLdouble) height / 2);

    glPushMatrix();
        glTranslatef(-xSize, 0, -ySize);
        glPushMatrix();
            drawWindowBars(width, height, depth, altitude);
            glTranslatef(depth, 0.0, depth);
            drawTableBack(width - 2, height - 2, depth, isNight);
        glPopMatrix();
    glPopMatrix();
}