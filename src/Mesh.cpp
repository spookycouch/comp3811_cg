#include "Mesh.h"

// LAZINESS. DEFINE STUFF AT FILE LEVEL
float x_rot = 0;
float y_rot = 0;
float z_rot = 0;


/** Constructor
 *
 * Initialise vertex and element vectors
 * load obj
 */
Mesh::Mesh(char *filename) {
    vertices = new std::vector<std::vector<float> >();
    elements = new std::vector<std::vector<std::vector<int > > >();
    LoadWaveFront(filename);
}


/** Load .OBJ file
 *
 * parse each line and extract vertices/polygon faces
 */
void Mesh::LoadWaveFront(char *filename) {
    std::string line;
    std::ifstream obj(filename);

    elements->push_back(*new std::vector<std::vector<int > >());
    std::vector<std::vector<int> > *polygons = &(elements->back());

    // parse line
    while (std::getline(obj, line)) {
        std::string token;
        std::stringstream values(line);
        std::getline(values, token, ' ');

        // token 'v': vertex
        if (token == "v") {
            std::vector<float> vertex;

            // parse all valid floats
            while (std::getline(values, token, ' ')) {
                try {
                    vertex.push_back(std::stof(token.c_str()));
                }
                catch(std::invalid_argument e) {}
            }

            vertices->push_back(vertex);

        }

        // token 'f': polygon face
        else if (token == "f") {
            std::vector<int> polygon;

            // parse all valid ints
            while (std::getline(values, token, ' ')) {
                try {
                    polygon.push_back(std::stoi(token.c_str()));
                }
                catch(std::invalid_argument e) {}
            }

            polygons->push_back(polygon);
        }

        // no valid definitions on this line.
        // push back polygons
        else if (polygons->size() > 0) {
            elements->push_back(*new std::vector<std::vector<int > >());
            polygons = &(elements->back());
        }
    }
}


// MatMult for rotation matrices
void calc_rotation(float a[3][3], float b[3][3], float c[3][3]) {
    for (int a_row = 0; a_row < 3; ++a_row)
        for(int b_col = 0; b_col < 3; ++b_col) {

            float sum = 0;
            for(int b_row = 0; b_row < 3; ++b_row)
                sum += a[a_row][b_row] * b[b_row][b_col];

            c[a_row][b_col] = sum;
        }
}


/** Render Element
 *
 * Meshes are typically composed of many elements.
 * We render all polygons in an element here.
 */
void Mesh::RenderElement(std::vector<std::vector<float> > *vertices, std::vector<std::vector<int> > *polygons, float c1, float c2, float c3) {
    glColor3f(c1, c2, c3);
    

    float x_mat[3][3] = {{1,0,0},
                            {0,cos(x_rot),-sin(x_rot)},
                            {0,sin(x_rot),cos(x_rot)}};
    float y_mat[3][3] = {{cos(y_rot),0,sin(y_rot)},
                            {0,1,0},
                            {-sin(y_rot),0,cos(y_rot)}};
    float z_mat[3][3] = {{cos(z_rot),-sin(z_rot),0},
                            {sin(z_rot),cos(z_rot),0},
                            {0,0,1}};
    
    float rotation[3][3];
    float temp[3][3];
    calc_rotation(x_mat, y_mat, temp);
    calc_rotation(z_mat, temp, rotation);


    // render each polygon in the element
    for (std::vector<std::vector<int> >::iterator poly_it = polygons->begin(); poly_it != polygons->end(); ++poly_it) {
        glBegin(GL_POLYGON);
        for (std::vector<int>::iterator vert_it = poly_it->begin(); vert_it != poly_it->end(); ++vert_it) {
            std::vector<float> vertex = vertices->at(*vert_it - 1);
            // glVertex3f(vertex.at(0)/10, vertex.at(1)/10,  vertex.at(2)/10);
            glVertex3f(vertex.at(0)/10 * rotation[0][0] + vertex.at(1)/10 * rotation[0][1] + vertex.at(2)/10 * rotation[0][2],
                       vertex.at(0)/10 * rotation[1][0] + vertex.at(1)/10 * rotation[1][1] + vertex.at(2)/10 * rotation[1][2],
                       vertex.at(0)/10 * rotation[2][0] + vertex.at(1)/10 * rotation[2][1] + vertex.at(2)/10 * rotation[2][2]);
        }
        glEnd();
    }
}


/** Draw Mesh
 *
 * Draw the mesh. Mostly for testing rn
 */
void Mesh::Draw() {
    int c_count = 0;
    float c1[] = {0,0.5,0,0};
    float c2[] = {0,0.5,0,0};
    float c3[] = {0,0.5,0,0};

    for (std::vector<std::vector<std::vector<int> > >::iterator polygons = elements->begin(); polygons != elements->end(); ++polygons) {
        RenderElement(vertices, &*polygons, c1[c_count], c2[c_count], c3[c_count]);
        ++c_count;
    }

    // TEST
    y_rot += 0.1;
}