#include "utils/WavefrontObj.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <GL/glu.h>


WavefrontObj::WavefrontObj() {
    vertices = new std::vector<std::vector<float> >();
    textures = new std::vector<std::vector<float> >();
    normals = new std::vector<std::vector<float> >();
    materials = new std::map<std::string, wavefrontMtl>();
    sub_objects = new std::vector<wavefrontSubObj>();
    images = new std::vector<Image*>();
}


WavefrontObj::~WavefrontObj() {
    delete vertices;
    delete normals;
    delete materials;
    delete sub_objects;
}


void WavefrontObj::load_mtl(std::string path) {
    std::ifstream mtl(path.c_str());
    if (mtl.fail())
        return;

    // create mtl struct
    wavefrontMtl* mtl_struct = 0;

    // parse the file
    std::string line;
    while (std::getline(mtl, line)) {
        // parse the token
        char token[128];
        sscanf(line.c_str(), "%s", token);


        // parse new material
        if (!strcmp(token, "newmtl")) {
            char name[128];
            sscanf(line.c_str(), "%s %s", token, name);

            if(mtl_struct)
                materials->insert(std::pair<std::string, wavefrontMtl>(mtl_struct->name, *mtl_struct));
            mtl_struct = new wavefrontMtl();
            mtl_struct->name = std::string(name);
        }


        // parse ambient
        if (!strcmp(token, "Ka")) {
            float r,g,b;

            if (sscanf(line.c_str(), "%s %f %f %f", token, &r, &g, &b) <= 1)
                continue;

            // store values
            mtl_struct->ambient[0] = r;
            mtl_struct->ambient[1] = g;
            mtl_struct->ambient[2] = b;
            mtl_struct->ambient[3] = 1.0;
        }


        // parse diffuse
        if (!strcmp(token, "Kd")) {
            float r,g,b;

            if (sscanf(line.c_str(), "%s %f %f %f", token, &r, &g, &b) <= 1)
                continue;

            // store values
            mtl_struct->diffuse[0] = r;
            mtl_struct->diffuse[1] = g;
            mtl_struct->diffuse[2] = b;
            mtl_struct->diffuse[3] = 1.0;
        }


        // parse specular
        if (!strcmp(token, "Ks")) {
            float r,g,b;

            if (sscanf(line.c_str(), "%s %f %f %f", token, &r, &g, &b) <= 1)
                continue;

            // store values
            mtl_struct->specular[0] = r;
            mtl_struct->specular[1] = g;
            mtl_struct->specular[2] = b;
            mtl_struct->specular[3] = 1.0;
        }


        // parse material library
        if (!strcmp(token, "map_Kd")) {
            char path[128];
            sscanf(line.c_str(), "%s %s", token, path);

            mtl_struct->path = std::string(path);
            mtl_struct->image_index = images->size();

            images->push_back(new Image(mtl_struct->path));
        }
    }


    // push back the current material
    if (mtl_struct)
        materials->insert(std::pair<std::string, wavefrontMtl>(mtl_struct->name, *mtl_struct));
}


void WavefrontObj::load(std::string path) {
    // try to create filestream
    std::ifstream obj(path.c_str());
    if (obj.fail())
        return;

    std::string line;
    wavefrontSubObj* sub_object = 0;

    // for each line
    while (std::getline(obj, line)) {
        // parse the token
        char token[128];
        sscanf(line.c_str(), "%s", token);


        // parse material library
        if (!strcmp(token, "mtllib")) {
            char path[128];
            sscanf(line.c_str(), "%s %s", token, path);

            load_mtl(std::string(path));
        }


        // parse vertex
        if (!strcmp(token, "v")) {
            std::vector<float> vertex;
            float x,y,z;

            if (sscanf(line.c_str(), "%s %f %f %f", token, &x, &y, &z) <= 1)
                continue;

            // store values
            vertex.push_back(x);
            vertex.push_back(y);
            vertex.push_back(z);
            vertices->push_back(vertex);
        }


        // parse normal
        if (!strcmp(token, "vt")) {
            std::vector<float> texture;
            float x,y,z;

            if (sscanf(line.c_str(), "%s %f %f %f", token, &x, &y, &z) <= 1)
                continue;

            // store values
            texture.push_back(x);
            texture.push_back(y);
            texture.push_back(z);
            textures->push_back(texture);
        }


        // parse normal
        if (!strcmp(token, "vn")) {
            std::vector<float> normal;
            float x,y,z;

            if (sscanf(line.c_str(), "%s %f %f %f", token, &x, &y, &z) <= 0)
                continue;

            // store values
            normal.push_back(x);
            normal.push_back(y);
            normal.push_back(z);
            normals->push_back(normal);
        }


        // parse sub-object
        if (!strcmp(token, "o")) {
            char name[128];
            sscanf(line.c_str(), "%s %s", token, name);

            if (sub_object)
                sub_objects->push_back(*sub_object);

            sub_object = new wavefrontSubObj();
            sub_object->name = std::string(name);
        }


        // parse new material
        if (!strcmp(token, "usemtl")) {
            char name[128];
            sscanf(line.c_str(), "%s %s", token, name);

            if (materials->find(std::string(name)) != materials->end())
                sub_object->mtl = &materials->at(std::string(name));
        }


        // parse polygon face
        if (!strcmp(token, "f")) {
            std::vector<int>* v_indices = new std::vector<int>();
            std::vector<int>* t_indices = new std::vector<int>();
            std::vector<int>* n_indices = new std::vector<int>();

            std::stringstream linestream(line.substr(line.find("f") + 1));
            std::string face_str;

            // parse any number of polygon indices
            while(std::getline(linestream, face_str, ' ')) {
                int v,n,t;

                if (sscanf(face_str.c_str(), "%d/%d/%d", &v, &n, &t) <= 0)
                    continue;

                v_indices->push_back(v);
                t_indices->push_back(n);
                n_indices->push_back(t);
            }
            sub_object->face_vertices.push_back(*v_indices);
            sub_object->face_textures.push_back(*t_indices);
            sub_object->face_normals.push_back(*n_indices);
        }
    }


    // push back the current sub-object
    if (sub_object)
        sub_objects->push_back(*sub_object);
}


void WavefrontObj::draw() {
    // for each sub-object
    for (std::vector<wavefrontSubObj>::iterator sub_object = sub_objects->begin(); sub_object != sub_objects->end(); ++sub_object) {
        wavefrontMtl* mtl = sub_object->mtl;

        // if the sub-object's material has a path,
        // enable textures and load the corresponding image
        if (mtl->path.size()) {
            Image* texture = images->at(mtl->image_index);
            glEnable(GL_TEXTURE_2D);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->Width(), texture->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture->imageField());
        }

        // set material properties
        glMaterialfv(GL_FRONT, GL_AMBIENT,  mtl->ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,  mtl->diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mtl->specular);
        glMaterialf(GL_FRONT, GL_SHININESS, mtl->shininess);

        // for each polygon
        for (uint face_index=0; face_index < sub_object->face_vertices.size(); ++face_index) {
            glBegin(GL_POLYGON);

            // set vertex, normal and texture coordinates
            for (uint point_index=0; point_index < sub_object->face_vertices.at(face_index).size(); ++point_index) {
                int v = sub_object->face_vertices.at(face_index).at(point_index);
                int t = sub_object->face_textures.at(face_index).at(point_index);
                int n = sub_object->face_normals.at(face_index).at(point_index);

                std::vector<float> vertex = vertices->at(v - 1);
                std::vector<float> texture = textures->at(t - 1);
                std::vector<float> normal = normals->at(n - 1);
                glTexCoord3f(texture.at(0), texture.at(1), texture.at(2));
                glNormal3f(normal.at(0), normal.at(1), normal.at(2));
                glVertex3f(vertex.at(0), vertex.at(1), vertex.at(2));
            }

            glEnd();
        }

        glDisable(GL_TEXTURE_2D);
    }
}