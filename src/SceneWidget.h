#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include "utils/Image.h"

struct materialStruct;
struct textureTransform;

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
    void square(const materialStruct* p_front, int n_div, textureTransform* tex_transform);


    /** Cube
     * GLUT solid cube of origin at the bottom left with z=0
    **/
    void cube(const materialStruct* p_front);


    /** Cylinder
     * taken from COMP3811 tutorials
     * a cylinder of origin at the centre with z=0
    **/
    void cylinder(const materialStruct* p_front, int N, int n_div);


    /** Sphere
     * GLUT sphere of origin at its centre
    **/
    void sphere(const materialStruct* p_front );


    /** House
     * Setting for our complex visual scene, comprised of
     * instances of squares, cubes, cylinders and spheres.
    **/
    void house();

    /** Background
     * Background viewable from the window of our house
     */
    void background();


    public slots:
    void set_light_bulb_period(int value);
    void set_light_bulb_amplitude(int value);


    private:
    float light_bulb_angle;
    float light_bulb_amplitude = 60;
    float light_bulb_speed = 0.05;
    float light_bulb_time = 0.0;
    // textures
    Image* wall_texture;
    Image* wood_texture;
    Image* world_texture;

    protected:
    // OpenGL functions for init, resize and paint
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif