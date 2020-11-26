#include "Mesh.h"
#include <iostream>


static materialStruct ironMaterials = {
  { 0.33, 0.33, 0.33, 1.0},
  { 0.57, 0.57, 0.57, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8 
};


/** Constructor
 *
 * Initialise vertex and element vectors
 * load obj
 */
Mesh::Mesh(const char *filename) {
    SetPosition(0,0,0);
    SetRotation(0,0,0);

    vertices = new std::vector<std::vector<float> >();
    vertex_normals = new std::vector<std::vector<float> >();
    elements = new std::vector<Element>();
    LoadWaveFront(filename);
}



/** Stringstrip
 *
 * convenience function to remove special characters
 * when parsing .obj files.
 */
std::string stringstrip(std::string str, std::string delimiters) {
    for (unsigned int i = 0; i < delimiters.size(); ++i) {
        int index = str.find(delimiters[i]);
        if (index != (int)std::string::npos)
            str = str.substr(0, index);
    }
    return str;
}

/** Load .OBJ file
 *
 * parse each line and extract vertices/polygon faces
 */
void Mesh::LoadWaveFront(const char *filename) {
    std::string line;
    std::ifstream obj(filename);

    // new element
    elements->push_back(Element());
    Element *element = &(elements->back());

    // parse each line
    while (std::getline(obj, line)) {
        std::string token;
        std::stringstream values(line);
        std::getline(values, token, ' ');


        // token 'o': object name
        if (token == "o") {
            std::getline(values, token, ' ');
            token = stringstrip(token, "\r\n");
            element->object_name = token;
        }


        // token 'g': group name
        if (token == "g") {
            std::getline(values, token, ' ');
            token = stringstrip(token, "\r\n");
            element->group_name = token;
        }


        // token 'v': vertex
        else if (token == "v") {
            std::vector<float> vertex;

            // parse valid floats
            while (std::getline(values, token, ' ')) {
                try {
                    vertex.push_back(std::stof(token.c_str()));
                }
                catch(std::invalid_argument e) {}
            }

            vertices->push_back(vertex);
        }


        // token 'vn': vertex normal
        else if (token == "vn") {
            std::vector<float> vertex_normal;

            // parse valid floats
            while (std::getline(values, token, ' ')) {
                try {
                    vertex_normal.push_back(std::stof(token.c_str()));
                }
                catch(std::invalid_argument e) {}
            }

            vertex_normals->push_back(vertex_normal);
        }


        // token 'f': polygon face
        else if (token == "f") {
            std::vector<int> polygon;
            std::vector<int> texture;
            std::vector<int> normal;

            while (std::getline(values, token, ' ')) {
                // parse valid ints as vertices
                try {
                    polygon.push_back(std::stoi(token.c_str()));
                }
                catch(std::invalid_argument e) {}

                // check if we have a texture delimiter
                int texture_index = token.find("/");
                if (texture_index == (int)std::string::npos)
                    continue;
                
                // check if we have a normal delimiter
                int normal_index = texture_index + 1;
                normal_index += token.substr(normal_index).find("/");

                // try to parse normals if a second '/' is found
                if (normal_index != (int)std::string::npos) {
                    try {
                        normal.push_back(std::stoi(token.substr(normal_index + 1).c_str()));
                    }
                    catch(std::invalid_argument e) {}
                }

                // try to parse textures if a '/' is found, not preceeding a '/'
                if (normal_index - texture_index != 1) {
                    try {
                        texture.push_back(std::stoi(token.substr(texture_index + 1).c_str()));
                    }
                    catch(std::invalid_argument e) {}
                }
            }

            // push back useful vectors to the struct
            element->polygons.push_back(polygon);
            if (texture.size() > 0)
                element->textures.push_back(texture);
            if (normal.size() > 0)
                element->normals.push_back(normal);
        }


        // no valid definitions on this line.
        // push back element
        else if (element->polygons.size() > 0) {
            std::cout << element->object_name << " " << element->group_name << std::endl;
            elements->push_back(Element());
            element = &(elements->back());
        }
    }
}



/** Render Element
 *
 * Meshes are typically composed of many elements.
 * We render all polygons in an element here.
 */
void Mesh::RenderElement(Element *element, materialStruct material) {
    glMaterialfv(GL_FRONT, GL_AMBIENT,  material.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  material.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);

    // render each polygon
    for (unsigned int i = 0; i < element->polygons.size(); ++i) {
        glBegin(GL_POLYGON);

        // for each vertex in the polygon
        for (unsigned int j = 0; j < element->polygons.at(i).size(); ++j) {

            // if a corresponding normal exists, apply it
            if (j < element->normals.at(i).size()) {
                std::vector<float> normal = vertex_normals->at(element->normals.at(i).at(j) - 1);
                glNormal3f(normal.at(0), normal.at(1), normal.at(2));
            }

            // add the vertex to the polygon
            std::vector<float> vertex = vertices->at(element->polygons.at(i).at(j) - 1);
            glVertex3f(vertex.at(0), vertex.at(1),  vertex.at(2));
        }
        glEnd();
    }
}



/** Draw Mesh
 *
 * Draw the mesh. Mostly for testing rn
 */
void Mesh::Draw() {
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
    // glLoadIdentity();

    glTranslatef(-position[0], -position[1], -position[2]);
    glRotatef(rotation[0], 1, 0, 0);
    glRotatef(rotation[1], 0, 1, 0);
    glRotatef(rotation[2], 0, 0, 1);

    for (std::vector<Element>::iterator elem_it = elements -> begin(); elem_it != elements -> end(); ++elem_it)
        RenderElement(&*elem_it, ironMaterials);
    
    glPopMatrix();
}