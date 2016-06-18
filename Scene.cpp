//
//  scene.cpp
//  cg-project
//
//  Created by Tomás Francisco and Madalena Fernandinho.
//  Copyright © 2016 Tomás Francisco and Madalena Fernandinho. All rights reserved.
//


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "OpenGL.hpp"


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



//#include "materiais.h" //isto e para tirar
#include "RgbImage.hpp"
#include "Object.hpp"
#include "Navigator.hpp"

//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas
GLfloat  xC = 16.0, zC = 15.0;
GLint    wScreen = 600, hScreen = 500;
char     texto[30];

//------------------------------------------------------------ Observador
GLfloat  PI = 3.14159;
//GLfloat  rVisao = 3.0, aVisao = 0.5*PI, incVisao = 0.1;
//GLfloat  obsPini[] = { 0, 4, static_cast<GLfloat>(0.5*xC) };
//GLfloat  obsPfin[] = { static_cast<GLfloat>(obsPini[0] - rVisao*cos(aVisao)), obsPini[1], static_cast<GLfloat>(obsPini[2] - rVisao*sin(aVisao)) };

//------------------------------------------------------------ Texturas e Rotacao
GLfloat   quadS = 4.0;
GLfloat   quadP[] = { -2, 0, -8 };

GLuint  texture[20];
RgbImage imag;

//------------------------------------------------------------ NOVO - Nevoeiro
//GLfloat nevoeiroCor[] = { 0.75, 0.75, 0.75, 1.0 }; //definicao da cor do nevoeiro


//------------------------------------------------------------ Iluminacao
//------------------------------------------------------------ Global (ambiente)

GLint   noite = 0;
GLfloat luzGlobalCor[4] = { 1.0,1.0,1.0,1.0 };   //
												 //Lampada tecto (ambiente local)

GLint   ligaLuz = 1;
GLfloat localCor[4] = { 0.1,0.1,0.1,1.0 };
GLfloat localCorDif[4] = { 1, 1, 1, 1.0 };
GLfloat localPos[4] = { xC / 2, 10.0, xC / 2, 1.0 };
GLfloat localAttCon = 1.0;
GLfloat localAttLin = 0.05;
GLfloat localAttQua = 0.0;

//Lanterna (local)
//GLint   ligaFoco = 0;
//GLfloat rFoco = 1.1, aFoco = aVisao;
//GLfloat incH = 0.0, incV = 0.0;
//GLfloat incMaxH = 0.5, incMaxV = 0.35;
//GLfloat focoPini[] = { obsPini[0], obsPini[1], obsPini[2], 1.0 };
//GLfloat focoPfin[] = { static_cast<GLfloat>(obsPini[0] - rFoco*cos(aFoco)), obsPini[1], static_cast<GLfloat>(obsPini[2] - rFoco*sin(aFoco)), 1.0 };
//GLfloat focoDir[] = { focoPfin[0] - focoPini[0], 0, focoPfin[2] - focoPini[2] };
//GLfloat focoExp = 10.0;
//GLfloat focoCut = 15.0;

//GLfloat focoCorEsp[4] = { 1.0 ,  1.0, 1.0, 1.0 };
//GLfloat focoCorDif[4] = { 0.85, 0.85,0.85, 1.0 };

//Materiais
GLint   colorM = 0;
GLfloat matAmbiente[] = { 1.0,1.0,1.0,1.0 };
GLfloat matDifusa[] = { 1.0,1.0,1.0,1.0 };
GLfloat matEspecular[] = { 1.0, 1.0, 1.0, 1.0 };
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

GLfloat Map[] = { 60.0, 25.0, 30.0 };

Object Pin("pin.obj");

//================================================================================
//=========================================================================== INIT
//================================================================================

void initLights(void) {
	//Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
	//Tecto
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, localAttLin);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, localAttQua);
}

