
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "OpenGL.hpp"
#include "materiais.hpp"
#include "RgbImage.hpp"

//==================================================================== Definir cores
#define AZUL     0.0, 0.0, 1.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0, 1.0
#define AMARELO  1.0, 1.0, 0.0, 1.0
#define VERDE    0.0, 1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY1    0.2, 0.2, 0.2, 1.0
#define GRAY2    0.93, 0.93, 0.93, 1.0


//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas
GLfloat  xC=16.0, zC=15.0;
GLint    wScreen=600, hScreen=500;
char     texto[30];
//------------------------------------------------------------ Observador
GLfloat  PI = 3.14159;
GLfloat  rVisao=3.0, aVisao=0.5*PI, incVisao=0.1;
GLfloat  obsPini[] ={0, 4, static_cast<GLfloat>(0.5*xC)};
GLfloat  obsPfin[] ={static_cast<GLfloat>(obsPini[0]+rVisao*cos(aVisao)), obsPini[1], static_cast<GLfloat>(obsPini[2]+rVisao*sin(aVisao))};

//------------------------------------------------------------ Rotacao e Velocidade

GLfloat   rotacoes [4] = {15,30,45,30};
GLfloat   timer = 10;


//Bolas
GLfloat   bolasPos [4][3]= {{-4 , 2, 6},
                            {-12, 2, 6},
                            {15,  2, -12},
                            {4,   2, 9}};

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

// textures
GLuint      texture[20];
RgbImage    imag;

GLfloat Map[] = { 60.0, 5.0, 30.0 };
GLint transp = 0;

//================================================================================
//=========================================================================== INIT
//================================================================================

