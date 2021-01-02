#ifndef __SC18J3J_SHAPES__
#define __SC18J3J_SHAPES__

#include <GL/glu.h>
#include <GL/glut.h>

/** Material
 * struct comprising phong
 * lighting values.
**/
typedef struct materialStruct {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
} materialStruct;

/** Texture transform
 * translation and scale for mapping
 * texture points to vertices.
**/
typedef struct textureTransform {
    float translate[2];
    float scale[2];
} textureTransform;

/** Square
 * a flat plane from x=0 to x=1, y=0 to y=1
**/
void square(const materialStruct* p_front, int n_div=1, textureTransform* tex_transform=0);


/** Cube
 * GLUT solid cube of origin at the bottom left with z=0
**/
void cube(const materialStruct* p_front);


/** Cylinder
 * taken from COMP3811 tutorials
 * a cylinder of origin at the centre with z=0
**/
void cylinder(const materialStruct* p_front, int N=6, int n_div=1);


/** Sphere
 * GLUT sphere of origin at its centre
**/
void sphere(const materialStruct* p_front );

#endif