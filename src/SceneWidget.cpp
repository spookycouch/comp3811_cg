#include "SceneWidget.h"
#include "utils/Shapes.h"
#include "utils/MaterialPredefs.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>



SceneWidget::SceneWidget(){}

void SceneWidget::initializeGL() {
    glClearColor(0,0,0,0);

    // load textures
    wall_texture = new Image("textures/Finishes.Painting.Paint.White.Flaking.jpg");
    wood_texture = new Image("textures/wild_cherry_mysticBrown.png");
    bg_textures.push_back(new Image("textures/dark_woods.jpeg"));
    bg_textures.push_back(new Image("textures/Marc_Dekamps.ppm"));
    bg_textures.push_back(new Image("textures/Mercator-projection.ppm"));

    // load .obj files
    body.load("models/body.obj");
    head.load("models/head.obj");
}

void SceneWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

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

    // texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0,1.0, -1.0,1.0, 1.5,20.0);
}

void SceneWidget::floor() {
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wood_texture->Width(), wood_texture->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, wood_texture->imageField());

    glPushMatrix();
    glRotatef(90,0,0,1);
    glTranslatef(0,-1,0);
    square(&woodMaterials, 5);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void SceneWidget::walls() {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix(); // D0

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
    // adjacent to window
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
    // diagonal to window
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
    glRotatef(rocking_chair_angle,0,1,0);
    body.draw();

    // head is at z=2.15 units
    glTranslatef(0,0,2.15);

    glRotatef(head_vibrate_angle,0,0,1);
    glRotatef(head_vibrate_angle,1,0,0);
    head.draw();
}

void SceneWidget::shadow() {
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glColor3f(0,0,0);

    float character_angle_rad = (orbit_angle - 15) * M_PI/180.0;

    // TODO: explain
    float shear_light = cos(character_angle_rad) * sin(light_bulb_time) * light_bulb_amplitude/100.0;
    float shear_chair = 0.5 * (sin(rocking_chair_time) + 1) + sin(character_angle_rad) * sin(light_bulb_time) * light_bulb_amplitude/100.0;
    GLfloat shadow_transform[16] = {1,0,0,0,
                                    0,1,0,0,
                                    shear_chair,shear_light,0,0,
                                    0,0,0,1};
    glMultMatrixf(shadow_transform);
    character();
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
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

void SceneWidget::set_rocking_chair_speed(int value) {
    rocking_chair_speed = value/200.0;
}

void SceneWidget::set_head_vibrate_speed(int value) {
    head_vibrate_speed = value/10.0;
}

void SceneWidget::set_proof_of_orbit(int state) {
    proof_of_orbit = state;
}

/** Add angle
 * add two angles and return the normalised
 * value between 0 and 2*PI radians.
 */
float add_angle(float x, float y) {
    x += y;
    if (x >= 2 * M_PI)
        x -= 2 * M_PI;
    return x;
}

void SceneWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
    gluLookAt(1.,-5.5,3,0.,0.,3.,0.,0.,1.);

    // set light bulb angle
    light_bulb_time = add_angle(light_bulb_time, light_bulb_speed);
    light_bulb_angle = sin(light_bulb_time) * light_bulb_amplitude;
    // background rotation
    background_rotation += background_speed;
    // set rocking chair angle
    rocking_chair_time = add_angle(rocking_chair_time, rocking_chair_speed);
    rocking_chair_angle = sin(rocking_chair_time) * 20;
    // set head angle
    head_vibrate_time = add_angle(head_vibrate_time, head_vibrate_speed);
    head_vibrate_angle = sin(head_vibrate_time) * 10;

    // scale by 6
    glScalef(6,6,6);

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

    // floor centered at 0,0,0
    glPushMatrix();
    glTranslatef(-0.5,-0.5,0.);
    floor();
    glPopMatrix();

    // set character pose
    glPushMatrix();
    glScalef(0.25, 0.25, 0.25);
    if (proof_of_orbit)
        orbit_angle -= 1;
    glRotatef(orbit_angle,0,0,1);
    glTranslatef(0,1,0);
    glRotatef(75,0,0,1);
    // draw the character's shadow
    shadow();
    // draw the character
    // (0.1 units off the ground to account for rocking chair)
    glTranslatef(0,0,0.1);
    character();
    glPopMatrix();

    // house centered at 0,0,0
    glTranslatef(-0.5,-0.5,0.);
    house();

    glFlush();
}