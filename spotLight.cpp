//
// Created by Tomás Francisco on 20/06/16.
//

#include "spotLight.hpp"


void drawSpotLight(GLint radius, GLboolean isNight) {
    GLfloat anguloFoco = 10.0;        //.. angulo inicial do foco

    GLfloat Pos2[] = {0.0f, 0.0, 30.0f, 1.0f};

    GLfloat Foco_direccao[] = {0, 1, -1};    //=== -Z
    GLfloat Foco2_cor[] = {1, 1, 1, 1};    //=== Cor da luz 2
    GLfloat Foco_ak = 1.0;
    GLfloat Foco_al = 0.05f;
    GLfloat Foco_aq = 0.0f;
    GLfloat Foco_Expon = 2.0;        // Foco, SPOT_Exponent

    if(isNight) {

        Foco2_cor[0] = 0;
        Foco2_cor[1] = 0.8;
        Foco2_cor[2] = 0.8;
    }

        //=================================================================Foco Direita
        glLightfv(GL_LIGHT1, GL_POSITION, Pos2);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco2_cor);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Foco_ak);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Foco_al);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Foco_aq);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, anguloFoco);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon);

}


