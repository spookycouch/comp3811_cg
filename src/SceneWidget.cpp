#include "SceneWidget.h"

SceneWidget::SceneWidget(QWidget *parent){
    this->parent = parent;
    meshes = new std::vector<Mesh>();
    meshes->push_back(Mesh("head_eyed_n.obj"));
    meshes->at(0).SetPosition(1,0,0);
    // meshes->at(0).SetPosition(0,0,0);
}

void SceneWidget::initializeGL() {
    // widget background colour
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // projection box
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);
}

void SceneWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // turn on the lights
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // where are the lights
    GLfloat light_pos[] = {2,0,1, 1.};	
    GLfloat spot_direction[] = {-2,0,-1, 0};	
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 50.);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
}

// LAZINESS. FILE LEVEL VARIABLES
float x = 0, y = 0, z = 0;
float x_rot = 0, y_rot = 0, z_rot = 0;

void SceneWidget::paintGL() {
    // clear the widget
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set model view mode and enable depth test
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
    // gluLookAt(0.,0.5,0.5, 0.0,0.0,0.0, 0.0,1.0,0.0);
    gluLookAt(0.,0.,1., 0.0,0.0,0.0, 0.0,1.0,0.0);


    // for (std::vector<Mesh>::iterator mesh = meshes->begin(); mesh != meshes->end(); ++mesh)
    //     mesh->Draw();


    // FOR OUR SPECIAL SCENE
    // rotate the world
    glRotatef(y_rot, 0, 1, 0);

    Mesh *face = &(meshes->at(0));
    face->Draw();
    // face->SetRotation(x_rot, y_rot, z_rot);
    y_rot += 1;



    // flush to screen
    glFlush();
}