#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>

struct materialStruct;

class SceneWidget: public QGLWidget {
    public:
    /** Constructor
     *
     **/
    SceneWidget(QWidget *parent);

    private:
    /** Square
     * a flat plane from x=0 to x=1, y=0 to y=1
    */
    void square(const materialStruct* p_front, int n_div);


    /** Cube
     * GLUT solid cube of origin at the bottom left with z=0
    **/
    void cube(const materialStruct* p_front);


    /** Cylinder
     * taken from COMP3811 tutorials
     * a cylinder of origin at the centre with z=0
    **/
    void cylinder(const materialStruct* p_front);


    /** Sphere
     * GLUT sphere of origin at its centre
    **/
    void sphere(const materialStruct* p_front );


    /** House
     * Background for our complex visual scene, comprised of
     * instances of squares, cubes, cylinders and spheres.
    **/
    void house();

    protected:
    // OpenGL functions for init, resize and paint
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif