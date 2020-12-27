#include "utils/Shapes.h"
#include <cmath>

void square(const materialStruct* p_front, int n_div, textureTransform* tex_transform) {
    glMaterialfv(GL_FRONT, GL_AMBIENT,  p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS, p_front->shininess);

    float step_size = 1.0/n_div;

    for (int i = 0; i < n_div; ++i)
        for (int j = 0; j < n_div; ++j)
        {
            // vertex coordinates
            float x0 = i * step_size;
            float y0 = j * step_size;
            float x1 = x0 + step_size;
            float y1 = y0 + step_size;

            // texture coordinates
            float tx0 = x0;
            float ty0 = y0;
            float tx1 = x1;
            float ty1 = y1;

            // apply texture transforms (if present)
            if (tex_transform) {
                tx0 = x0 + tex_transform->translate[0];
                ty0 = y0 + tex_transform->translate[1];
                tx1 = tx0 + step_size*tex_transform->scale[0];
                ty1 = ty0 + step_size*tex_transform->scale[1];
            }

            // create polygon
            glBegin(GL_POLYGON);
                glTexCoord2f(tx0, ty0);
                glVertex3f(x0,y0,0);
                glNormal3f(0,0,1);

                glTexCoord2f(tx1, ty0);
                glVertex3f(x1,y0,0);
                glNormal3f(0,0,1);

                glTexCoord2f(tx1, ty1);
                glVertex3f(x1,y1,0);
                glNormal3f(0,0,1);

                glTexCoord2f(tx0, ty1);
                glVertex3f(x0,y1,0);
                glNormal3f(0,0,1);
            glEnd();
        }
}

void cube(const materialStruct* p_front) {
    glPushMatrix();

    // top
    glTranslatef(0,0,1);
    square(p_front);
    // front
    glRotatef(90.,1,0,0);
    glTranslatef(0,-1,0);
    square(p_front);
    // bottom
    glRotatef(90.,1,0,0);
    glTranslatef(0,-1,0);
    square(p_front);
    // back
    glRotatef(90.,1,0,0);
    glTranslatef(0,-1,0);
    square(p_front);
    // right
    glPushMatrix();
    glRotatef(90.,0,1,0);
    glTranslatef(0,0,1);
    square(p_front);
    glPopMatrix();
    // left
    glRotatef(-90.,0,1,0);
    glTranslatef(-1,0,0);
    square(p_front);

    glPopMatrix();
}


void cylinder(const materialStruct* p_front, int N, int n_div) {
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    float x0, x1, y0, y1;
    float tx0, tx1, ty0, ty1;
    float z_min = 0;
    float z_max = 1;
    float delta_z = (z_max - z_min)/n_div;

    for (int i = 0; i < N; i++){
        for(int i_z = 0; i_z < n_div; i_z++){
            x0 = cos(2*i*M_PI/N);
            x1 = cos(2*(i+1)*M_PI/N);
            y0 = sin(2*i*M_PI/N);
            y1 = sin(2*(i+1)*M_PI/N);

            // flip texture x coords
            tx0 = 1;
            ty0 = 0;
            tx1 = 0;
            ty1 = 1;

            // NOTE: drawn clockwise to face inwards
            float z = z_min + i_z*delta_z;
            glBegin(GL_POLYGON);
                glTexCoord2f(tx0, ty0);
                glVertex3f(x0,y0,z);
                glNormal3f(-x0,-y0,0);

                glTexCoord2f(tx0, ty1);
                glVertex3f(x0,y0,z+delta_z);
                glNormal3f(-x0,-y0,0);

                glTexCoord2f(tx1, ty1);
                glVertex3f(x1,y1,z+delta_z);
                glNormal3f(-x1,-y1,0);

                glTexCoord2f(tx1, ty0);
                glVertex3f(x1,y1,z);
                glNormal3f(-x1,-y1,0);
            glEnd();
        }
    }
}

void sphere(const materialStruct* p_front){

    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
    GLUquadric * quad = gluNewQuadric();
    gluQuadricOrientation(quad, GLU_INSIDE);
    gluSphere(quad, 1, 32, 32);
}