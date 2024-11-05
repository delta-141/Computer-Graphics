#include <iostream>
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/openGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float ballX = -0.8f; 
float ballY = -0.3f; 
float ballZ = -1.2f; 
float colR = 1.0f; 
float colG = 1.0f; 
float colB = 0.0f; 
float bgColR = 0.0f; 
float bgColG = 0.0f; 
float bgColB = 0.0f; 
static int flag = 1; 

void drawBall(void) {
    glColor3f(colR, colG, colB); // Set ball color
    glTranslatef(ballX, ballY, ballZ); // Moving it toward the screen
    glutSolidSphere(0.05, 30, 30); // Create ball
    glTranslatef(-ballX, -ballY, -ballZ); // Reset translation
}

void drawAv(void) {
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-0.9, -0.7, -1.0);
    glVertex3f(-0.5, -0.1, -1.0);
    glVertex3f(-0.2, -1.0, -1.0);
    glVertex3f(0.5, 0.0, -1.0);
    glVertex3f(0.6, -0.2, -1.0);
    glVertex3f(0.9, -0.7, -1.0);
    glEnd();
}

void drawClouds() {
    // Example cloud representation
    glColor3f(1.0, 1.0, 1.0); // Cloud color
    glBegin(GL_QUADS);
    glVertex3f(-0.5, 0.5, -1.0);
    glVertex3f(0.5, 0.5, -1.0);
    glVertex3f(0.5, 0.3, -1.0);
    glVertex3f(-0.5, 0.3, -1.0);
    glEnd();
}

void keyPress(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) 
        ballX += 0.05f; 
    if (key == GLUT_KEY_LEFT) 
        ballX -= 0.05f; 
    glutPostRedisplay(); 
}

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bgColR, bgColG, bgColB, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Add ambient light
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; 
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    // Add positioned light
    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; 
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0); 
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    // Add directed light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; 
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f}; 
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1); 
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    // Drawing the SUN
    glPushMatrix(); 
    drawBall(); 
    glPopMatrix(); 

    // Drawing the Mount Avarest 
    glPushMatrix(); 
    drawAv(); 
    glPopMatrix(); 

    // Drawing the Clouds
    glPushMatrix(); 
    drawClouds(); 
    glPopMatrix(); 

    glutSwapBuffers(); 
}

void update(int value) { 
    if (ballX > 0.9f) { 
        ballX = -0.8f; 
        ballY = -0.3f; 
        flag = 1; 
        colR = 1.0; 
        colG = 1.0; 
        colB = 0.0; 
        bgColB = 0.0; 
    }

    ballX += 0.001f; 

    glutPostRedisplay(); // Tell GLUT that the display has changed 
    glutTimerFunc(25, update, 0); // Call update again in 25 milliseconds 
}

int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(400, 400); 
    glutCreateWindow("Sun"); 
    initRendering(); 
    glutDisplayFunc(drawScene); 
    glutFullScreen();
    glutSpecialFunc(keyPress); 
    glutReshapeFunc(handleResize); 
    glutTimerFunc(25, update, 0); 
    glutMainLoop(); 
    return 0; 
}

