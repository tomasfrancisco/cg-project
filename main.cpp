#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "OpenGL.hpp"
#include "materials.hpp"
#include "textures.hpp"
#include "colors.hpp"
#include "billiardTable.hpp"

//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas
GLfloat  xC=16.0, zC=15.0;
GLint    wScreen=600, hScreen=500;
char     texto[30];
//------------------------------------------------------------ Observador
GLfloat  PI = 3.14159;
GLfloat  rVisao=3.0, aVisao=0.5*PI, incVisao=0.1;
GLfloat  obsPini[] ={4, 6, static_cast<GLfloat>(0.5*xC)};
GLfloat  obsPfin[] ={static_cast<GLfloat>(obsPini[0]-rVisao*cos(aVisao)), obsPini[1], static_cast<GLfloat>(obsPini[2]-rVisao*sin(aVisao))};

//------------------------------------------------------------ Rotacao e Velocidade
GLfloat   velocidades [4]  = {1,2,3,4};
GLfloat   rotacoes [4]= {30,45,60,90};
GLfloat   timer = 1000;
GLfloat   timer2 = 10000;

//Bolas
GLfloat   bola1Pos [3] = {-2, 2, 6};

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

void drawScene() {
    drawAxis();
    //drawRoom();

        //glDisable(GL_COLOR_MATERIAL);
        //glEnable(GL_LIGHTING);
        initLights();



//        glPushMatrix();
//            initMaterials(1);
//            glTranslatef(2, 2, 3);
//            glutSolidSphere(1, 250, 250);
//        glPopMatrix();

        glPushMatrix();
            drawBilliardTable(60, 25);
        glPopMatrix();

        testBarsColision(1, 1);

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

    //================================================================= Mini-Map
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glViewport (wScreen - wScreen/4, 0, wScreen/4, hScreen/4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-xC,xC, -xC,xC, -zC,zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 0, 10,0, 0,0,0, 0, 0, -1);

    //--------------------- Desenha cena
    drawScene();

    //--------------------- Informacao
    glColor3f(0,0,0);
    sprintf(texto, "%d - Noite", noite);
    desenhaTexto(texto,-12,1,-6);
    sprintf(texto, "%d - Tecto", ligaLuz);
    desenhaTexto(texto,-12,1,-9);
    sprintf(texto, "%d - Trans", transp);
    desenhaTexto(texto,-12,1,-12);

    //================================================================= Viewport2
    glEnable(GL_LIGHTING);
    glViewport (0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(99.0, wScreen/hScreen, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);

    //--------------------- Desenha cena
    iluminacao();
    drawScene();

    glutSwapBuffers();
}

void updateVisao(){
    obsPfin[0] =obsPini[0]+rVisao*cos(aVisao);
    obsPfin[2] =obsPini[2]-rVisao*sin(aVisao);
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
            //--------------------------- Space
        case 32:
            obsPini[1]++;
            break;
            //--------------------------- Escape
        case 27:
            exit(0);
            break;
    }
}

void teclasNotAscii(int key, int x, int y) {
    if(key == GLUT_KEY_UP) {
        obsPini[0]=obsPini[0]+incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]-incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_DOWN) {
        obsPini[0]=obsPini[0]-incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]+incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_LEFT) {
        aVisao = (aVisao + 0.1) ;
    }
    if(key == GLUT_KEY_RIGHT) {
        aVisao = (aVisao - 0.1) ;

    }
    updateVisao();
}

void Timer(int value) {
    //bola1Pos[0] = bola1Pos[0] + cos (rotacoes[1]);
    //bola1Pos[2] = bola1Pos[2] + sin (rotacoes[1]);
    if(obsPini[1] >= -4) {
        obsPini[1]--;
    }
    glutPostRedisplay();
    glutTimerFunc(timer, Timer, 1);
}

void Timer2(int value) {
    //rotacoes[1] = rotacoes[1] +10;
    glutPostRedisplay();
    glutTimerFunc(timer, Timer, 1);
}

//======================================================= MAIN
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (400, 100);
    glutCreateWindow ("{(left,right,up,down) - (n,t,g)");

    init();
    glutSpecialFunc(teclasNotAscii);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(timer, Timer, 1);
    glutTimerFunc(timer2, Timer2, 1);

    glutMainLoop();

    return 0;
}
