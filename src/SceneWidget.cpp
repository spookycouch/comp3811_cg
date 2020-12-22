#include "SceneWidget.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

#include <iostream>
// static const int N        = 100; // This determines the number of faces of the cylinder
// static const int n_div   =  100;  // This determines the fineness of the cylinder along its length
static const int N        = 6; // This determines the number of faces of the cylinder
static const int n_div   =  1;  // This determines the fineness of the cylinder along its length
static const float PI = 3.1415926535;

// Setting up material properties
typedef struct materialStruct {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
} materialStruct;


static materialStruct woodMaterials = {
    { 0.0, 0.0, 0.0, 1.0},
    { 0.75, 0.5, 0.2, 1.0},
    { 0.0, 0.0, 0.0, 1.0},
    20.0
};

static materialStruct whitePaintMaterials = {
    { 0.2, 0.2, 0.2, 1.0},
    { 1.0, 1.0, 1.0, 1.0},
    { 0.8, 0.8, 0.8, 1.0},
    100.0
};

static materialStruct blackPlasticMaterials = {
    { 0.1, 0.1, 0.1, 1.0},
    { 0.1, 0.1, 0.1, 1.0},
    { 0.3, 0.3, 0.3, 1.0},
    100.0
};

static materialStruct glassMaterials = {
    { 0.5, 0.5, 0.5, 1.0},
    { 0.8, 0.9, 1.0, 0.2},
    { 0.8, 0.9, 1.0, 1.0},
    100.0
};

static materialStruct warmLightMaterials = {
    { 1.0, 1.0, 0, 1.0},
    { 1.0, 1.0, 0, 0.9},
    { 1.0, 1.0, 0, 1.0},
    100.0
};

SceneWidget::SceneWidget(QWidget *parent){}

void SceneWidget::initializeGL() {
    glClearColor(1, 0.8, 0.8, 0.0);

    // initialise glut with no arguments
    int argc = 0;
    char * argv = {};
    glutInit(&argc, &argv);
}

void SceneWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0,10.0, -10.0,10.0, -10.0,10.0);
    // glOrtho(-1.0,1.0, -1.0,1.0, -0.0,6.0); // light bulb
    // glFrustum(-1.0,1.0, -1.0,1.0, 1.5,20.0);
}

void SceneWidget::square(const materialStruct* p_front) {
    glMaterialfv(GL_FRONT, GL_AMBIENT,  p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS, p_front->shininess);

    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glNormal3f(0,0,1);

    glVertex3f(1,0,0);
    glNormal3f(0,0,1);

    glVertex3f(1,1,0);
    glNormal3f(0,0,1);

    glVertex3f(0,1,0);
    glNormal3f(0,0,1);
    glEnd();
}

void SceneWidget::cube(const materialStruct* p_front) {
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
    glPushMatrix();
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);
    glPopMatrix();
}

void SceneWidget::cylinder(const materialStruct* p_front) {
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    float x0, x1, y0, y1;
    float z_min = 0;
    float z_max = 1;
    float delta_z = (z_max - z_min)/n_div;

    for (int i = 0; i < N; i++){
        for(int i_z = 0; i_z < n_div; i_z++){
            x0 = cos(2*i*PI/N);
            x1 = cos(2*(i+1)*PI/N);
            y0 = sin(2*i*PI/N);
            y1 = sin(2*(i+1)*PI/N);

            // NOTE: negated the normals from
            // (x,y,0) to (-x,-y,0) so it reflects inwards
            float z = z_min + i_z*delta_z;
            glBegin(GL_POLYGON);
            glVertex3f(x0,y0,z);
            glNormal3f(-x0,-y0,0);
            glVertex3f(x1,y1,z);
            glNormal3f(-x1,-y1,0);
            glVertex3f(x1,y1,z+delta_z);
            glNormal3f(-x1,-y1,0);
            glVertex3f(x0,y0,z+delta_z);
            glNormal3f(-x0,-y0,0);
            glEnd();
        }
    }
}


void SceneWidget::sphere(const materialStruct* p_front){

    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
    GLUquadric * quad = gluNewQuadric();
    gluQuadricOrientation(quad, GLU_INSIDE);
    gluSphere(quad, 1, 8, 8);
}

