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
    { 0.6, 0.3, 0.15, 1.0},
    { 0.0, 0.0, 0.0, 1.0},
    20.0
};

static materialStruct whitePaintMaterials = {
    { 0.0, 0.0, 0.0, 1.0},
    { 0.6, 0.6, 0.6, 1.0},
    { 0.5, 0.5, 0.5, 1.0},
    50.0
};

static materialStruct blackPlasticMaterials = {
    { 0.0, 0.0, 0.0, 1.0},
    { 0.1, 0.1, 0.1, 1.0},
    { 0.6, 0.6, 0.6, 1.0},
    50.0
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
    GLfloat light_diffuse[] = {0.5, 0.5, 0.5, 1};
    GLfloat light_specular[] = {1, 1, 1, 1};
    GLfloat light_linear_atten = 0.3;
    GLfloat quadratic_linear_atten = 0.1;

    // light 0 (room illumination)
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, &light_linear_atten);
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &quadratic_linear_atten);

    light_diffuse[0] = 1;
    light_diffuse[1] = 1;
    light_diffuse[2] = 1;
    light_linear_atten = 0.9;
    quadratic_linear_atten = 0.9;

    // light 1 (light bulb glow)
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, &light_linear_atten);
    glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, &quadratic_linear_atten);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0,1.0, -1.0,1.0, 1.5,20.0);
}

void SceneWidget::square(const materialStruct* p_front, int n_div=1) {
    glMaterialfv(GL_FRONT, GL_AMBIENT,  p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS, p_front->shininess);
    // float n_div = 10.0;
    float step_size = 1.0/n_div;

    for (int i = 0; i < n_div; ++i)
        for (int j = 0; j < n_div; ++j)
        {
            float x0 = i * step_size;
            float y0 = j * step_size;
            float x1 = x0 + step_size;
            float y1 = y0 + step_size;

            glBegin(GL_POLYGON);
            glVertex3f(x0,y0,0);
            glNormal3f(0,0,1);

            glVertex3f(x1,y0,0);
            glNormal3f(0,0,1);

            glVertex3f(x1,y1,0);
            glNormal3f(0,0,1);

            glVertex3f(x0,y1,0);
            glNormal3f(0,0,1);
            glEnd();
        }
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
    gluSphere(quad, 1, 32, 32);
}

void SceneWidget::house() {
    glPushMatrix();

    // left wall
    glRotatef(90.,1,0,0);
    glRotatef(90.,0,1,0);
    square(&whitePaintMaterials, 5);
    // floor
    glRotatef(-90.,1,0,0);
    glTranslatef(0,-1,0);
    square(&woodMaterials, 5);
    // right wall
    glRotatef(-90.,1,0,0);
    glTranslatef(0,-1,0);
    square(&whitePaintMaterials, 5);
    // top wall
    glRotatef(-90.,1,0,0);
    glTranslatef(0,-1,0);
    square(&whitePaintMaterials, 5);
    // front wall
    glPopMatrix();
    glPushMatrix();
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
    glRotatef(light_bulb_angle, 0, 1, 0);
    glPushMatrix();
    glScalef(0.005,0.005,0.3);
    cylinder(&blackPlasticMaterials);
    glPopMatrix();

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

void SceneWidget::set_light_bulb_period(int value) {
    light_bulb_speed = 1.0/value;
}

void SceneWidget::set_light_bulb_amplitude(int value) {
    light_bulb_amplitude = value;
}

void SceneWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLoadIdentity();
    gluLookAt(1.,-5.5,3,0.,0.,3.,0.,0.,1.);
    glPushMatrix();

    // scale by 6
    glScalef(6,6,6);
    glPushMatrix();

    // light bulb rotation
    light_bulb_time += light_bulb_speed;
    if (light_bulb_time >= 2 * PI)
        light_bulb_time -= 2 * PI; // prevent overflow
    light_bulb_angle = sin(light_bulb_time) * light_bulb_amplitude;

    // position the lights
    glPushMatrix();
    glTranslatef(0,0,1);
    glRotatef(-light_bulb_angle, 0, 1, 0);
    GLfloat light_pos[] = {0, 0, -0.275, 1.};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
    glPopMatrix();

    // draw the "background"
    glPushMatrix();
    glTranslatef(0.5,0.5,0);
    glScalef(1.5,1.5,1.5);
    cylinder(&blackPlasticMaterials);
    glPopMatrix();

    // house centered at 0,0,0
    glTranslatef(-0.5,-0.5,0.);
    house();

    glPopMatrix();
    glPopMatrix();
    glFlush();
}