void initTextures() {
    //----------------------------------------- Chao
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imag.LoadBmpFile("textures/chao.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());

    //----------------------------------------- Parede
    glGenTextures(1, &texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imag.LoadBmpFile("textures/wall.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
}


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

void initMaterials(int material) {
    switch (material){
        case 0: //esmerald
            glMaterialfv(GL_FRONT,GL_AMBIENT,  esmeraldAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  esmeraldDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, esmeraldSpec);
            glMateriali (GL_FRONT,GL_SHININESS,esmeraldCoef);
            break;
        case 1: //jade
            glMaterialfv(GL_FRONT,GL_AMBIENT,  jadeAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  jadeDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, jadeSpec);
            glMateriali (GL_FRONT,GL_SHININESS,jadeCoef);
            break;
        case 2: //obsidian
            glMaterialfv(GL_FRONT,GL_AMBIENT,  obsidianAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  obsidianDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, obsidianSpec);
            glMateriali (GL_FRONT,GL_SHININESS,obsidianCoef);
            break;
        case 3: //pearl
            glMaterialfv(GL_FRONT,GL_AMBIENT,  pearlAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  pearlDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, pearlSpec);
            glMateriali (GL_FRONT,GL_SHININESS,pearlCoef);
            break;
        case 4: //ruby
            glMaterialfv(GL_FRONT,GL_AMBIENT,  rubyAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  rubyDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, rubySpec);
            glMateriali (GL_FRONT,GL_SHININESS,rubyCoef);
            break;
        case 5: //turquoise
            glMaterialfv(GL_FRONT,GL_AMBIENT,  turquoiseAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  turquoiseDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, turquoiseSpec);
            glMateriali (GL_FRONT,GL_SHININESS,turquoiseCoef);
            break;
        case 6: //brass
            glMaterialfv(GL_FRONT,GL_AMBIENT,  brassAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  brassDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, brassSpec);
            glMateriali (GL_FRONT,GL_SHININESS,brassCoef);
            break;
        case 7: //bronze
            glMaterialfv(GL_FRONT,GL_AMBIENT,  bronzeAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  bronzeDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, bronzeSpec);
            glMateriali (GL_FRONT,GL_SHININESS,bronzeCoef);
            break;
        case 8: //chrome
            glMaterialfv(GL_FRONT,GL_AMBIENT,  chromeAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  chromeDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, chromeSpec);
            glMateriali (GL_FRONT,GL_SHININESS,chromeCoef);
            break;
        case 9: //copper
            glMaterialfv(GL_FRONT,GL_AMBIENT,  copperAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  copperDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, copperSpec);
            glMateriali (GL_FRONT,GL_SHININESS,copperCoef);
            break;
        case 10: //gold
            glMaterialfv(GL_FRONT,GL_AMBIENT,  goldAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  goldDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, goldSpec);
            glMateriali (GL_FRONT,GL_SHININESS,goldCoef);
            break;
        case 11: //silver
            glMaterialfv(GL_FRONT,GL_AMBIENT,  silverAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  silverDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, silverSpec);
            glMateriali (GL_FRONT,GL_SHININESS,silverCoef);
            break;
        case 12: //blackPlastic
            glMaterialfv(GL_FRONT,GL_AMBIENT,  blackPlasticAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  blackPlasticDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, blackPlasticSpec);
            glMateriali (GL_FRONT,GL_SHININESS,blackPlasticCoef);
            break;
        case 13: //cyankPlastic
            glMaterialfv(GL_FRONT,GL_AMBIENT,  cyanPlasticAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  cyanPlasticDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, cyanPlasticSpec);
            glMateriali (GL_FRONT,GL_SHININESS,cyanPlasticCoef);
            break;
        case 14: //greenPlastic
            glMaterialfv(GL_FRONT,GL_AMBIENT,  greenPlasticAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  greenPlasticDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, greenPlasticSpec);
            glMateriali (GL_FRONT,GL_SHININESS,greenPlasticCoef);
            break;
        case 15: //redPlastic
            glMaterialfv(GL_FRONT,GL_AMBIENT,  redPlasticAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  redPlasticDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, redPlasticSpec);
            glMateriali (GL_FRONT,GL_SHININESS,redPlasticCoef);
            break;
        case 16: //yellowPlastic
            glMaterialfv(GL_FRONT,GL_AMBIENT,  whitePlasticAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  whitePlasticDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, whitePlasticSpec);
            glMateriali (GL_FRONT,GL_SHININESS,whitePlasticCoef);
            break;
        case 17: //yellowPlastic
            glMaterialfv(GL_FRONT,GL_AMBIENT,  yellowPlasticAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  yellowPlasticDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, yellowPlasticSpec);
            glMateriali (GL_FRONT,GL_SHININESS,yellowPlasticCoef);
            break;
    }
}

void init(void) {
    glClearColor(WHITE);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

    initTextures();
    initMaterials(1);
    initLights();


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
}

void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z) {
    glDisable(GL_LIGHTING);
    glRasterPos3f(x,y,z);
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}

void drawAxis() {

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
}

void drawRoom() {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chao y=0
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
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
    glBindTexture(GL_TEXTURE_2D, texture[1]);
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
    glBindTexture(GL_TEXTURE_2D, texture[1]);
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
    glBindTexture(GL_TEXTURE_2D, texture[1]);
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
    glBindTexture(GL_TEXTURE_2D, texture[1]);
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
    drawAxis();
    drawRoom();

    if (transp) {

        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);

        initLights();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

        //cyan
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


    glutPostRedisplay();
}



GLvoid resize(GLsizei width, GLsizei height)
{
    wScreen=width;
    hScreen=height;
    drawScene();
}

//======================================================================== ILUMINCCAO
void iluminacao(){

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
    gluLookAt(  obsPini[0], obsPini[1], obsPini[2] , obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);


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
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f (0., 0., 0., 0.11);
    drawMirror();

    glDisable (GL_BLEND);

    iluminacao();
    drawScene();

    //drawCeiling();
    //================================================================= Viewport2

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glViewport (wScreen - wScreen/4, 0, wScreen/4, hScreen/4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-xC,xC, -xC,xC, -zC,zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( obsPini[0], obsPini[1] + 10, obsPini[2], obsPini[0], obsPini[1], obsPini[2],  (obsPfin[0] - obsPini[0]), obsPini[1], (obsPfin[2] - obsPini[2]));

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
    obsPfin[0] =obsPini[0]+rVisao*cos(aVisao);
    obsPfin[2] =obsPini[2]+rVisao*sin(aVisao);
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

        case 'w':
        case 'W':
            obsPfin[1] += 1;
            break;

        case 's':
        case 'S':
            obsPfin[1] -= 1;
            break;
            //--------------------------- Escape
        case 27:
            exit(0);
            break;

    }
}

void teclasNotAscii(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
        obsPini[0]=obsPini[0]+incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]+incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_DOWN) {
        obsPini[0]=obsPini[0]-incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]-incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_LEFT) {
        aVisao = (aVisao - 0.1) ;
    }
    if(key == GLUT_KEY_RIGHT) {
        aVisao = (aVisao + 0.1) ;

    }
    updateVisao();
}

void Timer(int value)
{

    for (int i=0; i<4; i++)
    {
        if ((obsPini[0] >= bolasPos[i][0] -1 && obsPini[0] <= bolasPos[i][0] +1) && (obsPini[2] >= bolasPos[i][2] -1 && obsPini[2] <= bolasPos[i][2] +1) )
            exit(0);

        if (bolasPos[i][0] < 28 && bolasPos[i][0] > -28)
            bolasPos[i][0] += cos (rotacoes[i])/2;
        else
        {
            bolasPos[i][0] -= cos (rotacoes[i])/2;
            rotacoes[i] = PI- rotacoes[i];
        }


        if (bolasPos[i][2] < 13 && bolasPos[i][2] > -13)
            bolasPos[i][2] += sin (rotacoes[i])/2;
        else
        {
            bolasPos[i][2] -= sin (rotacoes[i])/2;
            rotacoes[i] = -rotacoes[i];
        }
    }

    glutPostRedisplay();
    glutTimerFunc(timer, Timer, 1);
}


//======================================================= MAIN
int main(int argc, char** argv){


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
