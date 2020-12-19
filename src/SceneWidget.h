#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>

struct materialStruct;

class SceneWidget: public QGLWidget {
    public:
    SceneWidget(QWidget *parent);

    private:
        void square(const materialStruct* p_front);
        void cube(const materialStruct* p_front);
        void cylinder(const materialStruct* p_front); // taken from course tutorials
        void sphere(const materialStruct* p_front ); // taken from course tutorials

    protected:
    // OpenGL functions for init, resize and paint
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif