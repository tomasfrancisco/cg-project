#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "OpenGL.hpp"
#include "materials.hpp"
#include "textures.hpp"
#include "colors.hpp"
#include "billiardTable.hpp"

#define PI 3.14159

#define X 0
#define Y 1
#define Z 2

#define RADIUS 0
#define ANGLE 1
#define INCLINATION 2

//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas
GLfloat  xC=16.0, zC=15.0;
GLint    wScreen=600, hScreen=500;
char     texto[30];
//------------------------------------------------------------ Observador
struct Observer {
    GLdouble    position[3],
                lookAt[3],
                upVector[3],
                vision[3];
};
Observer observer;

void initObserver() {
    observer.vision[RADIUS]         = 3.0;
    observer.vision[ANGLE]          = 0.5 * PI;
    observer.vision[INCLINATION]    = 0.1;

    observer.position[X]            = 0;
    observer.position[Y]            = 4;
    observer.position[Z]            = 0.5 * xC;

    observer.lookAt[X]              = observer.position[X] + observer.vision[RADIUS] * cos(observer.vision[ANGLE]);
    observer.lookAt[Y]              = observer.position[Y];
    observer.lookAt[Z]              = observer.position[Z] + observer.vision[RADIUS] * sin(observer.vision[ANGLE]);

    observer.upVector[X]            = 0;
    observer.upVector[Y]            = 1;
    observer.upVector[Z]            = 0;
}

//GLfloat  rVisao=3.0, aVisao=0.5*PI, incVisao=0.1;
//
//GLdouble obsPini[] ={0, 4, static_cast<GLfloat>(0.5*xC)};
//GLdouble  obsPfin[] ={static_cast<GLfloat>(obsPini[0]+rVisao*cos(aVisao)), obsPini[1], static_cast<GLfloat>(obsPini[2]+rVisao*sin(aVisao))};

//------------------------------------------------------------ Rotacao e Velocidade

GLdouble  rotacoes [4] = {15,30,45,30};
GLfloat   timer = 10;


//Bolas
GLdouble  bolasPos [4][3]= {{-4 , 2, 6},
                            {-10, 2, 6},
                            {15,  2, -7.5},
                            {4,   2, -7.5}};

//------------------------------------------------------------ Iluminacao
//------------------------------------------------------------ Global (ambiente)

GLint   noite=0;
GLfloat luzGlobalCor[4]={1.0,1.0,1.0,1.0};   // 
//Lampada tecto (ambiente local)

GLint   ligaLuz=1;
GLfloat localCor[4] ={0.1,0.1,0.1,1.0};
GLfloat localCorDif[4] ={ 1, 1, 1, 1.0};
GLfloat localPos[4] ={xC/2, 10.0, xC/2, 1.0};
GLfloat localAttCon =1.0;
GLfloat localAttLin =0.05;
GLfloat localAttQua =0.0;



GLfloat Map[] = { 60.0, 5.0, 30.0 };
GLint transp = 0;

void initLights(void){
    //Ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
    //Tecto
    glLightfv(GL_LIGHT0, GL_POSITION,      localPos );
    glLightfv(GL_LIGHT0, GL_AMBIENT,       localCor );
    glLightfv(GL_LIGHT0, GL_DIFFUSE,       localCorDif );
    glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, localAttCon);
    glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION,   localAttLin) ;
    glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION,localAttQua) ;
}

void init(void) {
    glClearColor(WHITE);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

    initObserver();

    initTextures();
    initMaterials(MATERIAL_ESMERALD);
    initLights();


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_NORMALIZE);
}

void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z) {
    glDisable(GL_LIGHTING);
    glRasterPos3f(x,y,z);
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}

void drawAxis() {
    glPushMatrix();
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    //Eixo dos zz
    glColor4f(AZUL);
    glBegin(GL_LINES);
    glVertex3i(0,0,-xC);
    glVertex3i(0,0, xC);
    glEnd();

    //Eixo dos yy
    glColor4f(VERDE);
    glBegin(GL_LINE);
    glVertex3i(0,-xC,0);
    glVertex3i(0,xC,0);
    glEnd();

    //Eixo dos xx
    glColor4f(VERMELHO);
    glBegin(GL_LINES);
    glVertex3i(-xC,0,0);
    glVertex3i( xC,0,0);
    glEnd();
    glPopMatrix();
}

