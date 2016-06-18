
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "OpenGL.hpp"
#include "materiais.hpp"

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
GLfloat  obsPini[] ={0, 0, static_cast<GLfloat>(0.5*xC)};
GLfloat  obsPfin[] ={static_cast<GLfloat>(obsPini[0]-rVisao*cos(aVisao)), obsPini[1], static_cast<GLfloat>(obsPini[2]-rVisao*sin(aVisao))};

//------------------------------------------------------------ Texturas e Rotacao
GLfloat   quadS   = 4.0;
GLfloat   quadP[] = {-2, 0, -8};

//------------------------------------------------------------ NOVO - Nevoeiro
GLfloat nevoeiroCor[] = {0.75, 0.75, 0.75, 1.0}; //definicao da cor do nevoeiro


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

//Lanterna (local)
GLint   ligaFoco  = 0;
GLfloat rFoco=1.1, aFoco=aVisao;
GLfloat incH =0.0, incV=0.0;
GLfloat incMaxH =0.5, incMaxV=0.35;
GLfloat focoPini[]= { obsPini[0], obsPini[1], obsPini[2], 1.0 };
GLfloat focoPfin[]={ static_cast<GLfloat>(obsPini[0]-rFoco*cos(aFoco)), obsPini[1], static_cast<GLfloat>(obsPini[2]-rFoco*sin(aFoco)), 1.0};
GLfloat focoDir[] = { focoPfin[0]-focoPini[0], 0, focoPfin[2]-focoPini[2]};
GLfloat focoExp   = 10.0;
GLfloat focoCut   = 15.0;

GLfloat focoCorEsp[4] ={ 1.0 ,  1.0, 1.0, 1.0};
GLfloat focoCorDif[4] ={ 0.85, 0.85,0.85, 1.0};

//Materiais
GLint   colorM=0;
GLfloat matAmbiente[] = {1.0,1.0,1.0,1.0};
GLfloat matDifusa[]   = {1.0,1.0,1.0,1.0};
GLfloat matEspecular[]= {1.0, 1.0, 1.0, 1.0};
GLint   especMaterial = 20;
GLint   material = 1;
GLint   material1 = 5;
GLint   material2 = 18;
GLint   material3 = 9;
GLint   material4 = 4;




GLfloat x = 0;
GLfloat y = 0;

GLfloat width = 20;
GLfloat height = 20;

GLint dim = 64;
//================================================================================
//=========================================================================== INIT
//================================================================================

void MenuMaterial(int op)
{
    material=op-1;

    material1=material+1; if (material1>23) material1=0;
    material2=material1+1; if (material2>23) material2=0;
    material3=material2+1; if (material3>23) material3=0;
    material4=material3+1; if (material4>23) material4=0;


    /*switch(op) {
     case 0:
     break;
     case 1:
     break;
     case 2:
     break;
     }*/
    glutPostRedisplay();
}
void MenuPrincipal(int op)
{
}

void CriaMenu()
{

    int menu,submenu1,submenu2;

    submenu1 = glutCreateMenu(MenuMaterial);
    glutAddMenuEntry(" 1 ",1);
    glutAddMenuEntry(" 2",2);
    glutAddMenuEntry(" 3",3);
    glutAddMenuEntry(" 4",4);
    glutAddMenuEntry(" 5",5);
    glutAddMenuEntry(" 6",6);
    glutAddMenuEntry(" 7",7);
    glutAddMenuEntry(" 8",8);
    glutAddMenuEntry(" 9",9);
    glutAddMenuEntry(" 10",10);
    glutAddMenuEntry(" gold",11);
    glutAddMenuEntry(" silver",12);
    glutAddMenuEntry(" black plastic",13);
    glutAddMenuEntry(" cyan plastic",14);
    glutAddMenuEntry(" green plastic",15);
    glutAddMenuEntry(" red plastic",16);
    glutAddMenuEntry(" white plastic",17);
    glutAddMenuEntry(" yellow plastic",18);
    glutAddMenuEntry(" black rubber",19);
    glutAddMenuEntry(" cyan rubber",20);
    glutAddMenuEntry(" green rubber",21);
    glutAddMenuEntry(" red rubber",22);
    glutAddMenuEntry(" white rubber",23);
    glutAddMenuEntry(" yellow rubber ",24);


    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Material",submenu1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void gestaoRato(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
    if (state == GLUT_DOWN)
        CriaMenu();

    glutPostRedisplay();
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
    //Foco
    glLightfv(GL_LIGHT1, GL_POSITION,      focoPini );
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,focoDir );
    glLightf (GL_LIGHT1, GL_SPOT_EXPONENT ,focoExp);
    glLightf (GL_LIGHT1, GL_SPOT_CUTOFF,   focoCut);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,       focoCorDif );
    glLightfv(GL_LIGHT1, GL_SPECULAR,      focoCorEsp  );
}