void initTextures()
{

	//----------------------------------------- Chao y=0 0
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("chao.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- Parede z=-Map/2 1

	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("wall1.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- Parede x=0 2

	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("wall2.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- Tecto

	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("ceiling.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());

}

//================================================================================
//======================================================================== DISPLAY
void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z)
{
	glRasterPos3f(x, y, z);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}

void drawScene() {

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chao y=0
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(-Map[0] / 2, 0, Map[2] / 2);
	glTexCoord2f(10.0f, 0.0f); glVertex3i(Map[0]/2, 0, Map[2] / 2);
	glTexCoord2f(10.0f, 10.0f); glVertex3i(Map[0]/2, 0, -Map[2]/2);
	glTexCoord2f(0.0f, 10.0f); glVertex3i(-Map[0] / 2, 0, -Map[2]/2);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Tecto y=Map[1]

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(-Map[0] / 2, Map[1], Map[2] / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(Map[0]/2, Map[1], Map[2] / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(Map[0]/2, Map[1], -Map[2]/2);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(-Map[0] / 2, Map[1], -Map[2]/2);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Paredes X

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(-Map[0] / 2, 0, Map[2] / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(-Map[0] / 2, Map[1], Map[2] / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(-Map[0] / 2, Map[1], -Map[2] / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(-Map[0] / 2, 0, -Map[2] / 2);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(Map[0] / 2, 0, Map[2] / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(Map[0] / 2, Map[1], Map[2] / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(Map[0] / 2, Map[1], -Map[2] / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(Map[0] / 2, 0, -Map[2] / 2);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Paredes Z

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(-Map[0] / 2, 0, -Map[2] / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(Map[0] / 2, 0, -Map[2] / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(Map[0] / 2, Map[1], -Map[2] / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(-Map[0] / 2, Map[1], -Map[2] / 2);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(-Map[0] / 2, 0, Map[2] / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(Map[0] / 2, 0, Map[2] / 2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(Map[0] / 2, Map[1], Map[2] / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(-Map[0] / 2, Map[1], Map[2] / 2);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	//============================================Eixos
	//Eixo dos zz
	glColor4f(AZUL);
	glBegin(GL_LINES);
	glVertex3i(0, 0, -xC);
	glVertex3i(0, 0, xC);
	glEnd();

	//Eixo dos yy
	glColor4f(VERDE);
	glBegin(GL_LINE);
	glVertex3i(0, -xC, 0);
	glVertex3i(0, xC, 0);
	glEnd();

	//Eixo dos xx
	glColor4f(VERMELHO);
	glBegin(GL_LINES);
	glVertex3i(-xC, 0, 0);
	glVertex3i(xC, 0, 0);
	glEnd();


	//Loading dos objectos para a cena
	char pin[20] = "pin.obj";
	char poolTable[20] = "PoolTable.obj";

	Pin.LoadFile();

	glPushMatrix();
		Pin.Draw();
	glPopMatrix();

	glutPostRedisplay();
}


GLvoid resize(GLsizei width, GLsizei height)
{
	wScreen = width;
	hScreen = height;
	drawScene();
}

//======================================================================== ILUMINCCAO
void iluminacao() {

	if (ligaLuz)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
}

void drawOrientacao() {
	glPushMatrix();
	glColor4f(VERDE);
	glTranslatef(getObserver().eye.x, getObserver().eye.y, getObserver().eye.z);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glColor4f(LARANJA);
	glTranslatef(getObserver().center.x, getObserver().center.y, getObserver().center.z);
	glutSolidCube(0.75);
	glPopMatrix();
}

void display(void) {

	if (noite)
		glClearColor(GRAY1);
	else
		glClearColor(GRAY2);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//================================================================= Viewport1

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, hScreen / 4, wScreen / 4, hScreen / 4);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-xC, xC, -xC, xC, -zC, zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 10, 0, 0, 0, 0, 0, 0, -1);


	//--------------------- desenha objectos
	drawScene();
	drawOrientacao();
	//--------------------- Informacao
	glColor3f(1, 0, 0);
	sprintf(texto, "%d - Noite", noite);
	desenhaTexto(texto, -12, 1, -6);
	sprintf(texto, "%d - Tecto", ligaLuz);
	desenhaTexto(texto, -12, 1, -9);

	//================================================================= Viewport2
	glEnable(GL_LIGHTING);
	glViewport(wScreen / 4, hScreen / 4, 0.75*wScreen, 0.75*hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(99.0, wScreen / hScreen, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(getObserver().eye.x,    getObserver().eye.y,    getObserver().eye.z,
			  getObserver().center.x, getObserver().center.y, getObserver().center.z,
			  getObserver().up.x,     getObserver().up.y,     getObserver().up.z);
	iluminacao();
	glDisable(GL_LIGHTING);
	drawScene();
	glutSwapBuffers();
}

void init(void) {

	initObserver(0, 	4, 			0.5 * xC,
				 0, 	1, 			0,
				 3.0, 	0.5 * PI, 	0.1);

	glClearColor(WHITE);
	glShadeModel(GL_SMOOTH);

	//NOVO - Activa o nevoeiro
	//glEnable(GL_FOG);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	initTextures();
	//initMaterials(1);
	initLights();
	//NOVO
	//initNevoeiro();
	Pin.LoadFile();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}

//======================================================= MAIN
void start(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("{jh,jpa,pjmm}@dei.uc.pt-CG  (left,right,up,down) - (n,t,f,m) - (s,d-e,c) ");

	init();
	glutSpecialFunc(Special);
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	//glutMouseFunc(gestaoRato);

	glutMainLoop();

}