void SceneWidget::house() {
    glPushMatrix();

    // left wall
    glRotatef(90.,1,0,0);
    glRotatef(90.,0,1,0);
    square(&whitePaintMaterials);
    // floor
    glRotatef(-90.,1,0,0);
    glTranslatef(0,-1,0);
    square(&whitePaintMaterials);
    // right wall
    glRotatef(-90.,1,0,0);
    glTranslatef(0,-1,0);
    square(&whitePaintMaterials);
    glPopMatrix();
    glPushMatrix();
    // front wall
    glTranslatef(0,1,0);
    glRotatef(90.,1,0,0);
    // 4 rectangular panels,
    // adjacent to windows
    glPushMatrix();
    glTranslatef(0.25,0,0);
    glScalef(0.5,0.25,1);
    square(&whitePaintMaterials);
    glTranslatef(0,3,0);
    square(&whitePaintMaterials);
    glPopMatrix();
    glPushMatrix();
    glScalef(0.25,0.5,1);
    glTranslatef(0,0.5,0);
    square(&whitePaintMaterials);
    glTranslatef(3,0,0);
    square(&whitePaintMaterials);
    // 4 square panels,
    // diagonal to windows
    glPopMatrix();
    glScalef(0.25,0.25,1);
    square(&whitePaintMaterials);
    glTranslatef(3,0,0);
    square(&whitePaintMaterials);
    glTranslatef(0,3,0);
    square(&whitePaintMaterials);
    glTranslatef(-3,0,0);
    square(&whitePaintMaterials);

    glPopMatrix();
    glPushMatrix();

    // draw windows
    glTranslatef(0.25,1,0.25);
    glPushMatrix();
    glTranslatef(0,-0.025,0);
    // window "bones"
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            glPushMatrix();
            glTranslatef(0.225 * i, 0, 0.225 * j);
            glScalef(0.225,0.05,0.05);
            cube(&woodMaterials);

            glPopMatrix();
            glPushMatrix();

            glTranslatef(0.225 * j, 0, 0.225 * i);
            glScalef(0.05,0.05,0.225);
            cube(&woodMaterials);
            glPopMatrix();
        }
    }
    // window "joints"
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            glPushMatrix();
            glTranslatef(0.225 * i, 0, 0.225 * j);
            glScalef(0.05,0.05,0.05);
            cube(&woodMaterials);
            glPopMatrix();
        }
    }
    // window glass (alpha blend)
    glPopMatrix();
    glRotatef(90,1,0,0);
    glScalef(0.5,0.5,1);
    square(&glassMaterials);

    glPopMatrix();
    glPushMatrix();

    // light cable
    glTranslatef(0.5,0.5,1);
    glRotatef(180,1,0,0);
    glPushMatrix();
    glScalef(0.005,0.005,0.3);
    cylinder(&blackPlasticMaterials);
    glPopMatrix();

    // TODO: use glusphere
    // draw the light (alpha blend)
    glTranslatef(0,0,0.25);
    glPushMatrix();
    glScalef(0.01,0.01,0.03);
    glTranslatef(0,0,1);
    sphere(&warmLightMaterials);
    // draw the glass bulb (alpha blend)
    glPopMatrix();
    glScalef(0.025,0.025,0.04);
    glTranslatef(0,0,1);
    sphere(&glassMaterials);

    glPopMatrix();
}

void SceneWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLoadIdentity();
    gluLookAt(1.0,-1.0,1.5, 0.0,0.0,0.0, 0.0,0.0,1.0);
    // gluLookAt(1.0,-1.0,4.5, 0.0,0.0,4.5, 0.0,0.0,1.0); // light bulb view
    // gluLookAt(2.,-7.5,3,0.,0.,3.,0.,0.,1.); // good perspective view
    // gluLookAt(0.,-1.,1., 0.0,0.0,0.0, 0.0,0.0,1.0); // top view
    glPushMatrix();

    // scale by 6
    glScalef(6,6,6);

    // // set the light bulb
	GLfloat light_pos[] = {0, 0., 0.725, 1.};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    // house centered at 0,0,0
    glTranslatef(-0.5,-0.5,0.);
    house();

    glPopMatrix();
    glPushMatrix();

    // draw the "background"
    glTranslatef(0.5,0.5,1.);
    glScalef(9,9,3);
    cylinder(&blackPlasticMaterials);

    glPopMatrix();
    glFlush();
}