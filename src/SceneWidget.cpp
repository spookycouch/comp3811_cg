#include "SceneWidget.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

#include <iostream>
// static const int N        = 100; // This determines the number of faces of the cylinder
// static const int n_div   =  100;  // This determines the fineness of the cylinder along its length
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
    { 0.8, 0.4, 0.2, 1.0},
    { 0.0, 0.0, 0.0, 1.0},
    20.0
};

static materialStruct whitePaintMaterials = {
    { 0.0, 0.0, 0.0, 1.0},
    { 0.5, 0.5, 0.5, 1.0},
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
    { 0.0, 0.0, 0.0, 1.0},
    { 0.6, 0.7, 0.8, 0.2},
    { 0.6, 0.7, 0.8, 0.2},
    100.0
};

static materialStruct warmLightMaterials = {
    { 1.0, 1.0, 0, 1.0},
    { 1.0, 1.0, 0, 0.9},
    { 1.0, 1.0, 0, 1.0},
    100.0
};

static materialStruct backgroundMaterials = {
    { 0.25, 0.25, 0.25, 1.0},
    { 0, 0, 0, 1.0},
    { 0, 0, 0, 1.0},
    100.0
};

typedef struct textureTransform {
    float translate[2];
    float scale[2];
} textureTransform;

SceneWidget::SceneWidget(QWidget *parent){}

void SceneWidget::initializeGL() {
    glClearColor(1, 0.8, 0.8, 0.0);

    // initialise glut with no arguments
    int argc = 0;
    char * argv = {};
    glutInit(&argc, &argv);

    // load textures
    wall_texture = new Image("textures/Finishes.Painting.Paint.White.Flaking.jpg");
    wood_texture = new Image("textures/beechwood_mysticBrown.png");
    world_texture = new Image("textures/Mercator-projection.ppm");
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

    // light 0 (light bulb illumination)
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

    //light 2 (room illumination)
    light_diffuse[0] = 0.25;
    light_diffuse[1] = 0.25;
    light_diffuse[2] = 0.25;
    GLfloat light_pos[] = {0, 0, 0, 1.};
    GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1.};

    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light_pos);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0,1.0, -1.0,1.0, 1.5,20.0);
}

