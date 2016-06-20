//
// Created by Tomás Francisco on 19/06/16.
//

#include "billiardTable.hpp"

void drawTableBar(GLint width, GLint height, GLint depth) {
    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_WOOD));

    glDisable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_LIGHTING);

    glEnable(GL_CULL_FACE);

    glPushMatrix();

        //front
        glDisable(GL_TEXTURE_2D);
        initMaterials(MATERIAL_GREEN_RUBBER);

        glPushMatrix();
            glTranslatef(0.0f, height, depth);
            glRotatef(90, 1, 0, 0);
            drawSquareMesh(width, height, false);
        glPopMatrix();

        glEnable(GL_TEXTURE_2D);
        initMaterials(MATERIAL_GOLD);

        //bottom
        glPushMatrix();
            glTranslatef(width, 0.0f, 0.0f);
            glRotatef(180, 0, 0, 1);
            drawSquareMesh(width, depth, true);
        glPopMatrix();

        //top
        glPushMatrix();
            glTranslatef(0.0f, height, 0.0f);
            drawSquareMesh(width, depth, true);
        glPopMatrix();

        //back
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            drawSquareMesh(width, height, true);
        glPopMatrix();

        //left
        glPushMatrix();
            glRotatef(90, 0, 0, 1);
            drawSquareMesh(height, depth, true);
        glPopMatrix();

        //right plane
        glPushMatrix();
            glTranslatef(width, height, 0);
            glRotatef(-90, 0, 0, 1);
            drawSquareMesh(height, depth, true);
        glPopMatrix();
    glPopMatrix();

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}

void drawTableBars(GLint width, GLint height, GLint depth, GLint altitude) {
    glPushMatrix();
        //back
        glPushMatrix();
            drawTableBar(width, altitude, depth);
        glPopMatrix();

        //left
        glPushMatrix();
            glTranslatef(0, 0, height);
            glRotatef(90, 0, 1, 0);

            drawTableBar(height, altitude, depth);
        glPopMatrix();

        //right
        glPushMatrix();
            glTranslatef(width, 0, 0);
            glRotatef(-90, 0, 1, 0);

            drawTableBar(height, altitude, depth);
        glPopMatrix();

        //front
        glPushMatrix();
            glTranslatef(0, altitude, height);
            glRotatef(180, 1, 0, 0);

            drawTableBar(width, altitude, depth);
        glPopMatrix();
    glPopMatrix();
}

void drawTableCamp(GLint width, GLint height, GLint depth) {
    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_WOOD));

    glDisable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_LIGHTING);

    glEnable(GL_CULL_FACE);

    glPushMatrix();
        //top
        glPushMatrix();
            initMaterials(MATERIAL_GREEN_RUBBER);

            glTranslatef(0.0, depth, 0.0);
            drawSquareMesh(width, height, false);
        glPopMatrix();

        glEnable(GL_TEXTURE_2D);
        initMaterials(MATERIAL_GOLD);

        //bottom
        glPushMatrix();
            glCullFace(GL_FRONT);

            drawSquareMesh(width, height, true);

            glCullFace(GL_BACK);
        glPopMatrix();

        //left
        glPushMatrix();
            glRotatef(90, 0, 0, 1);
            drawSquareMesh(depth, height, true);
        glPopMatrix();


        //right
        glPushMatrix();
            glTranslatef(width, depth, 0);
            glRotatef(-90, 0, 0, 1);
            drawSquareMesh(depth, height, true);
        glPopMatrix();

        //back
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            drawSquareMesh(width, depth, true);
        glPopMatrix();

        //front
        glPushMatrix();
            glTranslatef(0, depth, height);
            glRotatef(90, 1, 0, 0);
            drawSquareMesh(width, depth, true);
        glPopMatrix();

    glPopMatrix();

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}

void drawBillardTable(GLint width, GLint height) {
    glPushMatrix();
        glTranslatef(-(width / 2), 0, -(height / 2));
        glPushMatrix();
            drawTableBars(width, height, 1, 3);
            glTranslatef(1, 0.0, 1);
            drawTableCamp(width - 2, height - 2, 1);
        glPopMatrix();
    glPopMatrix();
}