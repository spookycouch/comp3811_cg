#ifndef __SC18J3J_WAVEFRONT__
#define __SC18J3J_WAVEFRONT__

#include <string>
#include <vector>
#include <map>
#include "utils/Image.h"

typedef struct wavefrontMtl {
    std::string name;
    std::string path;
    int image_index;
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
}wavefrontMtl;

typedef struct wavefrontSubObj {
    std::string name;
    wavefrontMtl* mtl;
    std::vector<std::vector<int> > face_vertices;
    std::vector<std::vector<int> > face_textures;
    std::vector<std::vector<int> > face_normals;
}wavefrontSubObj;

class WavefrontObj {
    public:
    WavefrontObj(); //constructor
    ~WavefrontObj(); // destructor

    /** Load .MTL files
     * Parse material textures and their ambient,
     * diffuse and specular values.
     * A wavefrontMtl struct is created for each
     * material parsed.
     *
     */
    void load_mtl(std::string path);

    /** Load .OBJ files
     * Parse vertex, texture and normal coordinates.
     * A wavefrontSubObj struct is created for each
     * sub-object parsed.
     *
     */
    void load(std::string path);

    /** Draw
     * Draw each stored sub-object using their
     * corresponding vertex, normal, material
     * and texture values.
     *
     */
    void draw();


    private:
    // data structures to store object
    std::vector<std::vector<float> >* vertices;
    std::vector<std::vector<float> >* textures;
    std::vector<std::vector<float> >* normals;
    std::map<std::string, wavefrontMtl>* materials;
    std::vector<Image*>* images;
    std::vector<wavefrontSubObj>* sub_objects;
};

#endif