void initMaterials(int material)
{
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
        case 18: //blackRubber
            glMaterialfv(GL_FRONT,GL_AMBIENT,  blackRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  blackRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, blackRubberSpec);
            glMateriali (GL_FRONT,GL_SHININESS,blackRubberCoef);
            break;
        case 19: //cyanRubber
            glMaterialfv(GL_FRONT,GL_AMBIENT,  cyanRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  cyanRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, cyanRubberSpec);
            glMateriali (GL_FRONT,GL_SHININESS,cyanRubberCoef);
            break;
        case 20: //greenRubber

            glMaterialfv(GL_FRONT,GL_AMBIENT,  greenRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  greenRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, greenRubberSpec);
            glMateriali (GL_FRONT,GL_SHININESS,greenRubberCoef);
            break;
        case 21: //redRubber
            glMaterialfv(GL_FRONT,GL_AMBIENT,  redRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  redRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, redRubberSpec);
            glMateriali (GL_FRONT,GL_SHININESS,redRubberCoef);
            break;
        case 22: //redRubber
            glMaterialfv(GL_FRONT,GL_AMBIENT,  whiteRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  whiteRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, whiteRubberSpec);
            glMateriali (GL_FRONT,GL_SHININESS,whiteRubberCoef);
            break;
        case 23: //redRubber
            glMaterialfv(GL_FRONT,GL_AMBIENT,  yellowRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  yellowRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, yellowRubberSpec);
            glMateriali (GL_FRONT,GL_SHININESS,yellowRubberCoef);
            break;
    }


}


//--------------------- NOVO - Definicoes do nevoeiro
void initNevoeiro(void){
    glFogfv(GL_FOG_COLOR, nevoeiroCor); //Cor do nevoeiro
    glFogi(GL_FOG_MODE, GL_LINEAR); //Equa��o do nevoeiro - linear
    glFogf(GL_FOG_START, 1.0); // Dist�ncia a que ter� in�cio o nevoeiro
    glFogf(GL_FOG_END, 5.0); // Dist�ncia a que o nevoeiro terminar�
    //glFogf (GL_FOG_DENSITY, 0.35); //Densidade do nevoeiro - n�o se especifica quando temos "nevoeiro linear"


}
void init(void)
{
    glClearColor(WHITE);
    glShadeModel(GL_SMOOTH);

    //NOVO - Activa o nevoeiro
    glEnable(GL_FOG);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

    initMaterials(1);
    initLights();
    //NOVO
    initNevoeiro();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
}


//================================================================================
//======================================================================== DISPLAY
void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z)
{
    glRasterPos3f(x,y,z);
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}




void drawScene(){



    //============================================Eixos
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

    //============================================ COloR MATERIAL
    if (colorM==1)
    {
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
        glEnable(GL_LIGHTING);

        glPushMatrix();
        glColor4f(AZUL);
        glTranslatef (-1.2, 0.0, 6.2);
        glutSolidSphere(1.2, 250, 250);
        glPopMatrix();
        glColor4f(LARANJA);
        glPushMatrix();
        glTranslatef (2.7, 0.0, 2.4);
        glutSolidTorus(0.45,1.2,100,100);
        glPopMatrix();
        glColor4f(VERMELHO);
        glPushMatrix();
        glTranslatef (-2.0, 0.0, -2.7);
        glRotatef (45, 1.0, 1.0,0);
        glRotatef(-90, 1, 0,0);
        glutSolidTorus(0.45,1.2,100,100);
        glPopMatrix();
        glColor4f(VERDE);
        glPushMatrix();
        glTranslatef (0.5, 0.0, 0.5);
        glRotatef (-90,1, 0.0, 0.1);
        glutSolidCone(1,4, 200,200);
        glPopMatrix();





        //NOVO: Poligono
        //Definicao da normal ao poligono. Necessario em modo colorMaterial.
        glColor4f(AZUL);

        glPushMatrix();
        glTranslatef(-1,-1,0);
        glBegin(GL_QUADS);

        glNormal3f(0,0,1);
        glVertex3d(0,0,0);

        glVertex3d(1,0,0);

        glVertex3d(1,1,0);

        glVertex3d(0,1,0);


        glEnd();
        glPopMatrix();
    }
    else  //================================= colorM=0
    {
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);


        initLights();
        initMaterials(material);
        glPushMatrix();
        glColor4f(AZUL);
        glTranslatef (-1.2, 0.0, 6.2);
        glutSolidSphere(1.2, 250, 250);
        glPopMatrix();

        initMaterials(material1);
        glPushMatrix();
        glTranslatef (2.7, 0.0, 2.4);
        glutSolidTorus(0.45,1.2,100,100);
        glPopMatrix();

        initMaterials(material2);
        glPushMatrix();
        glTranslatef (-2.0, 0.0, -2.7);
        glRotatef (45, 1.0, 1.0,0);
        glRotatef(-90, 1, 0,0);
        glutSolidTorus(0.45,1.2,100,100);
        glPopMatrix();

        initMaterials(material3);
        glPushMatrix();
        glTranslatef (0.5, 0.0, 0.5);
        glRotatef (-90,1, 0.0, 0.1);
        glutSolidCone(1,4, 200,200);
        glPopMatrix();


        initMaterials(22);



        glPushMatrix();
        glTranslatef(-1,-1,0);
        glBegin(GL_QUADS);


        glVertex3d(0,0,0);

        glVertex3d(1,0,0);

        glVertex3d(1,1,0);

        glVertex3d(0,1,0);


        glEnd();
        glPopMatrix();


    };


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

    if (ligaFoco)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);

    glLightfv(GL_LIGHT1, GL_POSITION,      focoPini);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,focoDir );
}

void drawOrientacao()
{
    glPushMatrix();
    glColor4f(VERDE);
    glTranslatef (obsPini[0],obsPini[1],obsPini[2]);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor4f(LARANJA);
    glTranslatef (obsPfin[0],obsPfin[1],obsPfin[2]);
    glutSolidCube(0.75);
    glPopMatrix();
    glPushMatrix();
    glColor4f(VERMELHO);
    glTranslatef (focoPfin[0],focoPfin[1],focoPfin[2]);
    glutSolidCube(0.75);
    glPopMatrix();
}

void display(void){

    if (noite)
        glClearColor(GRAY1);
    else
        glClearColor(GRAY2);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //================================================================= Viewport1

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glViewport (0, hScreen/4, wScreen/4, hScreen/4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-xC,xC, -xC,xC, -zC,zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 0, 10,0, 0,0,0, 0, 0, -1);


    //--------------------- desenha objectos
    drawScene();
    drawOrientacao();
    //--------------------- Informacao
    glColor3f(1,0,0);
    sprintf(texto, "%d - Noite", noite);
    desenhaTexto(texto,-12,1,-6);
    sprintf(texto, "%d - Tecto", ligaLuz);
    desenhaTexto(texto,-12,1,-9);

    //================================================================= Viewport2
    glEnable(GL_LIGHTING);
    glViewport (wScreen/4, hScreen/4, 0.75*wScreen, 0.75*hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(99.0, wScreen/hScreen, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);

    iluminacao();
    drawScene();
    glutSwapBuffers();




}


void updateVisao(){
    obsPfin[0] =obsPini[0]+rVisao*cos(aVisao);
    obsPfin[2] =obsPini[2]-rVisao*sin(aVisao);
    focoPini[0]=obsPini[0];
    focoPini[2]=obsPini[2];
    focoPfin[0]=focoPini[0]-rFoco*cos(aFoco+incH);
    focoPfin[2]=focoPini[2]-rFoco*sin(aFoco+incH);
    focoPini[1]=obsPini[1];
    focoPini[2]=obsPini[2];
    focoDir[0] =focoPfin[0]-focoPini[0];
    focoDir[1] =incV;
    focoDir[2] =focoPfin[2]-focoPini[2];
    glutPostRedisplay();

}



//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){
    switch (key) {
        //--------------------------- Direccao da Lanterna
        case 's':
        case 'S':
            incH=incH-0.05;
            if (incH<-incMaxH ) incH=-incMaxH ;
            updateVisao();
            break;
        case 'd':
        case 'D':
            incH=incH+0.05;
            if (incH>incMaxH ) incH=incMaxH ;
            updateVisao();
            break;
        case 'e':
        case 'E':
            incV=incV+0.05;
            if (incV>incMaxV ) incV=incMaxV ;
            updateVisao();
            break;
        case 'c':
        case 'C':
            incV=incV-0.05;
            if (incV<-incMaxV ) incV=-incMaxV ;
            updateVisao();
            break;
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
            //--------------------------- Observador
        case 'f':
        case 'F':
            ligaFoco=!ligaFoco;
            glutPostRedisplay();
            break;
            //--------------------------- ColorMaterial
        case 'm':
        case 'M':
            colorM=!colorM;
            glutPostRedisplay();
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
        obsPini[2]=obsPini[2]-incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_DOWN) {
        obsPini[0]=obsPini[0]-incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]+incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_LEFT) {
        aVisao = (aVisao + 0.1) ;
        aFoco=aFoco-0.1;
    }
    if(key == GLUT_KEY_RIGHT) {
        aVisao = (aVisao - 0.1) ;
        aFoco=aFoco+0.1;

    }
    updateVisao();
}

//======================================================= MAIN
int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (400, 100);
    glutCreateWindow ("{jh,jpa,pjmm}@dei.uc.pt-CG  (left,right,up,down) - (n,t,f,m) - (s,d-e,c) ");

    init();
    glutSpecialFunc(teclasNotAscii);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(gestaoRato);

    glutMainLoop();

    return 0;
}
