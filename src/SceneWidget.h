#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include "utils/Image.h"
#include "utils/WavefrontObj.h"

struct materialStruct;
struct textureTransform;

class SceneWidget: public QGLWidget {
    public:
    /** Constructor
     *
     **/
    SceneWidget(QWidget *parent);


    private:
    /** Walls for the setting.
     * Made up of 2D squares.
     * Uses materials and textures.
     */
    void walls();

    /** Window for the setting.
     * Made up of 3D cubes.
     * Uses materials and textures.
     */
    void window();

    /** Light bulb for the setting.
     * Made up of cylinders and spheres.
     * Uses materials.
     */
    void light_bulb();

    /** House
     * Setting for our complex visual scene, comprised of
     * walls, a window and a light bulb.
    **/
    void house();

    /** Background
     * Background viewable from the window of our house.
     */
    void background();

    /** Character
     * Draw the character, a convex object constructed
     * from polygons.
     */
    void character();


    public slots:
    /** Setters
     * for Qt interface.
     */
    void set_light_bulb_period(int value);
    void set_light_bulb_amplitude(int value);
    void set_background_index(int index);
    void set_background_speed(int value);


    private:
    // wavefront objects
    WavefrontObj body;
    WavefrontObj head;

    // variables to be adjusted via Qt
    float light_bulb_angle = 0;
    float light_bulb_amplitude = 60;
    float light_bulb_speed = 0.05;
    float light_bulb_time = 0.0;
    float background_rotation = 0.0;
    float background_speed = 1.0;

    // textures used in the scene
    Image* wall_texture;
    Image* wood_texture;
    std::vector<Image*> bg_textures;
    int bg_index = 0;


    protected:
    // OpenGL functions for init, resize and paint
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif