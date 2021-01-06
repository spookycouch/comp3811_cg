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
 * texture points to vertices in square().
**/
typedef struct textureTransform {
    float translate[2];
    float scale[2];
} textureTransform;


/** Square
 * a flat plane from x=0 to x=1, y=0 to y=1
 *
 * PARAMS:  p_front         material properties
 *          n_div           number of sub-divisions
 *          tex_transform   transform to apply to texture
 *
**/
void square(const materialStruct* p_front, int n_div=1, textureTransform* tex_transform=0);


/** Cube
 * 9 outward-facing squares to form a cube.
 *
 * PARAMS:  p_front         material properties
 *
**/
void cube(const materialStruct* p_front);


/** Cylinder
 * taken from COMP3811 tutorials
 * a cylinder of origin at the centre with z=0.
 * normals face inwards to reflect contained light source.
 *
 * PARAMS:  p_front         material properties
 *          N               number of faces
 *          n_div           number of height divisions
 *
**/
void cylinder_inside(const materialStruct* p_front, int N=6, int n_div=1);


/** Sphere
 * GLUT sphere of origin at its centre.
 * normals face inwards to reflect contained light source.
 *
 * PARAMS:  p_front         material properties
 *
**/
void sphere_inside(const materialStruct* p_front);

#endif