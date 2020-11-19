#include "SceneWidget.h"

SceneWidget::SceneWidget(QWidget *parent){
    meshes = new std::vector<Mesh>();
    meshes->push_back(Mesh("head_eyed.obj"));
}

void SceneWidget::initializeGL() {
    // widget background colour
    glClearColor(1, 0.8, 0.8, 0.0);
}

void SceneWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);
}

void SceneWidget::paintGL() {
    // clear the widget
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set model view mode and enable depth test
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    for (std::vector<Mesh>::iterator mesh = meshes->begin(); mesh != meshes->end(); ++mesh)
        mesh->Draw();

    glLoadIdentity();
    gluLookAt(0.,0.,2., 0.0,0.0,0.0, 0.0,1.0,0.0);

    // flush to screen
    glFlush();
}