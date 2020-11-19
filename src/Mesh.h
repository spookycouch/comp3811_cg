#include <GL/glu.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>

class Mesh {
    public:
    Mesh(char *filename);
    void RenderElement(std::vector<std::vector<float> > *vertices, std::vector<std::vector<int> > *polygons, float c1, float c2, float c3);
    void Draw();
    
    private:
    std::vector<std::vector<float> > *vertices;
    std::vector<std::vector<std::vector<int> > > *elements;
    void LoadWaveFront(char *filename);
};