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
    WavefrontObj();
    ~WavefrontObj();
    void load_mtl(std::string path);
    void load(std::string path);
    void draw();

    private:
    std::vector<std::vector<float> >* vertices;
    std::vector<std::vector<float> >* textures;
    std::vector<std::vector<float> >* normals;
    std::map<std::string, wavefrontMtl>* materials;
    std::vector<Image*>* images;
    std::vector<wavefrontSubObj>* sub_objects;
};

#endif