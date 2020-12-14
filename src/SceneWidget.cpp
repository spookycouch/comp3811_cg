#include "SceneWidget.h"
#include <GL/glu.h>
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


static materialStruct brassMaterials = {
    { 0.33, 0.22, 0.03, 1.0},
    { 0.78, 0.57, 0.11, 1.0},
    { 0.99, 0.91, 0.81, 1.0},
    27.8
};

static materialStruct whiteShinyMaterials = {
    { 1.0, 1.0, 1.0, 1.0},
    { 1.0, 1.0, 1.0, 1.0},
    { 1.0, 1.0, 1.0, 1.0},
    100.0
};

SceneWidget::SceneWidget(QWidget *parent){}

void SceneWidget::initializeGL() {
	glClearColor(1, 0.8, 0.8, 0.0);
}

void SceneWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
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
    glPushMatrix();

    // top
    glTranslatef(0,0,1);
    square(p_front);
    // front
    glRotatef(90.,1,0,0);
    glTranslatef(0,-1,0);
    square(p_front);
    // bottom
    glRotatef(90.,1,0,0);
    glTranslatef(0,-1,0);
    square(p_front);
    // back
    glRotatef(90.,1,0,0);
    glTranslatef(0,-1,0);
    square(p_front);

    glPushMatrix();

    // right
    glRotatef(90.,0,1,0);
    glTranslatef(0,0,1);
    square(p_front);

    glPopMatrix();

    // left
    glRotatef(-90.,0,1,0);
    glTranslatef(-1,0,0);
    square(p_front);

    glPopMatrix();
}

void SceneWidget::cylinder(const materialStruct* p_front) {
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    float x0, x1, y0, y1;
    float z_min = -1;
    float z_max =  1;
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

void SceneWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
    gluLookAt(1.,-1.,1., 0.0,0.0,0.0, 0.0,0.0,1.0);
    // gluLookAt(0.,-1.,1., 0.0,0.0,0.0, 0.0,0.0,1.0);
    glPushMatrix();

    // // set the light bulb
	GLfloat light_pos[] = {0., 0., 4.5, 1.};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);


    // house is a 6 metre cube origin at 0,0,0
    glScalef(6,6,6);
    glTranslatef(-0.5,-0.5,0.);

    glPushMatrix();

    // left wall
    glRotatef(90.,1,0,0);
    glRotatef(90.,0,1,0);
    square(&whiteShinyMaterials);

    // floor
    glRotatef(-90.,1,0,0);
    glTranslatef(0,-1,0);
    square(&whiteShinyMaterials);

    // right wall
    glRotatef(-90.,1,0,0);
    glTranslatef(0,-1,0);
    square(&whiteShinyMaterials);

    glPopMatrix();

    // front wall
    glTranslatef(0,1,0);
    glRotatef(90.,1,0,0);

    glPushMatrix();

    glScalef(1,0.25,1);
    square(&whiteShinyMaterials);
    glTranslatef(0,3,0);
    square(&whiteShinyMaterials);

    glPopMatrix();

    glScalef(0.25,0.5,1);
    glTranslatef(0,0.5,0);
    square(&whiteShinyMaterials);
    glTranslatef(3,0,0);
    square(&whiteShinyMaterials);

    
    glPopMatrix();
    glPushMatrix();

    // draw windows
    glTranslatef(-1.65,2.85,1.35);
    glPushMatrix();
    glScalef(3,0.3,0.3);
    cube(&brassMaterials);
    glTranslatef(0,0,5);
    cube(&brassMaterials);
    glTranslatef(0,0,5);
    cube(&brassMaterials);
    glPopMatrix();
    glScalef(0.3,0.3,3.3);
    cube(&brassMaterials);
    glTranslatef(5,0,0);
    cube(&brassMaterials);
    glTranslatef(5,0,0);
    cube(&brassMaterials);

    glPopMatrix();
    glPushMatrix();

    // draw the "background"
    glTranslatef(0.5,0.5,1.);
    glScalef(9,9,3);
    cylinder(&brassMaterials);

    glPopMatrix();

    // draw a cube in the corner
    // glTranslatef(-3,0,0);
    // cube(&brassMaterials);

    glFlush();
}