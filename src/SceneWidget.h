#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <GL/glu.h>
#include <glm/glm.hpp>
#include <QGLWidget>
#include "Mesh.h"

class SceneWidget: public QGLWidget {
    public:
    SceneWidget(QWidget *parent);

    private:
    QWidget *parent;
    std::vector<Mesh> *meshes;

    protected:
    // OpenGL functions for init, resize and paint
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

};

#endif