void SceneWidget::square(const materialStruct* p_front, int n_div=1, textureTransform* tex_transform=0) {
    glMaterialfv(GL_FRONT, GL_AMBIENT,  p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS, p_front->shininess);
    // float n_div = 10.0;
    float step_size = 1.0/n_div;

    for (int i = 0; i < n_div; ++i)
        for (int j = 0; j < n_div; ++j)
        {
            // vertex coordinates
            float x0 = i * step_size;
            float y0 = j * step_size;
            float x1 = x0 + step_size;
            float y1 = y0 + step_size;

            // texture coordinates
            float tx0 = x0;
            float ty0 = y0;
            float tx1 = x1;
            float ty1 = y1;

            // apply texture transforms (if present)
            if (tex_transform) {
                tx0 = x0 + tex_transform->translate[0];
                ty0 = y0 + tex_transform->translate[1];
                tx1 = tx0 + step_size*tex_transform->scale[0];
                ty1 = ty0 + step_size*tex_transform->scale[1];
            }

            // create polygon
            glBegin(GL_POLYGON);
                glTexCoord2f(tx0, ty0);
                glVertex3f(x0,y0,0);
                glNormal3f(0,0,1);

                glTexCoord2f(tx1, ty0);
                glVertex3f(x1,y0,0);
                glNormal3f(0,0,1);

                glTexCoord2f(tx1, ty1);
                glVertex3f(x1,y1,0);
                glNormal3f(0,0,1);

                glTexCoord2f(tx0, ty1);
                glVertex3f(x0,y1,0);
                glNormal3f(0,0,1);
            glEnd();
        }
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
    // right
    glPushMatrix();
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


void SceneWidget::cylinder(const materialStruct* p_front, int N=8, int n_div=1) {
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
                glTexCoord2f(0, 0);
                glVertex3f(x0,y0,z);
                glNormal3f(-x0,-y0,0);

                glTexCoord2f(1, 0);
                glVertex3f(x1,y1,z);
                glNormal3f(-x1,-y1,0);

                glTexCoord2f(1, 1);
                glVertex3f(x1,y1,z+delta_z);
                glNormal3f(-x1,-y1,0);

                glTexCoord2f(0, 1);
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
    glPushMatrix(); // D0

    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // floor
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wood_texture->Width(), wood_texture->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, wood_texture->imageField());
    glPushMatrix(); // D1
    glRotatef(90,0,0,1);
    glTranslatef(0,-1,0);
    square(&woodMaterials, 5);
    glPopMatrix(); // D1

    // walls
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wall_texture->Width(), wall_texture->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, wall_texture->imageField());
    // left wall
    glRotatef(90.,1,0,0);
    glRotatef(90.,0,1,0);
    square(&whitePaintMaterials, 5);
    // right wall
    glRotatef(-90.,1,0,0);
    glTranslatef(0,-1,0);
    glRotatef(-90.,1,0,0);
    glTranslatef(0,-1,0);
    square(&whitePaintMaterials, 5);
    // top wall
    glRotatef(-90.,1,0,0);
    glTranslatef(0,-1,0);
    square(&whitePaintMaterials, 5);
    // front wall
    glPopMatrix(); // D0
    glPushMatrix(); // D0
    glTranslatef(0,1,0);
    glRotatef(90.,1,0,0);

    // wall panels around window
    textureTransform* wall_transform = new textureTransform();
    // 4 rectangular panels,
    // adjacent to windows
    glPushMatrix(); // D1
    glTranslatef(0.25,0,0);
    glScalef(0.5,0.25,1);
    wall_transform->translate[0] = 0.25;
    wall_transform->translate[1] = 0;
    wall_transform->scale[0] = 0.5;
    wall_transform->scale[1] = 0.25;
    square(&whitePaintMaterials, 1, wall_transform);
    glTranslatef(0,3,0);
    wall_transform->translate[1] += 3;
    square(&whitePaintMaterials, 1, wall_transform);
    glPopMatrix(); // D1
    glPushMatrix(); // D1
    glScalef(0.25,0.5,1);
    glTranslatef(0,0.5,0);
    wall_transform->translate[0] = 0;
    wall_transform->translate[1] = 0.5;
    wall_transform->scale[0] = 0.25;
    wall_transform->scale[1] = 0.5;
    square(&whitePaintMaterials, 1, wall_transform);
    glTranslatef(3,0,0);
    wall_transform->translate[0] += 3;
    square(&whitePaintMaterials, 1, wall_transform);
    // 4 square panels,
    // diagonal to windows
    glPopMatrix(); // D1
    glScalef(0.25,0.25,1);
    wall_transform->translate[0] = 0;
    wall_transform->translate[1] = 0;
    wall_transform->scale[0] = 0.25;
    wall_transform->scale[1] = 0.25;
    square(&whitePaintMaterials, 1, wall_transform);
    glTranslatef(3,0,0);
    wall_transform->translate[0] += 3;
    square(&whitePaintMaterials, 1, wall_transform);
    glTranslatef(0,3,0);
    wall_transform->translate[1] += 3;
    square(&whitePaintMaterials, 1, wall_transform);
    glTranslatef(-3,0,0);
    wall_transform->translate[0] -= 3;
    square(&whitePaintMaterials, 1, wall_transform);
    delete wall_transform;
    glPopMatrix(); // D0
    glPushMatrix(); // D0

    // draw windows
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wood_texture->Width(), wood_texture->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, wood_texture->imageField());
    glTranslatef(0.25,1,0.25);
    glPushMatrix(); // D1
    glTranslatef(0,-0.025,0);
    // window "bones"
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            glPushMatrix(); // D2
            glTranslatef(0.225 * i, 0, 0.225 * j);
            glScalef(0.225,0.05,0.05);
            cube(&woodMaterials);

            glPopMatrix(); // D2
            glPushMatrix(); // D2

            glTranslatef(0.225 * j, 0, 0.225 * i);
            glScalef(0.05,0.05,0.225);
            cube(&woodMaterials);
            glPopMatrix(); // D2
        }
    }
    // window "joints"
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            glPushMatrix(); // D2
            glTranslatef(0.225 * i, 0, 0.225 * j);
            glScalef(0.05,0.05,0.05);
            cube(&woodMaterials);
            glPopMatrix(); // D2
        }
    }

    glDisable(GL_TEXTURE_2D);

    // window glass (alpha blend)
    glPopMatrix(); // D1
    glRotatef(90,1,0,0);
    glScalef(0.5,0.5,1);
    square(&glassMaterials);

    glPopMatrix(); // D0
    glPushMatrix(); // D0

    // light cable
    glTranslatef(0.5,0.5,1);
    glRotatef(180,1,0,0);
    glRotatef(light_bulb_angle, 0, 1, 0);
    glPushMatrix(); // D1
    glScalef(0.005,0.005,0.3);
    cylinder(&blackPlasticMaterials);
    glPopMatrix(); // D1

    // draw the light (alpha blend)
    glTranslatef(0,0,0.25);
    glPushMatrix(); // D1
    glScalef(0.01,0.01,0.03);
    glTranslatef(0,0,1);
    sphere(&warmLightMaterials);
    // draw the glass bulb (alpha blend)
    glPopMatrix(); // D1
    glScalef(0.025,0.025,0.04);
    glTranslatef(0,0,1);
    sphere(&glassMaterials);

    glPopMatrix(); // D0
}

void SceneWidget::background() {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, world_texture->Width(), world_texture->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, world_texture->imageField());
    glScalef(1.5,1.5,1.5);
    cylinder(&backgroundMaterials);
    glDisable(GL_TEXTURE_2D);
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
    // gluLookAt(0,0,15,0.,3.,3.,0.,1.,1.);
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
    background();

    // house centered at 0,0,0
    glTranslatef(-0.5,-0.5,0.);
    house();

    glPopMatrix();
    glPopMatrix();
    glFlush();
}