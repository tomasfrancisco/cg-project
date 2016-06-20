#include "main.hpp"

char        texto[30];
GLboolean   isLightEnabled = true;
GLboolean   isNightEnabled = false;
GLboolean   isTransparencyEnable = false;
GLfloat     timer = 10;

GLfloat billiardTableDimensions[] = { 60.0, 2.0, 30.0 };

Window window;
Observer observer;
Ball balls[4];
Light topLight;
Light ambientLight;

void initWindow() {
    window.mainViewportWidth    = 16.0;
    window.mainViewportHeight   = 15.0;

    window.windowWidth          = 600;
    window.windowHeight         = 500;
}

void initObserver() {
    observer.vision[RADIUS]         = 3.0;
    observer.vision[ANGLE]          = 0.5 * PI;
    observer.vision[INCLINATION]    = 0.1;

    observer.position[X]            = 0;
    observer.position[Y]            = 4;
    observer.position[Z]            = 0.5 * window.mainViewportWidth;

    observer.lookAt[X]              = observer.position[X] + observer.vision[RADIUS] * cos(observer.vision[ANGLE]);
    observer.lookAt[Y]              = observer.position[Y];
    observer.lookAt[Z]              = observer.position[Z] + observer.vision[RADIUS] * sin(observer.vision[ANGLE]);

    observer.upVector[X]            = 0;
    observer.upVector[Y]            = 1;
    observer.upVector[Z]            = 0;
}

void initBalls() {
    balls[0].x = -4;
    balls[0].y = 2;
    balls[0].z = 6;

    balls[0].rotation = 15;

    balls[1].x = -10;
    balls[1].y = 2;
    balls[1].z = 6;

    balls[1].rotation = 30;

    balls[2].x = 15;
    balls[2].y = 2;
    balls[2].z = -7.5;

    balls[2].rotation = 45;

    balls[3].x = 4;
    balls[3].y = 2;
    balls[3].z = -7.5;

    balls[3].rotation = 30;
}

void initTopLight() {
    topLight.position[X] = window.mainViewportWidth/2;
    topLight.position[Y] = 10.0;
    topLight.position[Z] = window.mainViewportWidth/2;
    topLight.position[W] = 1.0;

    topLight.attenuationConstant    = 1.0;
    topLight.linearAttenuation      = 0.05;
    topLight.quadraticAttenuation   = 0.0;

    topLight.color[R] = 0.1;
    topLight.color[G] = 0.1;
    topLight.color[B] = 0.1;
    topLight.color[A] = 1.0;

    topLight.diffuseColor[R] = 1.0;
    topLight.diffuseColor[G] = 1.0;
    topLight.diffuseColor[B] = 1.0;
    topLight.diffuseColor[A] = 1.0;
}

void initAmbientLight() {
    ambientLight.color[R] = 1.0;
    ambientLight.color[G] = 1.0;
    ambientLight.color[B] = 1.0;
    ambientLight.color[A] = 1.0;
}

void initLights() {
    initAmbientLight();
    initTopLight();
}

void enableLights(void){
    //Ambient Light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight.color);
    //Top Light
    glLightfv(GL_LIGHT0, GL_POSITION,      topLight.position );
    glLightfv(GL_LIGHT0, GL_AMBIENT,       topLight.color );
    glLightfv(GL_LIGHT0, GL_DIFFUSE,       topLight.diffuseColor );
    glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, topLight.attenuationConstant);
    glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION,   topLight.linearAttenuation) ;
    glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION,topLight.quadraticAttenuation) ;
}

void init(void) {
    glClearColor(WHITE);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

    initObserver();
    initBalls();
    initLights();


    initTextures();
    initMaterials(MATERIAL_ESMERALD);
    enableLights();


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
    glVertex3i(0,0,-window.mainViewportWidth);
    glVertex3i(0,0, window.mainViewportWidth);
    glEnd();

    //Eixo dos yy
    glColor4f(VERDE);
    glBegin(GL_LINE);
    glVertex3i(0,-window.mainViewportWidth,0);
    glVertex3i(0,window.mainViewportWidth,0);
    glEnd();

    //Eixo dos xx
    glColor4f(VERMELHO);
    glBegin(GL_LINES);
    glVertex3i(-window.mainViewportWidth,0,0);
    glVertex3i( window.mainViewportWidth,0,0);
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
    glVertex3i(-billiardTableDimensions[0] / 2, 0, billiardTableDimensions[2] / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3i(billiardTableDimensions[0] / 2, 0, billiardTableDimensions[2] / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3i(billiardTableDimensions[0] / 2, 0, -billiardTableDimensions[2] / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3i(-billiardTableDimensions[0] / 2, 0, -billiardTableDimensions[2] / 2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Paredes X

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_CAMP_WALL));
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3i(-billiardTableDimensions[0] / 2, 0, billiardTableDimensions[2] / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3i(-billiardTableDimensions[0] / 2, billiardTableDimensions[1], billiardTableDimensions[2] / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3i(-billiardTableDimensions[0] / 2, billiardTableDimensions[1], -billiardTableDimensions[2] / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3i(-billiardTableDimensions[0] / 2, 0, -billiardTableDimensions[2] / 2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_CAMP_WALL));
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3i(billiardTableDimensions[0] / 2, 0, billiardTableDimensions[2] / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3i(billiardTableDimensions[0] / 2, billiardTableDimensions[1], billiardTableDimensions[2] / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3i(billiardTableDimensions[0] / 2, billiardTableDimensions[1], -billiardTableDimensions[2] / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3i(billiardTableDimensions[0] / 2, 0, -billiardTableDimensions[2] / 2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Paredes Z

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_CAMP_WALL));
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3i(-billiardTableDimensions[0] / 2, 0, -billiardTableDimensions[2] / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3i(billiardTableDimensions[0] / 2, 0, -billiardTableDimensions[2] / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3i(billiardTableDimensions[0] / 2, billiardTableDimensions[1], -billiardTableDimensions[2] / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3i(-billiardTableDimensions[0] / 2, billiardTableDimensions[1], -billiardTableDimensions[2] / 2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getTexture(TEXTURE_CAMP_WALL));
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3i(-billiardTableDimensions[0] / 2, 0, billiardTableDimensions[2] / 2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3i(billiardTableDimensions[0] / 2, 0, billiardTableDimensions[2] / 2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3i(billiardTableDimensions[0] / 2, billiardTableDimensions[1], billiardTableDimensions[2] / 2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3i(-billiardTableDimensions[0] / 2, billiardTableDimensions[1], billiardTableDimensions[2] / 2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawMirror() {
    glBegin (GL_QUADS);
    glVertex3f (-billiardTableDimensions[0]/4, 15, billiardTableDimensions[2]/4);
    glVertex3f (-billiardTableDimensions[0]/4, 15, -billiardTableDimensions[2]/4);
    glVertex3f (billiardTableDimensions[0]/4, 15, -billiardTableDimensions[2]/4);
    glVertex3f (billiardTableDimensions[0]/4, 15, billiardTableDimensions[2]/4);
    glEnd();

}

void drawScene() {
    //glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BITS);
    drawAxis();

    drawBilliardTable(60, 20);

    if (isTransparencyEnable) {

        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);

        //glDisable(GL_COLOR_MATERIAL);
        //glEnable(GL_LIGHTING);
        enableLights();

        //black
        glPushMatrix();
        initMaterials(2);
        glTranslatef(balls[0].x, balls[0].y, balls[0].z);
        //glRotatef(rotacoes[1],1,0,0);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        //white
        glPushMatrix();
        initMaterials(3);
        glTranslatef(balls[1].x, balls[1].y, balls[1].z);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        //red
        glPushMatrix();
        initMaterials(4);
        glTranslatef(balls[2].x, balls[2].y, balls[2].z);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        glPushMatrix();

        initMaterials(5);
        glTranslatef(balls[3].x, balls[3].y, balls[3].z);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        glDisable(GL_BLEND);

    }else
    {
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
        enableLights();

        //black
        glPushMatrix();
        initMaterials(2);
        glTranslatef(balls[0].x, balls[0].y, balls[0].z);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        //white
        glPushMatrix();
        initMaterials(3);
        glTranslatef(balls[1].x, balls[1].y, balls[1].z);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        //red
        glPushMatrix();
        initMaterials(4);
        glTranslatef(balls[2].x, balls[2].y, balls[2].z);
        glutSolidSphere(1, 250, 250);
        glPopMatrix();

        //cyan
        glPushMatrix();
        initMaterials(5);
        glTranslatef(balls[3].x, balls[3].y, balls[3].z);
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
    window.windowWidth = width;
    window.windowHeight = height;
    drawScene();
}

void iluminacao() {
    if (isLightEnabled)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);
}

void display(void){
    if (isNightEnabled)
        glClearColor(GRAY1);
    else
        glClearColor(GRAY2);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    //================================================================= Viewport1
    glEnable(GL_LIGHTING);
    glViewport (0, 0, window.windowWidth, window.windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(99.0, window.windowWidth/window.windowHeight, 0.1, 100.0);
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


    glViewport (window.windowWidth - window.windowWidth/4, 0, window.windowWidth/4, window.windowHeight/4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-window.mainViewportWidth,window.mainViewportWidth, -window.mainViewportWidth,window.mainViewportWidth, -window.mainViewportHeight,window.mainViewportHeight);
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
    glViewport (window.windowWidth - window.windowWidth/4, 0, window.windowWidth/4, window.windowHeight/4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-window.mainViewportWidth,window.mainViewportWidth, -window.mainViewportWidth,window.mainViewportWidth, -window.mainViewportHeight,window.mainViewportHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,  10, 0,0, 0,0, 0, 0, -1);


    //--------------------- Informacao
    glColor3f(0,0,0);
    sprintf(texto, "%d - Noite", isNightEnabled);
    desenhaTexto(texto,-12 ,  + 1 ,- 6);
    sprintf(texto, "%d - Tecto", isLightEnabled);
    desenhaTexto(texto,-12 , 1 ,  - 9);
    sprintf(texto, "%d - Trans", isTransparencyEnable);
    desenhaTexto(texto,-12 ,1 ,  - 12);

    glutSwapBuffers();
}

void updateVisao(){
    observer.lookAt[X] = observer.position[X] + observer.vision[RADIUS] * cos(observer.vision[ANGLE]);
    observer.lookAt[Z] = observer.position[Z] + observer.vision[RADIUS] * sin(observer.vision[ANGLE]);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
            //--------------------------- Dia/isNightEnabled
        case 'n':
        case 'N':
            isNightEnabled = !isNightEnabled;

            if (isNightEnabled) {
                ambientLight.color[R]=1.0;
                ambientLight.color[G]=1.0;
                ambientLight.color[B]=1.0;
            }
            else {
                ambientLight.color[R]=0.3;
                ambientLight.color[G]=0.3;
                ambientLight.color[B]=0.3;
            }

            initLights();
            glutPostRedisplay();
            break;
            //--------------------------- Iluminacaoda sala
        case 't':
        case 'T':
            isLightEnabled = !isLightEnabled;

            glutPostRedisplay();
            break;

        case 'g':
        case 'G':
            isTransparencyEnable = !isTransparencyEnable;
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
        runColisionWithBalls(&balls[i].x, &balls[i].z, &balls[i].rotation, 1.0);
        for(int j = i + 1; j < 4; j++) {

        }
    }

    glutPostRedisplay();
    glutTimerFunc(timer, Timer, 1);
}

int main(int argc, char** argv) {
    initWindow();

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize (window.windowWidth, window.windowHeight);
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
