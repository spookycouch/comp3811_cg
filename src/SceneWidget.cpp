#include "SceneWidget.h"
#include "utils/Shapes.h"
#include "utils/MaterialPredefs.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

SceneWidget::SceneWidget(QWidget *parent){}

void SceneWidget::initializeGL() {
    glClearColor(1, 0.8, 0.8, 0.0);

    // initialise glut with no arguments
    int argc = 0;
    char * argv = {};
    glutInit(&argc, &argv);

    // load textures
    wall_texture = new Image("textures/Finishes.Painting.Paint.White.Flaking.jpg");
    wood_texture = new Image("textures/wild_cherry_mysticBrown.png");

    bg_textures.push_back(new Image("textures/dark_woods.jpg"));
    bg_textures.push_back(new Image("textures/Marc_Dekamps.ppm"));
    bg_textures.push_back(new Image("textures/Mercator-projection.ppm"));

    body.load("textures/body.obj");
    head.load("textures/head.obj");
}

void SceneWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);
    GLfloat light_diffuse[] = {1, 1, 1, 1};
    GLfloat light_specular[] = {1, 1, 1, 1};
    GLfloat light_linear_atten = 0.3;
    GLfloat quadratic_linear_atten = 0.01;

    // light 0 (light bulb illumination)
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, &light_linear_atten);
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &quadratic_linear_atten);

    light_linear_atten = 0.9;
    quadratic_linear_atten = 0.9;

    // light 1 (light bulb glow)
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, &light_linear_atten);
    glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, &quadratic_linear_atten);

    // //light 2 (room illumination)
    // light_diffuse[0] = 0.25;
    // light_diffuse[1] = 0.25;
    // light_diffuse[2] = 0.25;
    // GLfloat light_pos[] = {0, 0, 0, 1.};
    // GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1.};

    // glEnable(GL_LIGHT2);
    // glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    // glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    // glLightfv(GL_LIGHT2, GL_POSITION, light_pos);

    // texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0,1.0, -1.0,1.0, 1.5,20.0);
}

void SceneWidget::walls() {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix(); // D0

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

    // front wall (panels around window)
    glPopMatrix(); // D0
    glPushMatrix(); // D0
    glTranslatef(0,1,0);
    glRotatef(90.,1,0,0);
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
    glDisable(GL_TEXTURE_2D);
}

void SceneWidget::window() {
    glEnable(GL_TEXTURE_2D);
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
}

void SceneWidget::light_bulb() {
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

void SceneWidget::house() {
    walls();
    window();
    light_bulb();
}

void SceneWidget::background() {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bg_textures[bg_index]->Width(), bg_textures[bg_index]->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, bg_textures[bg_index]->imageField());

    glRotatef(background_rotation, 0, 0, 1);
    glTranslatef(0,0,-0.2);
    glScalef(1.5,1.5,1.5);
    cylinder(&backgroundMaterials);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void SceneWidget::character() {
    body.draw();
    glTranslatef(0,2,0);
    head.draw();
}

void SceneWidget::set_light_bulb_period(int value) {
    light_bulb_speed = 1.0/value;
}

void SceneWidget::set_light_bulb_amplitude(int value) {
    light_bulb_amplitude = value;
}

void SceneWidget::set_background_index(int index) {
    bg_index = index;
}

void SceneWidget::set_background_speed(int value) {
    background_speed = value/2.0;
}

void SceneWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLoadIdentity();
    // gluLookAt(0,-3,15,0.,3.,3.,0.,1.,1.);
    gluLookAt(1.,-5.5,3,0.,0.,3.,0.,0.,1.);
    glPushMatrix();

    // scale by 6
    glScalef(6,6,6);
    glPushMatrix();

    // light bulb rotation
    light_bulb_time += light_bulb_speed;
    if (light_bulb_time >= 2 * M_PI)
        light_bulb_time -= 2 * M_PI; // prevent overflow
    light_bulb_angle = sin(light_bulb_time) * light_bulb_amplitude;

    // background rotation
    background_rotation += background_speed;

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

    glPushMatrix();
    glScalef(1.5, 1.5, 1.5);
    glRotatef(90, 1, 0, 0);
    glTranslatef(0,0,-1);
    glRotatef(75, 0, 1, 0);

    glDisable(GL_BLEND);
    // glDisable(GL_LIGHTING);
    character();
    glPopMatrix();

    glFlush();
}