void drawRoom() {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chao y=0
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_CAMP_FLOOR));
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3i(-Map[0] / 2, 0, Map[2] / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3i(Map[0] / 2, 0, Map[2] / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3i(Map[0] / 2, 0, -Map[2] / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3i(-Map[0] / 2, 0, -Map[2] / 2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Paredes X

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_CAMP_WALL));
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3i(-Map[0] / 2, 0, Map[2] / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3i(-Map[0] / 2, Map[1], Map[2] / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3i(-Map[0] / 2, Map[1], -Map[2] / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3i(-Map[0] / 2, 0, -Map[2] / 2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_CAMP_WALL));
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3i(Map[0] / 2, 0, Map[2] / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3i(Map[0] / 2, Map[1], Map[2] / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3i(Map[0] / 2, Map[1], -Map[2] / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3i(Map[0] / 2, 0, -Map[2] / 2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Paredes Z

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_CAMP_WALL));
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3i(-Map[0] / 2, 0, -Map[2] / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3i(Map[0] / 2, 0, -Map[2] / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3i(Map[0] / 2, Map[1], -Map[2] / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3i(-Map[0] / 2, Map[1], -Map[2] / 2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_CAMP_WALL));
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3i(-Map[0] / 2, 0, Map[2] / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3i(Map[0] / 2, 0, Map[2] / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3i(Map[0] / 2, Map[1], Map[2] / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3i(-Map[0] / 2, Map[1], Map[2] / 2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawMirror()
{
    glBegin (GL_QUADS);
    glVertex3f (-Map[0]/4, 15, Map[2]/4);
    glVertex3f (-Map[0]/4, 15, -Map[2]/4);
    glVertex3f (Map[0]/4, 15, -Map[2]/4);
    glVertex3f (Map[0]/4, 15, Map[2]/4);
    glEnd();

}

void drawScene() {
    //glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BITS);
    drawAxis();

    drawBilliardTable(60, 20);

    if (transp) {

        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);

        //glDisable(GL_COLOR_MATERIAL);
        //glEnable(GL_LIGHTING);
        initLights();

        //black
        glPushMatrix();
        initMaterials(2);
        glTranslatef(bolasPos[0][0], bolasPos[0][1], bolasPos[0][2]);
        //glRotatef(rotacoes[1],1,0,0);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        //white
        glPushMatrix();
        initMaterials(3);
        glTranslatef(bolasPos[1][0], bolasPos[1][1], bolasPos[1][2]);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        //red
        glPushMatrix();
        initMaterials(4);
        glTranslatef(bolasPos[2][0], bolasPos[2][1], bolasPos[2][2]);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        glPushMatrix();

        initMaterials(5);
        glTranslatef(bolasPos[3][0], bolasPos[3][1], bolasPos[3][2]);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        glDisable(GL_BLEND);

    }else
    {
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
        initLights();

        //black
        glPushMatrix();
        initMaterials(2);
        glTranslatef(bolasPos[0][0], bolasPos[0][1], bolasPos[0][2]);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        //white
        glPushMatrix();
        initMaterials(3);
        glTranslatef(bolasPos[1][0], bolasPos[1][1], bolasPos[1][2]);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        //red
        glPushMatrix();
        initMaterials(4);
        glTranslatef(bolasPos[2][0], bolasPos[2][1], bolasPos[2][2]);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        //cyan
        glPushMatrix();
        initMaterials(5);
        glTranslatef(bolasPos[3][0], bolasPos[3][1], bolasPos[3][2]);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();
    }

//        glPushMatrix();
//            initMaterials(MATERIAL_GREEN_RUBBER);
//            drawSquareMesh(5.0f, 5.0f, 10, false);
//        glPopMatrix();

    glutPostRedisplay();
}

GLvoid resize(GLsizei width, GLsizei height) {
    wScreen = width;
    hScreen = height;
    drawScene();
}

void iluminacao() {
    if (ligaLuz)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);
}

void display(void){
    if (noite)
        glClearColor(GRAY1);
    else
        glClearColor(GRAY2);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    //================================================================= Viewport1
    glEnable(GL_LIGHTING);
    glViewport (0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(99.0, wScreen/hScreen, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(  observer.position[X], observer.position[Y], observer.position[Z],
                observer.lookAt[X], observer.lookAt[Y], observer.lookAt[Z],
                observer.upVector[X], observer.upVector[Y], observer.upVector[Z]);


    glColorMask(0, 0, 0, 0);
    glDisable(GL_DEPTH_TEST);

    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 1);

    glEnable(GL_STENCIL_TEST);

    glColorMask(1, 1, 1, 1);
    drawMirror();
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glColorMask(1, 1, 1, 1);

    glEnable(GL_DEPTH_TEST);

    //Desenha a cena refletida
    glPushMatrix();
        glScalef(1, -1, 1);
        glTranslated(0,-24,0);
        iluminacao();
        drawScene();
    glPopMatrix();

    glDisable(GL_STENCIL_TEST);

    // desenha o espelho transparente
    glClear(GL_STENCIL_BUFFER_BIT);
    glEnable (GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f (0., 0., 0., 0.11);
    drawMirror();

    glDisable (GL_BLEND);

    iluminacao();
    drawScene();

    //drawCeiling();
    //================================================================= Viewport2


    glViewport (wScreen - wScreen/4, 0, wScreen/4, hScreen/4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-xC,xC, -xC,xC, -zC,zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // TODO: Review this up vector (There's something weird happening here)
    gluLookAt( observer.position[X], observer.position[Y] + 10, observer.position[Z],
               observer.lookAt[X], observer.lookAt[Y], observer.lookAt[Z],
               observer.lookAt[X] - observer.position[X], observer.position[Y], observer.lookAt[Z] - observer.position[Z]);

    //--------------------- desenha objectos

    drawScene();

    //================================================================= Viewport3

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glViewport (wScreen - wScreen/4, 0, wScreen/4, hScreen/4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-xC,xC, -xC,xC, -zC,zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,  10, 0,0, 0,0, 0, 0, -1);


    //--------------------- Informacao
    glColor3f(0,0,0);
    sprintf(texto, "%d - Noite", noite);
    desenhaTexto(texto,-12 ,  + 1 ,- 6);
    sprintf(texto, "%d - Tecto", ligaLuz);
    desenhaTexto(texto,-12 , 1 ,  - 9);
    sprintf(texto, "%d - Trans", transp);
    desenhaTexto(texto,-12 ,1 ,  - 12);

    glutSwapBuffers();
}

void updateVisao(){
    observer.lookAt[X] = observer.position[X] + observer.vision[RADIUS] * cos(observer.vision[ANGLE]);
    observer.lookAt[Z] = observer.position[Z] + observer.vision[RADIUS] * sin(observer.vision[ANGLE]);
    glutPostRedisplay();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){
    switch (key) {
            //--------------------------- Dia/noite
        case 'n':
        case 'N':
            noite=!noite;
            if (noite)
            { luzGlobalCor[0]=0.6;   luzGlobalCor[1]=0.6;   luzGlobalCor[2]=0.6; }
            else
            { luzGlobalCor[0]=0.3;   luzGlobalCor[1]=0.3;   luzGlobalCor[2]=0.3; }
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
            glutPostRedisplay();
            break;
            //--------------------------- Iluminacaoda sala
        case 't':
        case 'T':
            ligaLuz=!ligaLuz;
            glutPostRedisplay();
            break;

        case 'g':
        case 'G':
            transp = !transp;
            glutPostRedisplay();
            break;
        case 'e':
            observer.position[Y] += 1;
            break;
        case 'd':
            observer.position[Y] -= 1;
            break;
        case 'w':
        case 'W':
            observer.lookAt[Y] += 1;
            break;

        case 's':
        case 'S':
            observer.lookAt[Y] -= 1;
            break;
            //--------------------------- Escape
        case 27:
            exit(0);
            break;
    }
}

void teclasNotAscii(int key, int x, int y) {
    if(key == GLUT_KEY_UP) {
        observer.position[X] = observer.position[X] + observer.vision[INCLINATION] * cos(observer.vision[ANGLE]);
        observer.position[Z] = observer.position[Z] + observer.vision[INCLINATION] * sin(observer.vision[ANGLE]);
    }
    if(key == GLUT_KEY_DOWN) {
        observer.position[X] = observer.position[X] - observer.vision[INCLINATION] * cos(observer.vision[ANGLE]);
        observer.position[Z] = observer.position[Z] - observer.vision[INCLINATION] * sin(observer.vision[ANGLE]);
    }
    if(key == GLUT_KEY_LEFT) {
        observer.vision[ANGLE] = (observer.vision[ANGLE] - 0.1) ;
    }
    if(key == GLUT_KEY_RIGHT) {
        observer.vision[ANGLE] = (observer.vision[ANGLE] + 0.1) ;

    }
    updateVisao();
}


void Timer(int value) {
    for(int i = 0; i < 4; i++) {
        runColisionWithBalls(&bolasPos[i][0], &bolasPos[i][2], &rotacoes[i], 1.0);
        for(int j = i + 1; j < 4; j++) {

        }
    }


    glutPostRedisplay();
    glutTimerFunc(timer, Timer, 1);
}


//======================================================= MAIN
int main(int argc, char** argv) {


    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (400, 100);
    glutCreateWindow ("{(left,right,up,down) - (n,t,g)");

    init();
    glutSpecialFunc(teclasNotAscii);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(timer, Timer, 1);

    glutMainLoop();

    return 0;
}
