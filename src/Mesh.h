#ifndef MESH_H
#define MESH_H

#include <GL/glu.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>

typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

typedef struct Element {
    std::string object_name;
    std::string group_name;
    std::vector<std::vector<int> > polygons;
    std::vector<std::vector<int> > textures;
    std::vector<std::vector<int> > normals;
} Element;


class Mesh {
    public:
    Mesh(const char *filename);
    void RenderElement(Element *element, materialStruct material);
    void Draw();
    inline void SetPosition(float x, float y, float z) {
        position[0] = x, position[1] = y, position[2] = z;
    };
    inline void SetRotation(float r, float p, float y) {
        rotation[0] = r, rotation[1] = p, rotation[2] = y;
    };

    private:
    void LoadWaveFront(const char *filename);
    float position[3];
    float rotation[3];
    std::vector<std::vector<float> > *vertices;
    std::vector<std::vector<float> > *vertex_normals;
    std::vector<Element> *elements;
};

#endif