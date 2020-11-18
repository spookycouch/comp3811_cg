#include "SceneWidget.h"

SceneWidget::SceneWidget(QWidget *parent){}

void SceneWidget::initializeGL() {
	glClearColor(1, 0.8, 0.8, 0.0);
}

void SceneWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void SceneWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glFlush();
}